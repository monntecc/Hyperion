#include "hrpch.hpp"

#include "Runtime/RHI/OpenGL/OpenGLShader.hpp"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <Tracy.hpp>

namespace Hyperion {
    
    static GLenum ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;

        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        HR_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        ZoneScoped;

        const std::string source = ReadFile(filepath);
        const auto shaderSources = PreProcess(source);

        Compile(shaderSources);

        // Extract shader name from filepath
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        const auto lastDot = filepath.rfind('.');
        const auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);

        HR_CORE_TRACE("Shader '{0}' was compiled successfully!", m_Name);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name)
    {
        ZoneScoped;

        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);

        HR_CORE_TRACE("Shader '{0}' was compiled successfully!", m_Name);
    }

    OpenGLShader::~OpenGLShader()
    {
        ZoneScoped;

        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const
    {
        ZoneScoped;

        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        ZoneScoped;

        glUseProgram(0);
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) const
    {
        ZoneScoped;

        UploadUniformMat4(name, value);
    }

    void OpenGLShader::SetFloat(const std::string& name, float value) const
    {
        ZoneScoped;

        UploadUniformFloat(name, value);
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value) const
    {
        ZoneScoped;

        UploadUniformFloat3(name, value);
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value) const
    {
        ZoneScoped;

        UploadUniformFloat4(name, value);
    }

    void OpenGLShader::SetInt(const std::string& name, int value) const
    {
        ZoneScoped;

        UploadUniformInt(name, value);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, int value) const
    {
        const GLint location = GetUniformLocation(name);
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, float value) const
    {
        const GLint location = GetUniformLocation(name);
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values) const
    {
        const GLint location = GetUniformLocation(name);
        glUniform2f(location, values.x, values.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values) const
    {
        const GLint location = GetUniformLocation(name);
        glUniform3f(location, values.x, values.y, values.z);
    }

    void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const
    {
        const GLint location = GetUniformLocation(name);
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const
    {
        const GLint location = GetUniformLocation(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    std::string OpenGLShader::ReadFile(const std::string& filepath)
    {
        ZoneScoped;

        std::string result;

        if (std::ifstream in(filepath, std::ios::in, std::ios::binary); in)
        {
            in.seekg(0, std::ios::end);
            const size_t size = in.tellg();
            if (static_cast<int>(size) != -1)
            {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(result.data(), static_cast<std::streamsize>(size));
                in.close();
            }
            else
            {
                HR_CORE_ERROR("Could not read from file '{0}'", filepath);
            }
        }
        else
        {
            HR_CORE_ERROR("Could not open file '{0}'", filepath);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
    {
        ZoneScoped;

        std::unordered_map<GLenum, std::string> shaderSources;

        const auto typeToken = "#type";
        const size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0); //Start of shader type declaration line

        while (pos != std::string::npos)
        {
            const size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
            HR_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            const size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
            std::string type = source.substr(begin, eol - begin);
            HR_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            //Start of shader code after shader type declaration line
            HR_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
            pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line
            shaderSources[ShaderTypeFromString(type)] = pos == std::string::npos
                                                            ? source.substr(nextLinePos)
                                                            : source.substr(nextLinePos, pos - nextLinePos);
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
        ZoneScoped;

        // Get a program object.
        const GLuint program = glCreateProgram();
        HR_CORE_ASSERT(shaderSources.size() <= 2, "Hyperion only supports 2 shaders for now!");
        std::array<GLenum, 2> glShaderIDs;
        int glShaderIDIndex = 0;

        for (const auto& [type, source] : shaderSources)
        {
            const GLuint shader = glCreateShader(type);

            const GLchar* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, nullptr);

            // Compile our shader
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

                // We don't need the shader anymore.
                glDeleteShader(shader);

                HR_CORE_ERROR("{0}", infoLog.data());
                HR_CORE_ASSERT(false, "Shader compilation failure!");

                break;
            }

            // Shader are successfully compiled.
            // Now time to link it into a program.
            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;

        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            for (const auto id : glShaderIDs)
                glDeleteShader(id);

            HR_CORE_ERROR("{0}", infoLog.data());
            HR_CORE_ASSERT(false, "Shader link failure!");

            // In this simple program, we'll just leave
            return;
        }

        GLint count = 0;
        glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
        HR_CORE_ASSERT(count, "Count of uniforms must be more then 0!");

        GLsizei bufSize = 0;
        glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &bufSize);
        HR_CORE_ASSERT(bufSize, "Active uniform buffer size cannot be 0!");

        for (int i = 0; i < count; i++)
        {
            GLenum type;
            const auto name = new GLchar[bufSize];
            GLint size;
            GLsizei length;

            glGetActiveUniform(program, static_cast<GLuint>(i), bufSize, &length, &size, &type, name);

            uniformMap.emplace(name, glGetUniformLocation(program, name));

            delete[] name;
        }

        // Always detach shaders after a successful link.
        for (const auto id : glShaderIDs)
        {
            glDetachShader(program, id);
            glDeleteShader(id); // Prevent shader from being leaked
        }

        m_RendererID = program;
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values) const
    {
        ZoneScoped;

        const GLint location = uniformMap.at(name);
        glUniform4f(location, values.x, values.y, values.z, values.w);
    }
}

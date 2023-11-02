#pragma once

#include "Runtime/Renderer/Shader.hpp"

#include <glm/glm.hpp>

#include "glad/glad.h"

namespace Hyperion {

	class HYPERION_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		const std::string& GetName() const override { return m_Name; }

		void SetMat4(const std::string& name, const glm::mat4& value) const override;
		void SetFloat3(const std::string& name, const glm::vec3& value) const override;
		void SetFloat4(const std::string& name, const glm::vec4& value) const override;
		void SetInt(const std::string& name, int value) const override;

		void UploadUniformInt(const std::string& name, int value) const;
		
		void UploadUniformFloat(const std::string& name, float value) const;
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values) const;
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values) const;
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values) const;
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;

	private:
		static std::string ReadFile(const std::string& filepath);
		static std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		std::unordered_map<std::string, GLint> uniformMap = std::unordered_map<std::string, GLint>();
		
		uint32_t m_RendererID;
		std::string m_Name;
	};

}

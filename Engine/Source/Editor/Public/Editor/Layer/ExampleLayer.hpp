#pragma once

#include "Hyperion.hpp"

class ExampleLayer : public Hyperion::Layer
{
public:
    ExampleLayer();

    void OnImGuiRender() override;
    void OnUpdate(Hyperion::Timestep timestep) override;
    void OnEvent(Hyperion::Event& event) override;

private:
	Hyperion::ShaderLibrary m_ShaderLibrary;
    Hyperion::Ref<Hyperion::Shader> m_Shader;
    Hyperion::Ref<Hyperion::VertexArray> m_VertexArray;

    Hyperion::Ref<Hyperion::Shader> m_FlatColorShader;
    Hyperion::Ref<Hyperion::VertexArray> m_SquareVA;

	Hyperion::Ref<Hyperion::Texture2D> m_Texture, m_HyperionLogoTexture;

    Hyperion::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;

    float m_CameraMoveSpeed = 5.0f; // meters per second

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f; // degrees per second

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

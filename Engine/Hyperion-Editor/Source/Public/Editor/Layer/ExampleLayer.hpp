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
    Hyperion::OrthographicCameraController m_CameraController;
    
	Hyperion::ShaderLibrary m_ShaderLibrary;
    Hyperion::Ref<Hyperion::Shader> m_Shader;
    Hyperion::Ref<Hyperion::VertexArray> m_VertexArray;

    Hyperion::Ref<Hyperion::Shader> m_FlatColorShader;
    Hyperion::Ref<Hyperion::VertexArray> m_SquareVA;

	Hyperion::Ref<Hyperion::Texture2D> m_Texture, m_HyperionLogoTexture;

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

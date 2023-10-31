#pragma once

#include "Hyperion.hpp"

class Sandbox2DLayer : public Hyperion::Layer
{
public:
    Sandbox2DLayer();
    ~Sandbox2DLayer() override = default;

    void OnUpdate(Hyperion::Timestep timestep) override;
    void OnEvent(Hyperion::Event& event) override;
    void OnImGuiRender() override;

    void OnAttach() override;
    void OnDetach() override;
private:
    Hyperion::OrthographicCameraController m_CameraController;

    // TODO: Temporary
    Hyperion::Ref<Hyperion::VertexArray> m_SquareVA;
    Hyperion::Ref<Hyperion::Shader> m_FlatColorShader;
    
    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
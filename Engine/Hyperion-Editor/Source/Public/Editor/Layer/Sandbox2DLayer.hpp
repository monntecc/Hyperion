#pragma once

#include "Hyperion.hpp"

#include "Editor/Content/ParticleSystem.hpp"

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
    Hyperion::Ref<Hyperion::Texture2D> m_CheckerboardTexture;
    // Hyperion::Ref<Hyperion::Texture2D> m_SpriteSheet;

    Hyperion::Ref<Hyperion::FrameBuffer> m_FrameBuffer;

    glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
    glm::vec4 m_CheckerboardColor = glm::vec4(1.0f);
    glm::vec4 m_RotatedCheckerboardColor = glm::vec4(1.0f);

    ParticleProps m_Particle;
    ParticleSystem m_ParticleSystem;
};

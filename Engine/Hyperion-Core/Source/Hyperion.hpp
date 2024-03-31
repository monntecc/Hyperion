#pragma once

// For use by Hyperion applications

#include "Engine/Core/Base.hpp"

#include "Engine/Core/Application.hpp"
#include "Engine/Core/Layer.hpp"
#include "Engine/Core/Log.hpp"
#include "Engine/Core/Input.hpp"
#include "Engine/Core/Assert.hpp"

#include "Engine/UI/ImGuiLayer.hpp"
#include "Engine/UI/UI.hpp"
#include "Engine/UI/ImGuiTheme.hpp"

#include "Engine/Core/Timestep.hpp"

// ------------------- Scene -------------------
#include "Engine/Scene/Scene.hpp"
#include "Engine/Scene/Entity.hpp"
#include "Engine/Scene/Components.hpp"
#include "Engine/Scene/ScriptableEntity.hpp"
// ------------------------------------------------

// ------------------- Renderer -------------------
#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Renderer/Renderer2D.hpp"
#include "Engine/Renderer/RenderCommand.hpp"

#include "Engine/Renderer/Buffer.hpp"
#include "Engine/Renderer/FrameBuffer.hpp"
#include "Engine/Renderer/Shader.hpp"
#include "Engine/Renderer/VertexArray.hpp"

#include "Engine/Renderer/Texture.hpp"

#include "Engine/Renderer/OrthographicCamera.hpp"
#include "Engine/Renderer/OrthographicCameraController.hpp"
// ------------------------------------------------

// ------------ KeyCodes ------------
#include "Engine/Core/MouseCodes.hpp"
#include "Engine/Events/MouseEvent.hpp"
#include "Engine/Events/ApplicationEvent.hpp"
#include "Engine/Events/KeyEvent.hpp"
#include "Engine/Core/KeyCodes.hpp"
// ----------------------------------

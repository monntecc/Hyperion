#pragma once

// For use by Hyperion applications

#include "Runtime/Core/Base.hpp"

#include "Runtime/Core/Application.hpp"
#include "Runtime/Core/Layer.hpp"
#include "Runtime/Core/Log.hpp"
#include "Runtime/Core/Input.hpp"

#include "Runtime/UI/ImGuiLayer.hpp"

#include "Runtime/Core/Timestep.hpp"

// ------------------- Scene -------------------
#include "Runtime/Scene/Scene.hpp"
#include "Runtime/Scene/Components.hpp"
// ------------------------------------------------

// ------------------- Renderer -------------------
#include "Runtime/Renderer/Renderer.hpp"
#include "Runtime/Renderer/Renderer2D.hpp"
#include "Runtime/Renderer/RenderCommand.hpp"

#include "Runtime/Renderer/Buffer.hpp"
#include "Runtime/Renderer/FrameBuffer.hpp"
#include "Runtime/Renderer/Shader.hpp"
#include "Runtime/Renderer/VertexArray.hpp"

#include "Runtime/Renderer/Texture.hpp"

#include "Runtime/Renderer/OrthographicCamera.hpp"
#include "Runtime/Renderer/OrthographicCameraController.hpp"
// ------------------------------------------------

// ------------ KeyCodes ------------
#include "Runtime/Core/MouseCodes.hpp"
#include "Runtime/Events/MouseEvent.hpp"
#include "Runtime/Events/ApplicationEvent.hpp"
#include "Runtime/Events/KeyEvent.hpp"
#include "Runtime/Core/KeyCodes.hpp"
// ----------------------------------

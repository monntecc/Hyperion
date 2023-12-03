#pragma once

#include <glm/glm.hpp>

namespace Hyperion {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		explicit TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		explicit TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}

		explicit operator glm::mat4& () { return Transform; }
		explicit operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		explicit SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

}
#pragma once
#pragma once
#include "Test.h"
#include"../VertexBuffer.h"
#include"../VertexBufferLayout.h"
#include"../Texture.h"
#include"../Shader.h"
#include"../Mesh.h"
#include<memory>

namespace test
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
	};

	class MeshTest : public Test
	{
	public:
		MeshTest();
		~MeshTest();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<Mesh> m_mesh;
		glm::mat4 m_proj;
		glm::vec4 m_color;
		glm::vec3 m_translate;
		glm::vec3 m_rotate;
		glm::vec3 m_scale;
		glm::vec3 m_camera;
		glm::vec3 m_look;
	};
}

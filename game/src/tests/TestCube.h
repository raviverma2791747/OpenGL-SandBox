#pragma once
#include "Test.h"
#include"../VertexBuffer.h"
#include"../VertexBufferLayout.h"
#include"../Texture.h"
#include"../Shader.h"
#include<memory>
 
namespace test
{
	class TestCube : public Test
	{
	public:
		TestCube();
		~TestCube();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexBuffer> m_vb;
		std::unique_ptr<VertexBuffer> m_cb;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<Shader>  m_shader;
		glm::mat4 m_proj;
		glm::vec4 m_color;
		glm::vec3 m_translate;
		glm::vec3 m_rotate;
		glm::vec3 m_scale;
		glm::vec3 m_camera;
		glm::vec3 m_look;
	};
}

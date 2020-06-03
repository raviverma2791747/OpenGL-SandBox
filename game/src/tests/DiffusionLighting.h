#pragma once
#include "Test.h"
#include"../VertexBuffer.h"
#include"../VertexBufferLayout.h"
#include"../Texture.h"
#include"../Shader.h"
#include<memory>

namespace test
{
	class DiffusionLightingCube : public Test
	{
	public:
		DiffusionLightingCube();
		~DiffusionLightingCube();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexArray> m_vaol;
		std::unique_ptr<VertexBuffer> m_vb;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<Shader>  m_shader;
		std::unique_ptr<Shader>  m_shaderl;
		glm::mat4 m_proj;
		glm::vec4 m_colorA;
		glm::vec4 m_colorB;
		glm::vec3 m_translateA;
		glm::vec3 m_translateB;
		glm::vec3 m_rotateA;
		glm::vec3 m_rotateB;
		glm::vec3 m_scaleA;
		glm::vec3 m_scaleB;
		glm::vec3 m_camera;
		glm::vec3 m_look;
	};
}

#include"TestTriangle2D.h"

#include"../Renderer.h"
#include"../vendor/imgui/imgui.h"

#include"../vendor/glm/glm/glm.hpp"
#include"../vendor/glm/glm/gtc/matrix_transform.hpp"

namespace test
{
	TestTriangle2D::TestTriangle2D()
        :
        m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
       // m_Proj(glm::perspective(0.0f,960.0f/540.0f,1.0f,-150.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        m_Translation(0,0,0)
	{
        GLCall(glEnable(GL_BLEND));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();

        float positions[] =
        {
             50.0f,  50.0f,   1.0f, 1.0f, // 0
            200.0f,  50.0f,   1.0f , 1.0f,// 1
            200.0f,  200.0f,  1.0f , 1.0f// 2
        };

        unsigned int indices[] = {
            0, 1, 2
        };
    
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 3 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(4);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 3);

        m_Shader = std::make_unique<Shader>("Res/shaders/TestTriangle2D.shader");
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", glm::vec4( 0.8f, 0.3f, 0.8f, 1.0f ));
	}

	TestTriangle2D::~TestTriangle2D()
	{

	}

	void TestTriangle2D::OnUpdate(float deltaTime)
	{

	}
	void TestTriangle2D::OnRender()
	{
		GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        Renderer renderer;

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
	}

	void TestTriangle2D::OnImGuiRender()
	{
        ImGui::SliderFloat3("Translation", &m_Translation.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
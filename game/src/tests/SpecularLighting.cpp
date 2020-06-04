#include"SpecularLighting.h"

#include"../Renderer.h"
#include"../vendor/imgui/imgui.h"

#include"../vendor/glm/glm/glm.hpp"
#include"../vendor/glm/glm/gtc/matrix_transform.hpp"

namespace test
{
    SpecularLightingCube::SpecularLightingCube() :
        m_proj(glm::perspective(glm::radians(45.0f), (float)960 / 540, 0.1f, 100.0f)),
        m_colorA(1.0f, 0.0f, 0.0f, 1.0f),
        m_translateA(0, 0, 0),
        m_rotateA(0, 0, 0),
        m_scaleA(1, 1, 1),
        m_colorB(1.0f, 1.0f, 1.0f, 1.0f),
        m_translateB(0, 5, 0),
        m_rotateB(0, 0, 0),
        m_scaleB(1, 1, 1),
        m_camera(15, 0, 0),
        m_look(0, 0, 0),
        m_shininess(32)
    {
        GLfloat vertices[] = {
              -1.0f, -1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
               1.0f, -1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
               1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
               1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
              -1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
              -1.0f, -1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,

              -1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
               1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
               1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
               1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
              -1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
              -1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,

              -1.0f,  1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
              -1.0f,  1.0f, -1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
              -1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
              -1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
              -1.0f, -1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
              -1.0f,  1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,

               1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
               1.0f,  1.0f, -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
               1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
               1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
               1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
               1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,

              -1.0f, -1.0f, -1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
               1.0f, -1.0f, -1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
               1.0f, -1.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
               1.0f, -1.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
              -1.0f, -1.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
              -1.0f, -1.0f, -1.0f, 1.0f,  0.0f, -1.0f,  0.0f,

              -1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
               1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
               1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
               1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
              -1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
              -1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));

        m_vao = std::make_unique<VertexArray>();

        m_vb = std::make_unique<VertexBuffer>(vertices, 6 * 6 * 7 * sizeof(GLfloat), 36);
        VertexBufferLayout vbl;
        vbl.Push<float>(4);
        vbl.Push<float>(3);
        m_vao->AddBuffer(*m_vb, vbl);
        m_shader = std::make_unique<Shader>("Res/shaders/SpecularLightingCube.shader");
        m_shader->Bind();

        m_vao->Unbind();
        m_vb->UnBind();
        m_shader->Unbind();

        m_vaol = std::make_unique<VertexArray>();
        m_vaol->AddBuffer(*m_vb, vbl);
        m_shaderl = std::make_unique<Shader>("Res/shaders/LightingCube.shader");
        m_shaderl->Bind();

        m_vaol->Unbind();
        m_vb->UnBind();
        m_shaderl->Unbind();
    }

    SpecularLightingCube::~SpecularLightingCube()
    {

    }

    void  SpecularLightingCube::OnUpdate(float deltaTime)
    {

    }
    void  SpecularLightingCube::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        glm::vec3 lightpos(0.0f, 5.0f, 0.0f);
        Renderer renderer;
        {
            m_vao->Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translateA);
            model = glm::rotate(model, m_rotateA.x, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, m_rotateA.y, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, m_rotateA.z, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, m_scaleA);
            glm::mat4 view = glm::lookAt(m_camera, m_look, glm::vec3(0, 1, 0));
            m_shader->Bind();
            m_shader->SetUniformMat4f("model", model);
            m_shader->SetUniformMat4f("view", view);
            m_shader->SetUniformMat4f("proj", m_proj);
            m_shader->SetUniform4f("cc", m_colorA);
            m_shader->SetUniform3f("lightcolor", m_colorB);
            m_shader->SetUniform3f("lightpos", lightpos);
            m_shader->SetUniform3f("viewpos", m_camera);
            m_shader->SetUniform1f("shininess", m_shininess);
            renderer.Draw(*m_vao, *m_shader, m_vb->GetCount());
            m_vao->Unbind();
        }
        {
            m_vaol->Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translateB);
            model = glm::rotate(model, m_rotateB.x, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, m_rotateB.y, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, m_rotateB.z, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, m_scaleB);
            glm::mat4 view = glm::lookAt(m_camera, m_look, glm::vec3(0, 1, 0));
            glm::mat4 mvp = m_proj * view * model;
            m_shaderl->Bind();
            m_shaderl->SetUniformMat4f("u_MVP", mvp);
            m_shaderl->SetUniform4f("cc", m_colorB);
            renderer.Draw(*m_vaol, *m_shaderl, m_vb->GetCount());
            m_vaol->Unbind();
        }
    }

    void  SpecularLightingCube::OnImGuiRender()
    {
        ImGui::Text("Cube A");
        ImGui::SliderFloat4("A Color", &m_colorA.x, 0.0f, 1.0f);
        ImGui::SliderFloat3("A Translate", &m_translateA.x, -15.0f, 15.0f);
        ImGui::SliderFloat3("A Rotate", &m_rotateA.x, -3.14159f, 3.14159f);
        ImGui::SliderFloat3("A Scale", &m_scaleA.x, 1.0f, 3.0f);
        ImGui::Text("Cube B");
        ImGui::SliderFloat4("B Color", &m_colorB.x, 0.0f, 1.0f);
        ImGui::SliderFloat3("B Translate", &m_translateB.x, -15.0f, 15.0f);
        ImGui::SliderFloat3("B Rotate", &m_rotateB.x, -3.14159f, 3.14159f);
        ImGui::SliderFloat3("B Scale", &m_scaleB.x, 1.0f, 3.0f);
        ImGui::Text("Light Controls");
        ImGui::SliderFloat("Shininess", &m_shininess, 2.0f, 256.0f);
        ImGui::Text("Camera");
        ImGui::SliderFloat3("Camera", &m_camera.x, -15.0f, 15.0f);
        ImGui::SliderFloat3("Look", &m_look.x, -15.0f, 15.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
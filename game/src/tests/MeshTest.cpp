#include"MeshTest.h"

#include"../Renderer.h"
#include"../vendor/imgui/imgui.h"

#include"../vendor/glm/glm/glm.hpp"
#include"../vendor/glm/glm/gtc/matrix_transform.hpp"

#include"assimp/postprocess.h"
#include"assimp/Importer.hpp"
#include"assimp/scene.h"


namespace test
{
    MeshTest::MeshTest() :
        m_color(1,1,1,1),
        m_proj(glm::perspective(glm::radians(45.0f), (float)960 / 540, 0.1f, 100.0f)),
        m_translate(0, 0, 0),
        m_rotate(0, 0, 0),
        m_scale(1, 1, 1),
        m_camera(15, 0, 0),
        m_look(0, 0, 0)
    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));
        m_mesh = std::make_unique<Mesh>("Res/models/male/MaleBodyMesh.obj", "Res/models/male/Male.shader");
    }

    MeshTest::~MeshTest()
    {

    }

    void  MeshTest::OnUpdate(float deltaTime)
    {

    }
    void   MeshTest::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        Renderer renderer;
        {
            m_mesh->m_shader->Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translate);
            model = glm::rotate(model, m_rotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, m_rotate.y, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, m_rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, m_scale);
            glm::mat4 view = glm::lookAt(m_camera, m_look, glm::vec3(0, 1, 0));
            m_mesh->m_shader->SetUniformMat4f("model", model);
            m_mesh->m_shader->SetUniformMat4f("view", view);
            m_mesh->m_shader->SetUniformMat4f("proj", m_proj);
            m_mesh->m_shader->SetUniform4f("u_color", m_color);
            renderer.Draw(*m_mesh->m_vao, *m_mesh->m_ib, *m_mesh->m_shader);
        }
    }

    void   MeshTest::OnImGuiRender()
    {
        ImGui::Text("Mesh ");
        ImGui::SliderFloat3("Translate", &m_translate.x, -15.0f, 15.0f);
        ImGui::SliderFloat3("Rotate", &m_rotate.x, -3.14159f, 3.14159f);
        ImGui::SliderFloat3("Scale", &m_scale.x, 1.0f, 3.0f);
        ImGui::SliderFloat4("Color", &m_color.x, 0.0f, 1.0f);
        ImGui::Text("Camera");
        ImGui::SliderFloat3("Camera", &m_camera.x, -50.0f, 50.0f);
        ImGui::SliderFloat3("Look", &m_look.x, -15.0f, 15.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
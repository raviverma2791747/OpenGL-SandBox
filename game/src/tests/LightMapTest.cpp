#include"LightMapTest.h"

#include"../Renderer.h"
#include"../vendor/imgui/imgui.h"

#include"../vendor/glm/glm/glm.hpp"
#include"../vendor/glm/glm/gtc/matrix_transform.hpp"

namespace test
{
    LightMapTest::LightMapTest() :
        m_proj(glm::perspective(glm::radians(45.0f), (float)960 / 540, 0.1f, 100.0f)),
        m_translate(0, 0, 0),
        m_rotate(0, 0, 0),
        m_scale(1, 1, 1),
        m_camera(15, 0, 0),
        m_look(0, 0, 0),
        m_lightcolor(1.0f,1.0f,1.0f),
        m_shininess(32),
        m_light{ glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.2f, 0.2f, 0.2f),glm::vec3(0.5f, 0.5f, 0.5f),glm::vec3(1.0f, 1.0f, 1.0f) }
    {
        GLfloat vertices[] = {
              -1.0f, -1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
               1.0f, -1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
               1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
               1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
              -1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
              -1.0f, -1.0f, -1.0f, 1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
   
              -1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
               1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
               1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
               1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
              -1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
              -1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         
              -1.0f,  1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
              -1.0f,  1.0f, -1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
              -1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
              -1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
              -1.0f, -1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
              -1.0f,  1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
       
               1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
               1.0f,  1.0f, -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
               1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
               1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
               1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
               1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
      
              -1.0f, -1.0f, -1.0f, 1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
               1.0f, -1.0f, -1.0f, 1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
               1.0f, -1.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
               1.0f, -1.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
              -1.0f, -1.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
              -1.0f, -1.0f, -1.0f, 1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         
              -1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, 
               1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
               1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
               1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
              -1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
              -1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f

        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));

        m_vao = std::make_unique<VertexArray>();

        m_vb = std::make_unique<VertexBuffer>(vertices, 6 * 6 * 9 * sizeof(GLfloat), 36);
        VertexBufferLayout vbl;
        vbl.Push<float>(4);
        vbl.Push<float>(3);
        vbl.Push<float>(2);
        m_vao->AddBuffer(*m_vb, vbl);
        m_shader = std::make_unique<Shader>("Res/shaders/LightMapTest.shader");
        m_shader->Bind();
        m_texture = std::make_unique<Texture2D>("Res/textures/container.png");
        m_texture->Bind();
        m_shader->SetUniform1i("material.diffuse", 0);
        m_spec_texture = std::make_unique<Texture2D>("Res/textures/container_specular.png");
        m_spec_texture->Bind(1);
        m_shader->SetUniform1i("material.specular", 1);
    }

    LightMapTest::~LightMapTest()
    {

    }

    void   LightMapTest::OnUpdate(float deltaTime)
    {

    }
    void   LightMapTest::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        Renderer renderer;
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translate);
            model = glm::rotate(model, m_rotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, m_rotate.y, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, m_rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, m_scale);
            glm::mat4 view = glm::lookAt(m_camera, m_look, glm::vec3(0, 1, 0));
            m_shader->Bind();
            m_shader->SetUniformMat4f("model", model);
            m_shader->SetUniformMat4f("view", view);
            m_shader->SetUniformMat4f("proj", m_proj);
            m_shader->SetUniform3f("viewpos", m_camera);
            m_shader->SetUniform1f("material.shininess", m_shininess);
            m_shader->SetUniform3f("light.position", m_light.position);
            m_shader->SetUniform3f("light.ambient", m_light.ambient );
            m_shader->SetUniform3f("light.diffuse", m_light.diffuse);
            m_shader->SetUniform3f("light.specular", m_light.specular);
            renderer.Draw(*m_vao, *m_shader, m_vb->GetCount());
        }
    }

    void   LightMapTest::OnImGuiRender()
    {
        ImGui::Text("Cube ");
        ImGui::SliderFloat3("Translate", &m_translate.x, -15.0f, 15.0f);
        ImGui::SliderFloat3("Rotate", &m_rotate.x, -3.14159f, 3.14159f);
        ImGui::SliderFloat3("Scale", &m_scale.x, 1.0f, 3.0f);
        ImGui::Text("Material Controls");
        ImGui::SliderFloat("shininess", &m_shininess, 0.0f, 256.0f);
        ImGui::Text("Light Controls");
        ImGui::SliderFloat3("color", &m_lightcolor.x, 0.0f, 1.0f);
        ImGui::SliderFloat3("position", &m_light.position.x, -15.0f, 15.0f);
        ImGui::SliderFloat3("ambient", &m_light.ambient.x, 0.0f, 1.0f);
        ImGui::SliderFloat3("diffuse", &m_light.diffuse.x, 0.0f, 1.0f);
        ImGui::SliderFloat3("specular", &m_light.specular.x, 0.0f, 1.0f);
        ImGui::Text("Camera");
        ImGui::SliderFloat3("Camera", &m_camera.x, -15.0f, 15.0f);
        ImGui::SliderFloat3("Look", &m_look.x, -15.0f, 15.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
#include"TextureCube.h"

#include"../Renderer.h"
#include"../vendor/imgui/imgui.h"

#include"../vendor/glm/glm/glm.hpp"
#include"../vendor/glm/glm/gtc/matrix_transform.hpp"

namespace test
{
    TextureCube::TextureCube() :
        m_proj(glm::perspective(glm::radians(45.0f), (float)960 / 540, 0.1f, 100.0f)),
        m_translate(0, 0, 0),
        m_camera(20, 0, 0),
        m_look(0, 0, 0),
        m_rotate(0, 0, 0),
        m_scale(1, 1, 1)
    {
        GLfloat vertices[] = {
            // front
          -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, //0
           1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 0.0f, //1
           1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, //2
          -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 1.0f, //3
          // back                                
          -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, //4
           1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, //5
           1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 0.0f, //6
          -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, //7

          //fix texture 
          //right
            1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f, //8
            1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, //9
          //left
            -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, //10
            -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, //11 
        };

        GLuint indices[] = {
            // front
             0, 1, 2,
             2, 3, 0,
             // right
             1, 5, 8,
             8, 9, 1,
             // back
             7, 6, 5,
             5, 4, 7,
             // left
             4, 0, 10,
             10, 11, 4,
             // bottom
             4, 5, 1,
             1, 0, 4,
             // top
             3, 2, 6,
             6, 7, 3
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));

        m_vao = std::make_unique<VertexArray>();

        m_vb = std::make_unique<VertexBuffer>(vertices,12*6* sizeof(GLfloat));
        VertexBufferLayout vbl;
        vbl.Push<float>(4);
        vbl.Push<float>(2);
        m_vao->AddBuffer(*m_vb, vbl);

        m_ib = std::make_unique<IndexBuffer>(indices,6*2*3);

        m_shader = std::make_unique<Shader>("Res/shaders/TextureCube.shader");
        m_shader->Bind();

        m_texture = std::make_unique<Texture2D>("Res/textures/gold.jpg");
        m_texture->Bind();
        m_shader->SetUniform1i("u_texture",0); 
    }

    TextureCube::~TextureCube()
    {

    }

    void  TextureCube::OnUpdate(float deltaTime)
    {

    }
    void  TextureCube::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        Renderer renderer;
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translate);
        model = glm::rotate(model, m_rotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, m_rotate.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, m_rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, m_scale);
        glm::mat4 view = glm::lookAt(m_camera, m_look, glm::vec3(0, 1, 0));
        glm::mat4 mvp = m_proj * view * model;
        m_shader->Bind();
        m_shader->SetUniformMat4f("u_MVP", mvp);
        m_texture->Bind();
        renderer.Draw(*m_vao, *m_ib, *m_shader);
    }

    void  TextureCube::OnImGuiRender()
    {
        ImGui::SliderFloat3("Translate", &m_translate.x, -15.0f, 15.0f);
        ImGui::SliderFloat3("Rotate", &m_rotate.x, -3.14159f, 3.14159f);
        ImGui::SliderFloat3("Scale", &m_scale.x,  1.0f, 3.0f);
        ImGui::SliderFloat3("Camera", &m_camera.x, -15.0f, 15.0f);
        ImGui::SliderFloat3("Look", &m_look.x, -15.0f, 15.0f);
        //  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
#include "Render_Manager.hpp"
#include "Graphics_Include.hpp"
#include "Managers.hpp"
#include "Shader.hpp"
#include <cmath>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource1 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "uniform vec4 ourColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = ourColor;\n"
                                    "}\n\0";

bool Render_Manager::Init() {
  std::shared_ptr<Shader> vertexShader = Managers::Shader()->CreateVertexShader(1, &vertexShaderSource, NULL);
  if (vertexShader == nullptr) {
    return false;
  }

  std::shared_ptr<Shader> fragmentShader = Managers::Shader()->CreateFragmentShader(1, &fragmentShaderSource1, NULL);
  if (fragmentShader == nullptr) {
    Managers::Shader()->DeleteShader(vertexShader);
    return false;
  }

  std::shared_ptr<Program> program = Managers::Program()->CreateProgram();
  if (program != nullptr) {
    program->AttachShader(vertexShader);
    program->AttachShader(fragmentShader);
    program->Link();
  }
  Managers::Shader()->DeleteShader(fragmentShader);
  Managers::Shader()->DeleteShader(vertexShader);

  if (program == nullptr) {
    return false;
  }
  if (!program->Getiv(GL_LINK_STATUS)) {
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << program->GetInfoLog() << std::endl;
    Managers::Program()->DeleteProgram(program);
    return false;
  }

  float vertices1[] = {
      -0.8f,
      -0.3f,
      0.0f, // left
      -0.3f,
      -0.3f,
      0.0f, // right
      -0.55f,
      0.2f,
      0.0f, // top
  };

  m_program = program;
  m_colorLocation = m_program->GetUniformLocation("ourColor");
  m_mesh = std::make_unique<Mesh>(vertices1, 3);
  return true;
}

void Render_Manager::Update() const {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  float timeValue = glfwGetTime();
  float greenValue = std::sin(timeValue) / 2.0f + 0.5f;

  m_program->SetUniform4f(m_colorLocation, 0.0f, greenValue, 0.0f, 1.0f);
  m_mesh->Draw();
}

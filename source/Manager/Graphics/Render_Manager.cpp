#include "Render_Manager.hpp"
#include "Graphics_Include.hpp"
#include "Managers.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <memory>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;   // 위치 변수는 위치 0이라는 속성을 가지고 있습니다.\n"
                                 "layout (location = 1) in vec3 aColor; // 색상 변수는 위치 1이라는 속성을 가지고 있습니다.\n"

                                 "out vec3 ourColor; // 프래그먼트 셰이더로 보낼 색\n"
                                 "out vec4 ourPosition; // 위치\n"
                                 "uniform float xOffset;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);\n"
                                 "    ourColor = aColor; // ourColor 변수를 정점 데이터에서 가져온 입력 색상으로 설정합니다.\n"
                                 "    ourPosition = gl_Position;\n"
                                 "}\n";
const char *fragmentShaderSource1 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "in vec3 ourColor;\n"
                                    "in vec4 ourPosition;\n"
                                    "void main()\n"
                                    "{\n"
                                    "    FragColor = ourPosition;\n"
                                    "}\n";

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

  float vertices[] = {
      // positions         // colors
      0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
      -0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
      0.0f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f   // top
  };

  AddMesh(program, std::make_shared<Mesh>(vertices, 3, std::vector<int32>{3, 3}));
  return true;
}

void Render_Manager::AddMesh(std::shared_ptr<Program> _program, std::shared_ptr<Mesh> _mesh) {
  if (_program == nullptr || _mesh == nullptr) {
    return;
  }

  for (RenderBatch &batch : m_batches) {
    if (batch.program == _program) {
      batch.meshes.push_back(_mesh);
      return;
    }
  }
  m_batches.push_back({_program, {_mesh}});
}

void Render_Manager::Update() const {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  float xOffset = std::sin(glfwGetTime() * 2) / 2;

  for (const RenderBatch &batch : m_batches) {
    std::shared_ptr<Program> program = batch.program;
    program->Use();
    program->SetUniform1f(program->GetUniformLocation("xOffset"), xOffset);
    for (const std::shared_ptr<Mesh> &mesh : batch.meshes) {
      mesh->Draw();
    }
  }
}

#include "Render_Manager.hpp"
#include "BMP.hpp"
#include "Graphics_Include.hpp"
#include "Managers.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;   // 위치 변수는 위치 0이라는 속성을 가지고 있습니다.\n"
                                 "layout (location = 1) in vec3 aColor; // 색상 변수는 위치 1이라는 속성을 가지고 있습니다.\n"

                                 "out vec3 ourColor; // 프래그먼트 셰이더로 보낼 색\n"
                                 "layout (location = 2) in vec2 aTexCoord;\n"
                                 "out vec2 TexCoord;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "    ourColor = aColor; // ourColor 변수를 정점 데이터에서 가져온 입력 색상으로 설정합니다.\n"
                                 "    TexCoord = aTexCoord;\n"
                                 "}\n";
const char *fragmentShaderSource1 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "in vec3 ourColor;\n"
                                    "in vec2 TexCoord;\n"
                                    "uniform sampler2D ourTexture;\n"
                                    "void main()\n"
                                    "{\n"
                                    "    FragColor = texture(ourTexture, TexCoord);\n"
                                    "}\n";

static const char *tempTexturePath = "Resources/Image/TangTang.bmp";

bool Render_Manager::Init() { return true; }

bool Render_Manager::InitScene() {
  Managers::File()->ReadFile(tempTexturePath);
  if (!Managers::Texture()->Create(tempTexturePath)) {
    return false;
  }

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
      // positions         // colors         // uv
      0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 1.0f, // 우측위
      0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,  // 우측 아래
      0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 좌측 아래
      0.0f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // 좌측 위
      0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 1.0f, // 우측 위
      0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f   // 좌측 아래
  };

  AddMesh(program, std::make_shared<Mesh>(vertices, 6, std::vector<int32>{3, 3, 2}));
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

  Managers::Texture()->Bind();

  for (const RenderBatch &batch : m_batches) {
    std::shared_ptr<Program> program = batch.program;
    program->Use();
    for (const std::shared_ptr<Mesh> &mesh : batch.meshes) {
      mesh->Draw();
    }
  }
}

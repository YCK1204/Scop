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
                                 "uniform float xOffset;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);\n"
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
static uint32 tempTexture = 0;

/**
 * @brief 임시 코드. tempTexturePath의 BMP를 읽어 tempTexture에 2D 텍스처로 올린다.
 * 텍스처 클래스가 생기면 그쪽으로 옮기고 지울 것. 텍스처를 삭제하지 않는다
 * @return 파일을 읽고 텍스처를 만들었으면 true
 */
static bool LoadTempTexture() {
  std::ifstream file;
  const std::string *fileStr = nullptr;
  BMP bmp;

  Managers::File()->ReadAndSetFileStr(tempTexturePath, file);
  if (!Managers::File()->TryGetFileStr(tempTexturePath, fileStr) || !bmp.Read(*fileStr)) {
    std::cout << "ERROR::TEXTURE::LOAD_FAILED " << tempTexturePath << std::endl;
    return false;
  }

  glGenTextures(1, &tempTexture);
  glBindTexture(GL_TEXTURE_2D, tempTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.GetWidth(), bmp.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, bmp.GetPixels());
  return true;
}

bool Render_Manager::Init() {
  if (!LoadTempTexture()) {
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
      0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // bottom right
      -0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // bottom left
      0.0f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f   // top
  };

  AddMesh(program, std::make_shared<Mesh>(vertices, 3, std::vector<int32>{3, 3, 2}));
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

  glBindTexture(GL_TEXTURE_2D, tempTexture);

  for (const RenderBatch &batch : m_batches) {
    std::shared_ptr<Program> program = batch.program;
    program->Use();
    program->SetUniform1f(program->GetUniformLocation("xOffset"), xOffset);
    for (const std::shared_ptr<Mesh> &mesh : batch.meshes) {
      mesh->Draw();
    }
  }
}

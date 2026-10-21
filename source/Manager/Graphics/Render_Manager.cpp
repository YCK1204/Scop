#include "Render_Manager.hpp"
#include "BMP.hpp"
#include "Graphics_Include.hpp"
#include "Managers.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include "Utils/ShaderSourceBuilder.hpp"
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

  std::shared_ptr<Shader> vertexShader = Managers::Shader()->CreateVertexShader();
  if (vertexShader == nullptr) {
    return false;
  }

  std::shared_ptr<Shader> fragmentShader = Managers::Shader()->CreateFragmentShader();
  if (fragmentShader == nullptr) {
    Managers::Shader()->DeleteShader(vertexShader);
    return false;
  }
  ShaderSourceBuilder vertexBuilder;
  vertexBuilder.H_AddLayout(0, "vec3", "aPos")
                              .H_AddLayout(1, "vec3", "aColor")
                              .H_AddLayout(2, "vec2", "aTexCoord")
                              .H_AddUniform("vec3", "OffsetPosition")
                              .H_AddOut("vec2", "TexCoord")
                              .M_AddSetVar("gl_Position", "vec4(aPos + OffsetPosition, 1.0)")
                              .M_AddSetVar("TexCoord", "aTexCoord");
  std::string vertexSrc = vertexBuilder.Build();

  ShaderSourceBuilder fragmentBuilder;
  fragmentBuilder.H_AddOut("vec4", "FragColor")
                                .H_AddIn("vec2", "TexCoord")
                                .H_AddUniform("sampler2D", "ourTexture")
                                .M_AddSetVar("FragColor", "texture(ourTexture, TexCoord)");
  std::string fragmentSrc = fragmentBuilder.Build();

  std::shared_ptr<Program> program = Managers::Program()->CreateProgram();
  vertexShader->Compile(vertexSrc);
  fragmentShader->Compile(fragmentSrc);
  if (program != nullptr && vertexShader->IsCompiled() && fragmentShader->IsCompiled()) {
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
  program->RegisterUniforms(vertexBuilder.GetUniforms());
  program->RegisterUniforms(fragmentBuilder.GetUniforms());

  float vertices[] = {
      // positions         // colors         // uv
      0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 1.0f, // 우측위
      0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,  // 우측 아래
      0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 좌측 아래
      0.0f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // 좌측 위
      0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 1.0f, // 우측 위
      0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f   // 좌측 아래
  };

  std::shared_ptr<Object> quad = std::make_shared<Object>("quad");
  quad->SetMesh(std::make_shared<Mesh>(vertices, 6, std::vector<int32>{3, 3, 2}));
  Managers::Objects()->SetObject(quad);
  quad->SetProgram(program);
  quad->SetUniform("OffsetPosition", Vec3(-0.125f, -0.125f, 0.0f));
  return true;
}

void Render_Manager::Update() const {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  Managers::Texture()->Bind();

  std::shared_ptr<Object> quad = Managers::Objects()->GetObject("quad");
  if (quad != nullptr) {
    float xOffset = std::sin(glfwGetTime() * 2) / 2;
    quad->SetUniform("OffsetPosition", Vec3(xOffset - 0.125f, -0.125f, 0.0f));
  }

  for (const auto &[id, program] : Managers::Program()->GetPrograms()) {
    program->DrawObjects();
  }
}

#include "Render_Manager.hpp"
#include "BMP.hpp"
#include "Graphics_Include.hpp"
#include "Managers.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include "Utils/ShaderSourceBuilder.hpp"
#include <GLFW/glfw3.h>
#include <algorithm>
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

/**
 * @brief 임시: B키로 바꾸는 WASD 조작 대상
 */
enum class Control_Mode : uint8 {
  NONE,
  POSITION,
  SCALE,
  ROTATION,
  MAX
};

static Control_Mode s_controlMode = Control_Mode::NONE;
static float s_deltaTime = 0.0f;

static const float POSITION_SPEED = 1.0f;
static const float SCALE_SPEED = 1.0f;
static const float ROTATION_SPEED = 2.0f;
static const float MIN_SCALE = 0.1f;

static const char *ControlModeName(Control_Mode _mode) {
  switch (_mode) {
  case Control_Mode::POSITION:
    return "POSITION";
  case Control_Mode::SCALE:
    return "SCALE";
  case Control_Mode::ROTATION:
    return "ROTATION";
  default:
    return "NONE";
  }
}

static void OnToggleControlMode() {
  uint8 next = (static_cast<uint8>(s_controlMode) + 1) % static_cast<uint8>(Control_Mode::MAX);

  s_controlMode = static_cast<Control_Mode>(next);
  std::cout << "Control mode: " << ControlModeName(s_controlMode) << std::endl;
}

/**
 * @brief 현재 모드에 맞춰 quad의 Transform을 바꾼다
 * @param _x A/D 입력 방향 (-1, 0, 1)
 * @param _y W/S 입력 방향 (-1, 0, 1)
 */
static void ApplyControl(float _x, float _y) {
  std::shared_ptr<Object> quad = Managers::Objects()->GetObject("quad");
  if (quad == nullptr) {
    return;
  }

  std::shared_ptr<Transform> transform = quad->GetTransform();
  if (s_controlMode == Control_Mode::POSITION) {
    float step = POSITION_SPEED * s_deltaTime;
    transform->SetPosition(transform->GetPosition() + Vec3(_x * step, _y * step, 0.0f));
  } else if (s_controlMode == Control_Mode::SCALE) {
    float step = SCALE_SPEED * s_deltaTime;
    Vec3 scale = transform->GetScale() + Vec3(_x * step, _y * step, 0.0f);
    scale.x = std::max(scale.x, MIN_SCALE);
    scale.y = std::max(scale.y, MIN_SCALE);
    transform->SetScale(scale);
  } else if (s_controlMode == Control_Mode::ROTATION) {
    float step = ROTATION_SPEED * s_deltaTime;
    transform->SetRotation(transform->GetRotation() + Vec3(-_y * step, _x * step, 0.0f));
  }
}

static void OnHoldW() { ApplyControl(0.0f, 1.0f); }
static void OnHoldS() { ApplyControl(0.0f, -1.0f); }
static void OnHoldA() { ApplyControl(-1.0f, 0.0f); }
static void OnHoldD() { ApplyControl(1.0f, 0.0f); }

static void RegisterControlCallbacks() {
  Managers::Input()->AddCallback(Input_Type::INPUT_PRESS, Key::B, OnToggleControlMode);
  Managers::Input()->AddCallback(Input_Type::INPUT_HOLD, Key::W, OnHoldW);
  Managers::Input()->AddCallback(Input_Type::INPUT_HOLD, Key::S, OnHoldS);
  Managers::Input()->AddCallback(Input_Type::INPUT_HOLD, Key::A, OnHoldA);
  Managers::Input()->AddCallback(Input_Type::INPUT_HOLD, Key::D, OnHoldD);
}

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
                              .H_AddUniform("mat4", "Model")
                              .H_AddOut("vec2", "TexCoord")
                              .M_AddSetVar("gl_Position", "Model * vec4(aPos, 1.0)")
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
      0.125f, 0.125f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 1.0f,   // 우측위
      0.125f, -0.125f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,  // 우측 아래
      -0.125f, -0.125f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 좌측 아래
      -0.125f, 0.125f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // 좌측 위
      0.125f, 0.125f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 1.0f,   // 우측 위
      -0.125f, -0.125f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f  // 좌측 아래
  };

  std::shared_ptr<Object> quad = std::make_shared<Object>("quad");
  quad->SetMesh(std::make_shared<Mesh>(vertices, 6, std::vector<int32>{3, 3, 2}));
  Managers::Objects()->SetObject(quad);
  quad->SetProgram(program);
  quad->SetUniform("Model", quad->GetTransform()->GetModelMatrix());
  RegisterControlCallbacks();
  return true;
}

void Render_Manager::Update() const {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  Managers::Texture()->Bind();

  static double lastTime = glfwGetTime();
  double now = glfwGetTime();
  s_deltaTime = static_cast<float>(now - lastTime);
  lastTime = now;

  std::shared_ptr<Object> quad = Managers::Objects()->GetObject("quad");
  if (quad != nullptr) {
    quad->SetUniform("Model", quad->GetTransform()->GetModelMatrix());
  }

  for (const auto &[id, program] : Managers::Program()->GetPrograms()) {
    program->DrawObjects();
  }
}

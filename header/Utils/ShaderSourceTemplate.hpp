#pragma once
#include <memory>
#include <string>

// const char *vertexShaderSource = "#version 330 core\n"
//                                  "layout (location = 0) in vec3 aPos;   // 위치 변수는 위치 0이라는 속성을 가지고 있습니다.\n"
//                                  "layout (location = 1) in vec3 aColor; // 색상 변수는 위치 1이라는 속성을 가지고 있습니다.\n"

//                                  "out vec3 ourColor; // 프래그먼트 셰이더로 보낼 색\n"
//                                  "layout (location = 2) in vec2 aTexCoord;\n"
//                                  "out vec2 TexCoord;\n"
//                                  "void main()\n"
//                                  "{\n"
//                                  "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//                                  "    ourColor = aColor; // ourColor 변수를 정점 데이터에서 가져온 입력 색상으로 설정합니다.\n"
//                                  "    TexCoord = aTexCoord;\n"
//                                  "}\n";
// const char *fragmentShaderSource1 = "#version 330 core\n"
//                                     "out vec4 FragColor;\n"
//                                     "in vec3 ourColor;\n"
//                                     "in vec2 TexCoord;\n"
//                                     "uniform sampler2D ourTexture;\n"
//                                     "void main()\n"
//                                     "{\n"
//                                     "    FragColor = texture(ourTexture, TexCoord);\n"
//                                     "}\n";

struct ShaderSourceTemplate {

public:
  struct Header {
  public:
    static constexpr const char* Layout = "layout (location = {0}) in {1} {2};\n"; // 0: location id, 1: 자료형, 2: 변수명
    static constexpr const char* OutVar = "out {0} {1};\n";                                         // 0: 자료형, 1: 변수명
    static constexpr const char* InVar = "in {0} {1};\n";                                           // 0: 자료형, 1: 변수명
    static constexpr const char* UniformVar = "uniform {0} {1};\n";                                 // 0: 자료형, 1: 변수명
  };

public:
  struct Main {
  public:
    static constexpr const char* Base = "void main()\n"
                       "{\n"
                       "    {0}\n"
                       "}\n";
    static constexpr const char* SetVar = "{0} = {1};\n";
    static constexpr const char* AddVar = "{0} += {1};\n";
    static constexpr const char* SubVar = "{0} -= {1};\n";
    static constexpr const char* MulVar = "{0} *= {1};\n";
    static constexpr const char* DivVar = "{0} /= {1};\n";
    static constexpr const char* ModVar = "{0} %= {1};\n";
  };

public:
  static constexpr const char* Base = "#version 330 core\n"
                     "{0}\n"  // header
                     "{1}\n"; // main
};
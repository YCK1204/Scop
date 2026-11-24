#pragma once

#include "Define.hpp"
#include "Utils/Mat4.hpp"
#include "Utils/Vec3.hpp"
#include <string>
#include <variant>

/**
 * @brief 쉐이더에 선언한 유니폼 하나. ShaderSourceBuilder::H_AddUniform이 기록하고 Program::RegisterUniforms가 받는다
 */
struct UniformDecl {
  std::string type;
  std::string name;
};

/**
 * @brief 유니폼에 넣을 값. GLSL 자료형 float, int(sampler 포함), vec3, mat4에 대응한다
 */
using UniformValue = std::variant<float, int32, Vec3, Mat4>;

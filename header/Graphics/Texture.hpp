#pragma once

#include "Define.hpp"
class Texture {
private:
  uint32 m_id;

private:
  Texture();

public:
  Texture(const uint32 &_id);
  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;
  const uint32 &GetId() const;
};
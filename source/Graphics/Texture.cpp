#include "Texture.hpp"
Texture::Texture(const uint32 &_id) : m_id(_id) {}
const uint32 &Texture::GetId() const { return m_id; }

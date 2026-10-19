#include "TextureManager.hpp"
#include "BMP.hpp"
#include "Graphics_Include.hpp"
#include "Managers.hpp"
#include "Texture.hpp"
#include <iostream>
#include <memory>
#include <string>

bool TextureManager::Init() { return true; }

std::shared_ptr<Texture> TextureManager::Create(const std::string &_imageFileName) {
  uint32 id = 0;
  std::shared_ptr<Texture> texture = nullptr;
  const std::string *fileStr;
  BMP bmp;

  if (!Managers::File()->TryGetFileStr(_imageFileName, fileStr) || !bmp.Read(*fileStr)) {
    std::cout << "ERROR::TEXTURE::LOAD_FAILED " << _imageFileName << std::endl;
    return texture;
  }

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.GetWidth(), bmp.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, bmp.GetPixels());
  texture = std::make_shared<Texture>(id);
  m_textures[id] = texture;
  return texture;
}
void TextureManager::GenerateMipmap() const { glGenerateMipmap(GL_TEXTURE_2D); }

std::shared_ptr<Texture> TextureManager::GetTexture(uint32 _id) const {
  std::map<uint32, std::shared_ptr<Texture>>::const_iterator it = m_textures.find(_id);
  if (it == m_textures.end()) {
    return nullptr;
  }
  return it->second;
}

void TextureManager::DeleteTexture(uint32 _id) {
  glDeleteTextures(1, &_id);
}
void TextureManager::Bind() const {
  for (auto it : m_textures) {
    glBindTexture(GL_TEXTURE_2D, it.second->GetId());
  }
}
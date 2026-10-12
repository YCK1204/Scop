#pragma once

#include "Define.hpp"
#include "Singleton.hpp"
#include "Texture.hpp"
#include <map>
#include <memory>
class TextureManager : public Singleton<TextureManager> {
private:
  std::map<uint32, std::shared_ptr<Texture>> m_textures;

public:
  std::shared_ptr<Texture> Create(const std::string& _imageFileName);
  void GenerateMipmap() const;
  std::shared_ptr<Texture> GetTexture(uint32 _id) const;
  void DeleteTexture(uint32 _id);
  void Bind() const;
};
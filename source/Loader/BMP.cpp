#include "Loader/BMP.hpp"
#include <iostream>
#include <memory>
#include <sstream>

BMP::BMP() : m_pixels(nullptr) {
}

bool BMP::Read(const std::string &_fileStr) {
  if (_fileStr.empty())
    return false;

  uint16 fileHeaderSize = sizeof(BITMAPFILEHEADER);
  uint16 infoHeaderSize = sizeof(BITMAPINFOHEADER);

  std::stringstream ss(_fileStr);

  ss.read((char *)&m_bmpHeader, fileHeaderSize);
  ss.read((char *)&m_bmpInfo, infoHeaderSize);

  if (ss.fail())
    return false;
  if (m_bmpHeader.bfType != 0x4D42) {
    std::cout << "File isn't a bitmap file\n";
    return false;
  }
  if (m_bmpInfo.biBitCount != 24 || m_bmpInfo.biCompression != 0) {
    std::cout << "File isn't 24 bit\n";
    return false;
  }

  m_pixels = std::make_unique<uint8[]>(m_bmpInfo.biSizeImage);

  ss.seekg(m_bmpHeader.bfOffBits);
  ss.read((char *)m_pixels.get(), m_bmpInfo.biSizeImage);
  uint8 tmpRGB = 0; 
  for (unsigned long i = 0; i < m_bmpInfo.biSizeImage; i += 3) {
    tmpRGB = m_pixels[i];
    m_pixels[i] = m_pixels[i + 2];
    m_pixels[i + 2] = tmpRGB;
  }

  return true;
}
const uint32 &BMP::GetWidth() const { return m_bmpInfo.biWidth; }
const uint32 &BMP::GetHeight() const { return m_bmpInfo.biHeight; }
const uint8 *BMP::GetPixels() const { return m_pixels.get(); }
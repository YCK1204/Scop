#pragma once
#include "Define.hpp"
#include <memory>
#include <string>

#pragma pack(push, 1)
typedef struct tagBITMAPINFOHEADER {
  uint32 biSize;
  uint32 biWidth;
  uint32 biHeight;
  uint16 biPlanes;
  uint16 biBitCount;
  uint32 biCompression;
  uint32 biSizeImage;
  int32 biXPelsPerMeter;
  int32 biYPelsPerMeter;
  uint32 biClrUsed;
  uint32 biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER {
  uint16 bfType;
  uint32 bfSize;
  uint16 bfReserved1;
  uint16 bfReserved2;
  uint32 bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;
#pragma pack(pop)
class BMP {
private:
  BITMAPFILEHEADER m_bmpHeader;
  BITMAPINFOHEADER m_bmpInfo;
  std::unique_ptr<uint8[]> m_pixels;

public:
  BMP();
  BMP(const BMP &) = delete;
  BMP &operator=(const BMP &) = delete;

public:
  bool Read(const std::string &_fileStr);
  const uint32 &GetWidth() const;
  const uint32 &GetHeight() const;
  const uint8* GetPixels() const;
};
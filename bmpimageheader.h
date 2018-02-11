#ifndef BMPIMAGEHEADER_H
#define BMPIMAGEHEADER_H

#include <cstdint>
#include <cstring>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef uint32_t DWORD;


class BmpImageHeader
{
public:
    BmpImageHeader();
    BmpImageHeader(char*);
    void setImageHeader(char *);
    DWORD getWidth();
    DWORD getHeight();
    WORD getBitCount();
    void getAllHeader(unsigned char *);
    void setBiBitCount(const WORD &value);
    DWORD getBiSizeImage() const;

private:
    DWORD biSize;
    DWORD biWidth;
    DWORD biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    DWORD biXPelsPerMeter;
    DWORD biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
};

#endif // BMPIMAGEHEADER_H
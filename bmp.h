#ifndef BMP_H
#define BMP_H

typedef unsigned char uchar;
typedef unsigned int  uint;

typedef struct RGBApixel {
    uchar Blue;
    uchar Green;
    uchar Red;
    uchar Alpha;
} RGBApixel;

#pragma pack(push,1)

typedef struct BMPH {
    short bfType;
    uint  bfSize;
    short bfReserved1;
    short bfReserved2;
    uint  bfOffBits;

    uint  biSize;
    uint  biWidth;
    uint  biHeight;
    short biPlanes;
    short biBitCount;
    uint  biCompression;
    uint  biSizeImage;
    uint  biXPelsPerMeter;
    uint  biYPelsPerMeter;
    uint  biClrUsed;
    uint  biClrImportant;
} BMPH;

#pragma pack(pop)

class BMP
{
public:
    RGBApixel** pixels;
    BMPH header;

    BMP();
    ~BMP();
    bool readFromFile(char* filename);
    bool writeToFile(char* filename);
    RGBApixel getPixel(int x, int y);
    void setPixel(int x, int y, RGBApixel pixel);
    BMP operator=(BMP copy);
};

#endif // BMP_H

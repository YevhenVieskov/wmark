
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "bmp.h"




BMP::BMP()
{
    this->pixels = NULL;

}

BMP::~BMP()
{
    int width = this->header.biWidth;
    if (this->pixels == NULL) return;
    for (int i = 0; i < width; i++)
        delete [] this->pixels[i];
    delete [] this->pixels;
    this->pixels = 0;
}

bool BMP::readFromFile(char*filename)
{
    using namespace std;

    char bitCount;
    int width;
    int height;
    int colSize;

    char* buffer;

    ifstream input(filename, ios::in | ios::binary);
    input.read((char*) &(this->header), 54);
    input.seekg(this->header.bfOffBits, ios_base::beg);

    bitCount = this->header.biBitCount;
    width = this->header.biWidth;
    height = this->header.biHeight;

    colSize = ((width*bitCount)/8.0);

    while (8*colSize < width*bitCount) {
        colSize++;
    }

    while (colSize % 4) {
        colSize++;
    }

    this->pixels = new RGBApixel*[width];
    buffer = new char[colSize];
    for (int i = 0; i < width; i++)
        this->pixels[i] = new RGBApixel[height];

    for (int i = height-1; i >= 0; i--) {
        input.read(buffer, colSize);
        for (int j = 0; j < width; j++) {
            if (bitCount == 24) {
                memcpy((char*) &(pixels[j][i]), buffer + 3*j, 3);
            } else if (bitCount == 32) {
                memcpy((char*) &(pixels[j][i]), buffer + 4*j, 4);
            } else {
                return false;
            }
        }
    }
    return true;
}

bool BMP::writeToFile(char *filename)
{
    using namespace std;

    char bitCount;
    int width;
    int height;
    int colSize;

    char* buffer;

    ofstream output(filename, ios::out | ios::binary);
    output.write((char*)&(this->header), this->header.bfOffBits);

    bitCount = this->header.biBitCount;
    width = this->header.biWidth;
    height = this->header.biHeight;

    colSize = ((width*bitCount)/8.0);

    while (8*colSize < width*bitCount) {
        colSize++;
    }

    while (colSize % 4) {
        colSize++;
    }
    buffer = new char[colSize];

    for (int i = height-1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            if (bitCount == 24) {
                memcpy(buffer+3*j, (char*)&(this->pixels[j][i]), 3);
            } else if (bitCount == 32) {
                memcpy(buffer+4*j,(char*)&(this->pixels[j][i]), 4);
            } else {
                return false;
            }

        }
        output.write(buffer, colSize);
    }
    return true;
}

RGBApixel BMP::getPixel(int x, int y)
{
    return this->pixels[x][y];
}

void BMP::setPixel(int x, int y, RGBApixel pixel)
{
    this->pixels[x][y] = pixel;
}

BMP BMP::operator =(BMP copy)
{
	char bitCount;
	int width;
	int height;
	int colSize;

	if (pixels != NULL) {
		for (int i = 0; i < this->header.biHeight; i++)
			delete[] this->pixels[i];
		delete[] this->pixels;
	}
	this->header = copy.header;
	bitCount = this->header.biBitCount;
	width = this->header.biWidth;
	height = this->header.biHeight;

	colSize = ((width*bitCount) / 8.0);

	while (8 * colSize < width*bitCount) {
		colSize++;
	}
	while (colSize % 4) {
		colSize++;
	}

	this->pixels = new RGBApixel*[width];
	for (int i = 0; i < width; i++)
		this->pixels[i] = new RGBApixel[height];

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			this->pixels[i][j].Blue = copy.pixels[i][j].Blue;
			this->pixels[i][j].Green = copy.pixels[i][j].Green;
			this->pixels[i][j].Red = copy.pixels[i][j].Red;
		}
	}
	return *this;
}
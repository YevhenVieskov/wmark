

#include <cstring>
#include <cmath>
#include "stdafx.h"
#include "stegokoch.h"




#define FIRST 3][4
#define SECOND 4][3

StegoKoch::StegoKoch(char* inputFilename, char* outputFilename,char* inputMessage)
{
    this->readOnly = false;
    this->Input.readFromFile(inputFilename);
    this->message.putString(inputMessage, strlen(inputMessage));
    this->inputFilename = inputFilename;
    this->outputFilename = outputFilename;
    this->insertMessage();
    this->Input.writeToFile(outputFilename);
}

StegoKoch::StegoKoch(char* inputFilename)
{
    this->readOnly = true;
    this->inputFilename = inputFilename;
    this->Input.readFromFile(inputFilename);
    this->readMessage();
}

void StegoKoch::insertMessage()
{
    if (this->readOnly)
        return;
    double** dct;
    RGBApixel** temp;
    double k = 0;
    int l = 0;

    dct = new double*[8];
    temp = new RGBApixel*[8];
    for (int i = 0; i < 8; i++) {
        dct[i] = new double[8];
        temp[i] = new RGBApixel[8];
    }
    for (int i = 0; i+8 < this->Input.header.biHeight; i += 8) {
        for (int j = 0; j+8 < this->Input.header.biWidth; j += 8) {
            if (l >= this->message.getLenght())
                break;

            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    temp[x][y].Alpha = this->Input.pixels[j+x][i+y].Alpha;
                    temp[x][y].Red = this->Input.pixels[j+x][i+y].Red;
                    temp[x][y].Green = this->Input.pixels[j+x][i+y].Green;
                    temp[x][y].Blue = this->Input.pixels[j+x][i+y].Blue;
                }
            }

            this->dct(dct, temp);
            k = fabs(dct[FIRST]) - fabs(dct[SECOND]);
            if (this->message.getBit(l)) {
                if (k <= 25) {
                    dct[FIRST] = (dct[FIRST] >= 0) ?
                                  fabs(dct[SECOND]) + 150 :
                              -1*(fabs(dct[SECOND]) + 150);
                }
            } else {
                if (k >= -25) {
                    dct[SECOND] = (dct[SECOND] >= 0) ?
                                   fabs(dct[FIRST]) + 150 :
                               -1*(fabs(dct[FIRST]) + 150);
                }
            }
            this->idct(dct, temp);
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    this->Input.pixels[j+x][i+y].Alpha = temp[x][y].Alpha;
                    this->Input.pixels[j+x][i+y].Red = temp[x][y].Red;
                    this->Input.pixels[j+x][i+y].Green = temp[x][y].Green;
                    this->Input.pixels[j+x][i+y].Blue = temp[x][y].Blue;
                }
            }
            l++;
        }
        if (l >= this->message.getLenght())
            break;
    }



    for (int i = 0; i < 8; i++) {
        delete [] dct[i];
        delete [] temp[i];
    }

    delete [] dct;
    delete [] temp;
}

void StegoKoch::readMessage()
{
    double** dct;
    RGBApixel** temp;
    double k = 0;
    int l = 0;
    char a;
    uchar b = 0,p = 0;

    dct = new double*[8];
    temp = new RGBApixel*[8];
    for (int i = 0; i < 8; i++) {
        dct[i] = new double[8];
        temp[i] = new RGBApixel[8];
    }
    this->outMes_s.clear();
    for (int i = 0; i+8 < this->Input.header.biHeight; i += 8) {
        for (int j = 0; j+8 < this->Input.header.biWidth; j += 8) {
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    temp[x][y].Alpha = this->Input.pixels[j+x][i+y].Alpha;
                    temp[x][y].Red = this->Input.pixels[j+x][i+y].Red;
                    temp[x][y].Green = this->Input.pixels[j+x][i+y].Green;
                    temp[x][y].Blue = this->Input.pixels[j+x][i+y].Blue;
                }
            }
            l++;
            this->dct(dct, temp);
            k = fabs(dct[FIRST]) - fabs(dct[SECOND]);
            if (k >= 25) {
                a = 1;
            } else if (k <= -25) {
                a = 0;
            } else {
                a = -1;
                break;
            }

            b |= a << p;
            if (p == 7) {
                this->outMes_s.push_back(b);
                b = 0;
            }
            p = (p < 7) ? p + 1 : 0;


        }
        if (a == -1)
            break;
    }

 //   qDebug() << l;

    for (int i = 0; i < 8; i++) {
        delete [] dct[i];
        delete [] temp[i];
    }
    delete [] dct;
    delete [] temp;
}

double cos_t[][8] = { {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                      {0.9807853, 0.8314696, 0.5555702, 0.1950903,
                      -0.1950903,-0.5555702,-0.8314696,-0.9807853},
                      {0.9238795, 0.3826834,-0.3826834,-0.9238795,
                      -0.9238795,-0.3826834, 0.3826834, 0.9238795},
                      {0.8314696,-0.1950903,-0.9807853,-0.5555702,
                       0.5555702, 0.9807853, 0.1950903,-0.8314696},
                      {0.7071068,-0.7071068,-0.7071068, 0.7071068,
                       0.7071068,-0.7071068,-0.7071068, 0.7071068},
                      {0.5555702,-0.9807853, 0.1950903, 0.8314696,
                      -0.8314696,-0.1950903, 0.9807853,-0.5555702},
                      {0.3826834,-0.9238795, 0.9238795,-0.3826834,
                      -0.3826834, 0.9238795,-0.9238795, 0.3826834},
                      {0.1950903,-0.5555702, 0.8314696,-0.9807853,
                       0.9807853,-0.8314696, 0.5555702,-0.1950903} };

double e[][8] = { {0.125, 0.176777777, 0.176777777, 0.176777777,
                   0.176777777, 0.176777777, 0.176777777, 0.176777777},
                  {0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25},
                  {0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25},
                  {0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25},
                  {0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25},
                  {0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25},
                  {0.176777777, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25} };

void StegoKoch::dct(double **dct, RGBApixel **quad)
{
    double temp;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            temp = 0;
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    temp += cos_t[i][x]*cos_t[j][y]*quad[x][y].Blue;
                }
            }
            dct[i][j] = e[i][j]*temp;
        }
    }
}

void StegoKoch::idct(double **dct, RGBApixel **quad)
{
    double temp;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            temp = 0;
            for (int x = 0; x < 8; x++)
                for (int y = 0; y < 8; y++)
                    temp += dct[x][y]*cos_t[x][i]*cos_t[y][j]*e[x][y];
            quad[i][j].Blue = (temp > 255) ? 255 :
                                               (temp < 0) ? 0 :
                                                            (uchar)ceil(temp);
        }
}

bool StegoKoch::isForReadOnly()
{
    return this->readOnly;
}

#ifndef STEGOKOCH_H
#define STEGOKOCH_H

#include "bmp.h"
#include "bitmessage.h"

#include <string>

using std::string;

class StegoKoch
{
    BMP Input;
    BitMessage message;
    bool readOnly;
	char* inputFilename;
	char* outputFilename;
public:
    string outMes_s;
	StegoKoch(char* inputFilename, char* outputFilename, char* inputMessage);
	StegoKoch(char* inputFilename);
    BitMessage getMessage();
    void dct(double** dct, RGBApixel** quad);
    void idct(double** dct, RGBApixel** quad);
    void insertMessage();
    void readMessage();
    bool isForReadOnly();
};

#endif // STEGOKOCH_H

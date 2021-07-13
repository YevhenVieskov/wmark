#ifndef BITMESSAGE_H
#define BITMESSAGE_H

typedef unsigned int uint;
typedef unsigned char uchar;

#include <vector>

using std::vector;

class BitMessage
{
    vector<char> message_v;
    uint curPos;
public:
    BitMessage();
    bool getNextBit();
    bool getBit(uint pos);
    void putBit(bool bit);
	void putString(char* string, int len);
    int getLenght();
};

#endif // BITMESSAGE_H

#include "stdafx.h"
#include "bitmessage.h"

BitMessage::BitMessage()
{
    this->curPos = 0;
    this->message_v.clear();
}

bool BitMessage::getBit(uint pos)
{
    return (bool)(this->message_v[pos/8] & (1 << pos%8));
}

void BitMessage::putString(char *string, int len)
{
    for (int i = 0; i < len; i++) {
        this->message_v.push_back(string[i]);
    }

}

int BitMessage::getLenght()
{
    return this->message_v.size()*8;
}

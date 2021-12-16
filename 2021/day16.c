#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

const char* packet0 = "D2FE28";
const char* packet1 = "38006F45291200";
const char* packet2 = "EE00D40C823060";
const char* packet3 = "8A004A801A8002F478";
const char* packet4 = "620080001611562C8802118E34";
const char* packet5 = "C0015000016115A2E0802F182340";
const char* packet6 = "A0016C880162017C3686B18A3D4780";
const char* packet7 = "C200B40A82";
const char* packet8 = "04005AC33890";
const char* packet9 = "880086C3E88112";
const char* packet10 = "CE00C43D881120";
const char* packet11 = "D8005AC2A8F0";
const char* packet12 = "F600BC2D8F";
const char* packet13 = "9C005AC2F8F0";
const char* packet14 = "9C0141080250320F1802104A08";
const char* packet15 = "005473C9244483004B001F79A9CE75FF9065446725685F1223600542661B7A9F4D001428C01D8C30C61210021F0663043A20042616C75868800BAC9CB59F4BC3A40232680220008542D89B114401886F1EA2DCF16CFE3BE6281060104B00C9994B83C13200AD3C0169B85FA7D3BE0A91356004824A32E6C94803A1D005E6701B2B49D76A1257EC7310C2015E7C0151006E0843F8D000086C4284910A47518CF7DD04380553C2F2D4BFEE67350DE2C9331FEFAFAD24CB282004F328C73F4E8B49C34AF094802B2B004E76762F9D9D8BA500653EEA4016CD802126B72D8F004C5F9975200C924B5065C00686467E58919F960C017F00466BB3B6B4B135D9DB5A5A93C2210050B32A9400A9497D524BEA660084EEA8EF600849E21EFB7C9F07E5C34C014C009067794BCC527794BCC424F12A67DCBC905C01B97BF8DE5ED9F7C865A4051F50024F9B9EAFA93ECE1A49A2C2E20128E4CA30037100042612C6F8B600084C1C8850BC400B8DAA01547197D6370BC8422C4A72051291E2A0803B0E2094D4BB5FDBEF6A0094F3CCC9A0002FD38E1350E7500C01A1006E3CC24884200C46389312C401F8551C63D4CC9D08035293FD6FCAFF1468B0056780A45D0C01498FBED0039925B82CCDCA7F4E20021A692CC012B00440010B8691761E0002190E21244C98EE0B0C0139297660B401A80002150E20A43C1006A0E44582A400C04A81CD994B9A1004BB1625D0648CE440E49DC402D8612BB6C9F5E97A5AC193F589A100505800ABCF5205138BD2EB527EA130008611167331AEA9B8BDCC4752B78165B39DAA1004C906740139EB0148D3CEC80662B801E60041015EE6006801364E007B801C003F1A801880350100BEC002A3000920E0079801CA00500046A800C0A001A73DFE9830059D29B5E8A51865777DCA1A2820040E4C7A49F88028B9F92DF80292E592B6B840";

#define PACKET_TYPE_ID_LITERAL  4
#define PACKET_TYPE_ID_OP_SUM   0
#define PACKET_TYPE_ID_OP_MUL   1
#define PACKET_TYPE_ID_OP_MIN   2
#define PACKET_TYPE_ID_OP_MAX   3
#define PACKET_TYPE_ID_OP_GT    5
#define PACKET_TYPE_ID_OP_LT    6
#define PACKET_TYPE_ID_OP_EQ    7

#define MAX_SUB_PACKAGES 64

#define STREAM_BLOCK_SIZE 8

int streamReadOffset = 0;

int HexToDec(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'F')
        return (c - 'A') + 10;
    assert(false && "not a valid value");
}

int GetTransmissionByteStream(const char* str, uint8_t* buffer, int bufferLength)
{
    int len = strlen(str) / 2;
    if (buffer == NULL) {
        return len;
    }

    assert(bufferLength >= len && "buffer too small");
    streamReadOffset = 0;
    for (int i = 0; i < len; ++i, str += 2)
    {
        buffer[i] = (HexToDec(str[0]) << 4) | HexToDec(str[1]);
    }
    return len;
}

int readBits(const uint8_t* stream, int bits)
{
    int value = 0;

    for (int bitsToRead = 0; bits; bits -= bitsToRead, streamReadOffset += bitsToRead)
    {
        int blockIndex = streamReadOffset / STREAM_BLOCK_SIZE;
        int bitsInBlock = STREAM_BLOCK_SIZE - (streamReadOffset & (STREAM_BLOCK_SIZE - 1));
        bitsToRead = bits < bitsInBlock ? bits : bitsInBlock;
        value <<= bitsToRead;
        value |= (stream[blockIndex] >> (bitsInBlock - bitsToRead)) & ((1 << bitsToRead) - 1);
    }

    return value;
}

__int64 evaluate(int type, __int64 values[], int numValues)
{
    __int64 value = 0;

    switch (type)
    {
    case PACKET_TYPE_ID_OP_SUM:
        for (int i = 0; i < numValues; ++i)
        {
            value += values[i];
        }
        break;
    case PACKET_TYPE_ID_OP_MUL:
        value = 1;
        for (int i = 0; i < numValues; ++i)
        {
            value *= values[i];
        }
        break;
    case PACKET_TYPE_ID_OP_MIN:
        value = values[0];
        for (int i = 1; i < numValues; ++i)
        {
            if (values[i] < value)
                value = values[i];
        }
        break;
    case PACKET_TYPE_ID_OP_MAX:
        value = values[0];
        for (int i = 1; i < numValues; ++i)
        {
            if (values[i] > value)
                value = values[i];
        }
        break;
    case PACKET_TYPE_ID_OP_LT:
        value = values[0] < values[1] ? 1 : 0;
        break;
    case PACKET_TYPE_ID_OP_GT:
        value = values[0] > values[1] ? 1 : 0;
        break;
    case PACKET_TYPE_ID_OP_EQ:
        value = values[0] == values[1] ? 1 : 0;
        break;
    }

    return value;
}

int parsePacket(const uint8_t* stream, __int64* value)
{
    int startOffset = streamReadOffset;
    int version = readBits(stream, 3);
    int type = readBits(stream, 3);

    if (type == PACKET_TYPE_ID_LITERAL)
    {
        __int64 literalValue = 0;
        bool lastBlock = false;
        while (!lastBlock)
        {
            int block = readBits(stream, 5);
            lastBlock = (block & 16) == 0;
            literalValue = (literalValue << 4) | block & 15;
        }

        *value = literalValue;
    }
    else
    {
        __int64 values[MAX_SUB_PACKAGES] = { 0 };
        int numValues = 0;

        int I = readBits(stream, 1);
        if (I == 0)
        {
            int subpacketLength = readBits(stream, 15);
            while (subpacketLength > 0)
            {
                subpacketLength -= parsePacket(stream, &values[numValues++]);
            }
        }
        else
        {
            int numSubPackets = readBits(stream, 11);
            for (int i = 0; i < numSubPackets; ++i)
            {
                parsePacket(stream, &values[numValues++]);
            }
        }

        *value = evaluate(type, values, numValues);
    }

    return streamReadOffset - startOffset;
}

int main()
{
    const char* packets[16] = { packet0, packet1, packet2, packet3, packet4, packet5, packet6,packet7, packet8, packet9, packet10, packet11, packet12, packet13, packet14, packet15 };

    int bufferLength = GetTransmissionByteStream(packet15, NULL, 0);
    uint8_t* stream = (uint8_t*)malloc(bufferLength);

    for (int i = 0; i < _countof(packets); ++i)
    {
        GetTransmissionByteStream(packets[i], stream, bufferLength);

        __int64 packetValue;
        parsePacket(stream, &packetValue);
        printf("packet #%d -> %I64d\n", i, packetValue);
    }

    free(stream);
}
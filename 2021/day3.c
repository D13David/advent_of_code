#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define PART 2

const int data1[] =
{
    0b000011000110,
    0b100110100101,
    0b101100101001,
    0b001100010000,
    0b011000100100,
    0b110100101111,
    0b110110001001,
    0b010010100101,
    0b100111000010,
    0b001010110001,
    0b110111010001,
    0b110001011000,
    0b011110010100,
    0b001001010111,
    0b110010111111,
    0b111011010111,
    0b100010001011,
    0b010001100010,
    0b111110111111,
    0b001000101111,
    0b010111110110,
    0b000000001100,
    0b001000110101,
    0b111111010011,
    0b111010011100,
    0b111010010110,
    0b100110011000,
    0b110110000010,
    0b101101011101,
    0b111100000001,
    0b110000101011,
    0b000110111000,
    0b110101110000,
    0b110001100001,
    0b110101001101,
    0b100011011000,
    0b110101000111,
    0b100010100111,
    0b111101001100,
    0b000110000110,
    0b101011000100,
    0b011100100001,
    0b101110111010,
    0b110011011101,
    0b010111001101,
    0b110001001101,
    0b100000000101,
    0b010011100100,
    0b111001111111,
    0b101111111111,
    0b110000101010,
    0b000110100001,
    0b111100111000,
    0b000010000100,
    0b010100101001,
    0b000000111111,
    0b111100111011,
    0b000010100111,
    0b100101101110,
    0b101001110110,
    0b100101000111,
    0b111100101011,
    0b011101101000,
    0b101010110101,
    0b010011000100,
    0b111001101110,
    0b001110000110,
    0b000111001011,
    0b010110101011,
    0b100001011001,
    0b001111000111,
    0b110000111000,
    0b111111111011,
    0b100010110011,
    0b001011000100,
    0b100011101111,
    0b111101101000,
    0b111100111010,
    0b000110001100,
    0b010000110001,
    0b000101010101,
    0b110100011000,
    0b001100101111,
    0b110110101010,
    0b101111100111,
    0b011111110001,
    0b011000001100,
    0b110101100001,
    0b101010000111,
    0b101000001000,
    0b001101110100,
    0b100000111010,
    0b011101110000,
    0b011100100100,
    0b111000111010,
    0b100001111110,
    0b100001001111,
    0b011111110010,
    0b001110101011,
    0b111100011010,
    0b010100010111,
    0b000000110001,
    0b110100010001,
    0b110100111101,
    0b101110110000,
    0b111010101010,
    0b101100110001,
    0b010011011001,
    0b111000001001,
    0b100001110101,
    0b011001000110,
    0b010001100101,
    0b100111010101,
    0b100011011010,
    0b001101110011,
    0b100111101101,
    0b111000010010,
    0b011110110001,
    0b100110000010,
    0b000000100011,
    0b100010110100,
    0b101001010101,
    0b101001101100,
    0b000111111000,
    0b101010110100,
    0b010011000001,
    0b110110011101,
    0b111001010110,
    0b011100111101,
    0b001100010001,
    0b011101000001,
    0b001001101001,
    0b010111001011,
    0b111000000010,
    0b111011011101,
    0b101010011101,
    0b001001001110,
    0b001011100011,
    0b100100111111,
    0b101110101111,
    0b111001011101,
    0b000010001100,
    0b010110101010,
    0b001101000010,
    0b010011101110,
    0b110000001001,
    0b010111001111,
    0b100011000010,
    0b100000110010,
    0b100111110101,
    0b100111111011,
    0b010000000101,
    0b111000101101,
    0b010111001010,
    0b100100110101,
    0b100110000110,
    0b110010110111,
    0b000000111101,
    0b010110011100,
    0b100000101000,
    0b000110001111,
    0b001001110110,
    0b101010111001,
    0b101010100110,
    0b101101100111,
    0b001111010110,
    0b001001110100,
    0b011010011111,
    0b101100101010,
    0b001010011010,
    0b101111010100,
    0b100110100001,
    0b111001110101,
    0b110100001110,
    0b000011001100,
    0b001101011110,
    0b001011111010,
    0b101100011101,
    0b001111001110,
    0b111000111000,
    0b100111001010,
    0b010100111100,
    0b010100000111,
    0b010100101011,
    0b010100000001,
    0b100111000110,
    0b111011010000,
    0b100011011001,
    0b111001001110,
    0b000000010101,
    0b111001011110,
    0b010101011000,
    0b110010001001,
    0b100011000000,
    0b111100001100,
    0b001010000100,
    0b100000100110,
    0b100011110110,
    0b010010110001,
    0b011110000000,
    0b000000101000,
    0b010001011001,
    0b011010111010,
    0b011010101110,
    0b001101011011,
    0b111100111001,
    0b011011010110,
    0b111110100101,
    0b100001110001,
    0b010111011100,
    0b111100100001,
    0b110011100010,
    0b001010001011,
    0b100100111100,
    0b000010010001,
    0b101111010000,
    0b111000001101,
    0b000110001011,
    0b000101101001,
    0b001001011011,
    0b001001010010,
    0b011110111011,
    0b001001100001,
    0b110011001011,
    0b000011110000,
    0b001011011101,
    0b001010010010,
    0b011100111110,
    0b101000101000,
    0b110000011001,
    0b010001100001,
    0b011010100010,
    0b100101110010,
    0b111100001010,
    0b001110000010,
    0b011101000000,
    0b110100110011,
    0b010010011101,
    0b101001000100,
    0b110111110010,
    0b001100000011,
    0b000001110110,
    0b000101010010,
    0b100000011011,
    0b000000000010,
    0b011111000111,
    0b110010101011,
    0b100101101001,
    0b010110010101,
    0b000100101000,
    0b001011100010,
    0b001110100010,
    0b110111101001,
    0b101110110100,
    0b011100110101,
    0b011101100111,
    0b001100101100,
    0b111101000010,
    0b011110110100,
    0b111001100000,
    0b111110011000,
    0b001101001110,
    0b101000011111,
    0b110010010110,
    0b111011100011,
    0b110010111001,
    0b101111110111,
    0b101001100110,
    0b011010011010,
    0b000010100101,
    0b110110100001,
    0b000101001001,
    0b000001111111,
    0b010010111011,
    0b100010110111,
    0b110111011111,
    0b010001001101,
    0b000110110101,
    0b010010010100,
    0b101011001111,
    0b111000011110,
    0b110110010010,
    0b111110100110,
    0b100110000001,
    0b011111100001,
    0b001100010100,
    0b001101000101,
    0b011011100010,
    0b011110101111,
    0b001101110110,
    0b110101010110,
    0b000110101101,
    0b111010111000,
    0b011001011111,
    0b100011111101,
    0b110100111100,
    0b100111101100,
    0b001011001110,
    0b111000010100,
    0b001100000110,
    0b111011010101,
    0b000001001011,
    0b111100000000,
    0b010010111101,
    0b110011101010,
    0b011110111110,
    0b011111011110,
    0b111001001001,
    0b000100100111,
    0b001010010101,
    0b101011101101,
    0b110011010111,
    0b011000001000,
    0b111001000101,
    0b101001110011,
    0b011110110101,
    0b111101111011,
    0b111100101100,
    0b001010110100,
    0b101100111000,
    0b011011000000,
    0b101000100011,
    0b100001100110,
    0b001000011101,
    0b001110100000,
    0b011111111101,
    0b010001010111,
    0b001101001000,
    0b100101100100,
    0b000011010110,
    0b100000000100,
    0b011100011111,
    0b000010110011,
    0b100000100010,
    0b101100101110,
    0b100100000010,
    0b001001111001,
    0b011100110111,
    0b011111100011,
    0b010000101100,
    0b100101001101,
    0b000110010100,
    0b110101010010,
    0b100010100011,
    0b110101000001,
    0b010000000110,
    0b110110001011,
    0b100011001001,
    0b111111110000,
    0b111010000011,
    0b011001010101,
    0b011111101000,
    0b100010101111,
    0b010100100000,
    0b100110110100,
    0b101111010011,
    0b011101010001,
    0b100100001010,
    0b001110000000,
    0b001110000101,
    0b111010000010,
    0b101000010000,
    0b111101011111,
    0b001001110001,
    0b011001000100,
    0b000011101100,
    0b100010010111,
    0b110000101111,
    0b110010100100,
    0b100000011111,
    0b011100100011,
    0b000001101000,
    0b101010100001,
    0b010001100011,
    0b001010111110,
    0b111010111110,
    0b011011000100,
    0b001101100000,
    0b001101100011,
    0b111010011111,
    0b111110110010,
    0b010110100111,
    0b101011011010,
    0b110010011001,
    0b001011010010,
    0b000101100000,
    0b100000100011,
    0b000111100001,
    0b001111110101,
    0b000011101001,
    0b110101010100,
    0b111011010110,
    0b101111011000,
    0b001000100100,
    0b010110011001,
    0b110111000011,
    0b001010011000,
    0b110011000010,
    0b111101001000,
    0b000001010001,
    0b101011110111,
    0b011001100110,
    0b101101101101,
    0b100011010110,
    0b110001010000,
    0b110001010001,
    0b100011100110,
    0b111111011100,
    0b000101101000,
    0b110000111001,
    0b111100010011,
    0b101010110001,
    0b101100001011,
    0b110100110001,
    0b100110111011,
    0b011100100111,
    0b110001011111,
    0b011010100101,
    0b101011111100,
    0b111000010101,
    0b110110110100,
    0b111101100011,
    0b001110100101,
    0b100010111001,
    0b100010001001,
    0b100001010101,
    0b010011001100,
    0b000101010111,
    0b101100010100,
    0b000101000111,
    0b001111101100,
    0b111000001100,
    0b100110101101,
    0b000001100010,
    0b100010011011,
    0b011001000011,
    0b110000010100,
    0b010100001011,
    0b101011001110,
    0b000110110000,
    0b110011000110,
    0b101101111101,
    0b001001000111,
    0b001001011111,
    0b110100011011,
    0b101110010011,
    0b100001011000,
    0b010010110111,
    0b011001011000,
    0b011011101100,
    0b100110000100,
    0b001101110000,
    0b011011001101,
    0b111110001011,
    0b110111100101,
    0b101001010100,
    0b100101110101,
    0b100010000001,
    0b011110011010,
    0b000010011100,
    0b111011000101,
    0b100110001011,
    0b000101101011,
    0b011100100010,
    0b000010111000,
    0b000001100000,
    0b000100001000,
    0b110110101110,
    0b101000100110,
    0b100101010001,
    0b011010010100,
    0b000001111110,
    0b001100010110,
    0b001001101111,
    0b111010001011,
    0b100100101111,
    0b011100011011,
    0b100111011110,
    0b000010010101,
    0b011001110001,
    0b001011011000,
    0b011010100110,
    0b110011011111,
    0b001110011101,
    0b111101010001,
    0b101010111000,
    0b110000010110,
    0b110110001000,
    0b011000111001,
    0b111010100111,
    0b101011011110,
    0b001001011001,
    0b101011100111,
    0b111011110010,
    0b010100110101,
    0b101001111010,
    0b111110011111,
    0b110110010000,
    0b101101010101,
    0b000101111100,
    0b001110101010,
    0b111111111000,
    0b001001000100,
    0b111011011111,
    0b111000010001,
    0b111101100010,
    0b001000011100,
    0b100100000001,
    0b111101010011,
    0b001100011110,
    0b110000001100,
    0b000101011000,
    0b101000101111,
    0b100000101100,
    0b001010100001,
    0b001100111001,
    0b000110011011,
    0b000111100000,
    0b010001000001,
    0b010010111001,
    0b101111001101,
    0b110111011101,
    0b101010001110,
    0b101010100111,
    0b111101000001,
    0b101001011010,
    0b011111010100,
    0b100010111000,
    0b110111110001,
    0b001110111000,
    0b000010001111,
    0b110111001101,
    0b110110011110,
    0b000001001111,
    0b110100000000,
    0b100101011001,
    0b111101110001,
    0b001000000000,
    0b110110001010,
    0b010000101111,
    0b110000000100,
    0b111100110100,
    0b001110000011,
    0b101100111111,
    0b100101011110,
    0b010010101110,
    0b001011001001,
    0b011000101000,
    0b100000001010,
    0b010001110001,
    0b011001111001,
    0b111100001111,
    0b000111100011,
    0b110100100111,
    0b101101111011,
    0b101010111101,
    0b110000001011,
    0b011011010000,
    0b001000100000,
    0b101101001100,
    0b110111101000,
    0b111011101011,
    0b110011101100,
    0b000010010000,
    0b111100010100,
    0b000111011101,
    0b110110110011,
    0b100110100000,
    0b101010000110,
    0b101001110001,
    0b101110001101,
    0b100010111110,
    0b011001001001,
    0b011111111001,
    0b000101010110,
    0b010011110111,
    0b000000000011,
    0b001101001100,
    0b001001110101,
    0b010010101100,
    0b101100000110,
    0b010110011111,
    0b101000010110,
    0b011001011010,
    0b011111110000,
    0b101101111001,
    0b110011110110,
    0b101101101010,
    0b111111111110,
    0b011001110110,
    0b000010111101,
    0b100110110001,
    0b000111010001,
    0b000011001101,
    0b100110111111,
    0b101010011110,
    0b101010011011,
    0b110011010001,
    0b101001100000,
    0b111100000111,
    0b000111101000,
    0b011011010111,
    0b010111000011,
    0b000111100101,
    0b101111011111,
    0b101110011111,
    0b100010001000,
    0b101111000001,
    0b100101010101,
    0b101011110010,
    0b001010111111,
    0b010101010001,
    0b110101110110,
    0b000000111110,
    0b010001101000,
    0b111111001001,
    0b110111101111,
    0b100100110000,
    0b110111010010,
    0b111011000000,
    0b011100010001,
    0b001100100010,
    0b010110010011,
    0b111101010000,
    0b011010101011,
    0b100110010101,
    0b011100000110,
    0b001110011001,
    0b001010100000,
    0b101000000000,
    0b101011101110,
    0b111100110101,
    0b100111110100,
    0b011000110010,
    0b110011010011,
    0b101011011101,
    0b101001110111,
    0b011010111111,
    0b101011000010,
    0b001100110010,
    0b111100100111,
    0b100110111000,
    0b111111010010,
    0b010111010100,
    0b101000101010,
    0b011000011111,
    0b000001110100,
    0b101110111000,
    0b001001011000,
    0b011001100101,
    0b011111000000,
    0b110001101010,
    0b010000101110,
    0b000001110010,
    0b000000000101,
    0b001010111001,
    0b101101101001,
    0b110100100100,
    0b001000100011,
    0b010000000000,
    0b010111010101,
    0b011010001010,
    0b000101010011,
    0b101011001010,
    0b001010101101,
    0b101110001010,
    0b101101110000,
    0b001000010001,
    0b100001000001,
    0b010100000011,
    0b011111011010,
    0b001110011111,
    0b010000110000,
    0b100100010010,
    0b111011111101,
    0b010010010010,
    0b110010000000,
    0b011000111100,
    0b001110010101,
    0b100110011010,
    0b110101000011,
    0b110011000001,
    0b110101111000,
    0b111001011100,
    0b101010000100,
    0b001001110011,
    0b101011110101,
    0b101011010101,
    0b110011111000,
    0b100001011010,
    0b000010000111,
    0b001010110010,
    0b000110010000,
    0b101101101111,
    0b111010010000,
    0b011010000100,
    0b011110010101,
    0b011010011101,
    0b010001011010,
    0b001111101010,
    0b100001001000,
    0b010010110110,
    0b000001011101,
    0b001001101011,
    0b111001110010,
    0b101101100100,
    0b001000101110,
    0b000000010100,
    0b001010110000,
    0b011010101000,
    0b010001001001,
    0b100110111110,
    0b110111001010,
    0b111110000111,
    0b101111011110,
    0b001110110001,
    0b001101110001,
    0b111000000011,
    0b010000010001,
    0b011001111010,
    0b010100111111,
    0b111000000111,
    0b101011001100,
    0b111000100101,
    0b101001110100,
    0b101110100000,
    0b100011001110,
    0b010111101110,
    0b000100000100,
    0b110011110011,
    0b011110101010,
    0b101100001000,
    0b011010111101,
    0b111111111010,
    0b100000101011,
    0b001110101001,
    0b011100000111,
    0b010000101101,
    0b001101011000,
    0b011000101010,
    0b000100111001,
    0b110111100000,
    0b000111111101,
    0b111001011011,
    0b000011001110,
    0b011110010000,
    0b100010101110,
    0b111001110001,
    0b000101011010,
    0b110001100101,
    0b010011011000,
    0b000000100100,
    0b000101001101,
    0b111110011110,
    0b000010110110,
    0b101100001100,
    0b010111000111,
    0b000110010110,
    0b110110010100,
    0b111000110011,
    0b111011011100,
    0b011001000000,
    0b100101000110,
    0b100011010101,
    0b101011101111,
    0b010011111010,
    0b000110011100,
    0b111010010010,
    0b111010111100,
    0b010111100101,
    0b101101001101,
    0b010110100100,
    0b011100010101,
    0b000001100110,
    0b001000110110,
    0b011101000010,
    0b111100101111,
    0b110110001110,
    0b000011100010,
    0b101011000001,
    0b110100100000,
    0b001111111000,
    0b110111001111,
    0b000100111110,
    0b111100000110,
    0b010111010010,
    0b001000101001,
    0b000001010000,
    0b100010110010,
    0b101101110100,
    0b111101100001,
    0b000101111111,
    0b000101001110,
    0b110010001101,
    0b101000011001,
    0b111001001111,
    0b111000000000,
    0b000101110110,
    0b111001111001,
    0b010010010101,
    0b110011011000,
    0b011000001001,
    0b110001010010,
    0b101100110010,
    0b101011010011,
    0b000000110110,
    0b111000011000,
    0b101001101011,
    0b111100100100,
    0b111011111001,
    0b111101001110,
    0b101000001010,
    0b000111000101,
    0b110011010010,
    0b011101101001,
    0b111000110010,
    0b111010011010,
    0b110001011101,
    0b101000111100,
    0b100111011111,
    0b011000101101,
    0b011111101101,
    0b100001000111,
    0b010001101010,
    0b110100010000,
    0b110100011100,
    0b111001100001,
    0b001101010100,
    0b000101100110,
    0b001111001000,
    0b011001011100,
    0b000100011001,
    0b011100010010,
    0b101010101100,
    0b111011110101,
    0b101011000111,
    0b100111010100,
    0b111001100100,
    0b110011101011,
    0b010011000110,
    0b111101100101,
    0b101101011000,
    0b000101000100,
    0b010001001110,
    0b110000011110,
    0b100100100101,
    0b011000100000,
    0b010111010000,
    0b000101011001,
    0b110110101100,
    0b000011010000,
    0b010110100000,
    0b110010101101,
    0b111100111111,
    0b001101101001,
    0b000110000010,
    0b100101111101,
    0b101101010010,
    0b110111011000,
    0b000110000100,
    0b001000001001,
    0b010010101010,
    0b101111010101,
    0b010010000000,
    0b101011011111,
    0b111110010010,
    0b111000111011,
    0b000001011100,
    0b010101111111,
    0b011000101100,
    0b000001011001,
    0b100001011011,
    0b100001101110,
    0b110010000001,
    0b001011110100,
    0b011110010001,
    0b111100110000,
    0b101000111111,
    0b110000011011,
    0b011100111010,
    0b001010011101,
    0b100110001100,
    0b110011011010,
    0b111001000100,
    0b010100111110,
    0b010001110111,
    0b010011010010,
    0b000101001000,
    0b010011101010,
    0b000001110101,
    0b010101101101,
    0b010001100111,
    0b101001111111,
    0b111011011011,
    0b100001100011,
    0b101101111000,
    0b110011011001,
    0b001110110010,
    0b011101001101,
    0b010101010010,
    0b110001110001,
    0b010011010000,
    0b110000000111,
    0b011100110100,
    0b010000011000,
    0b011001111011,
    0b111010110010,
    0b101100010011,
    0b011011001000,
    0b111011101101,
    0b010000011101,
    0b000001010101,
    0b101011100011,
    0b010110111011,
    0b001100100000,
    0b111011100001,
    0b111111001000,
    0b111110110001,
    0b100001110000,
    0b010001001010,
    0b100111010011,
    0b000010000000,
    0b010011000010,
    0b110101110101,
    0b000110011110,
    0b011111111010,
    0b011010101101,
    0b110110000101,
    0b111000110000,
    0b111011000110,
    0b111101000011,
    0b101110010110,
    0b000001000111,
    0b001111111001,
    0b110101011001,
    0b111010110100,
    0b100000000011,
    0b010110110011,
    0b100011100111,
    0b001111101110,
    0b110010111000,
    0b001100111010,
    0b101010100101,
    0b000101110111,
    0b011001110010,
    0b010110001100,
    0b101010111111,
    0b010010011011,
    0b100110011111,
    0b100010010000,
    0b110100001000,
    0b001001000010,
    0b101010100100,
    0b100111001011,
    0b010100000000,
    0b100100100111,
    0b110001101011,
    0b011000110100,
    0b111000001000,
    0b011111110110,
    0b011111000101,
    0b000000011011,
    0b100111000111,
    0b010001110100,
    0b101000010001,
    0b010011100010,
    0b111010001010,
    0b101101110111,
    0b010100010101,
    0b000100001111,
    0b001110000001,
    0b000011110001,
    0b101000010101,
    0b111100100010,
    0b101100010110,
    0b000111001101,
    0b101100101111,
    0b110011101001,
    0b111110110101,
    0b000110011010,
    0b010100100010,
    0b111100010110,
    0b011110110110,
    0b101011101000,
    0b100001000010,
    0b001001101101,
    0b110111111101,
    0b111001110100,
    0b111001001000,
    0b011011100101,
    0b010111011110,
    0b111000011111,
    0b110111100100,
    0b010011110110,
    0b010000111011,
    0b100000001001,
    0b101110010101,
    0b100110111010,
    0b100001000000,
    0b110100110111
};

const int data2[] =
{
    0b00100,
    0b11110,
    0b10110,
    0b10111,
    0b10101,
    0b01111,
    0b00111,
    0b11100,
    0b10000,
    0b11001,
    0b00010,
    0b01010
};

#define data data1
#define BITS 12 // 5

void CountBitsInArray(int bitCounts[BITS], const int* buffer, int count)
{
    memset(bitCounts, 0, BITS * sizeof(int));

    for (int i = 0; i < count; ++i)
    {
        switch (BITS - 1)
        {
        case 11: bitCounts[11] += (buffer[i] >> 11) & 1;
        case 10: bitCounts[10] += (buffer[i] >> 10) & 1;
        case 9: bitCounts[9] += (buffer[i] >> 9) & 1;
        case 8: bitCounts[8] += (buffer[i] >> 8) & 1;
        case 7: bitCounts[7] += (buffer[i] >> 7) & 1;
        case 6: bitCounts[6] += (buffer[i] >> 6) & 1;
        case 5: bitCounts[5] += (buffer[i] >> 5) & 1;
        case 4: bitCounts[4] += (buffer[i] >> 4) & 1;
        case 3: bitCounts[3] += (buffer[i] >> 3) & 1;
        case 2: bitCounts[2] += (buffer[i] >> 2) & 1;
        case 1: bitCounts[1] += (buffer[i] >> 1) & 1;
        case 0: bitCounts[0] += (buffer[i] >> 0) & 1;
        }
    }
}
#if PART == 1
void SolvePuzzle()
{
    int bitCounts[BITS]{};

    CountBitsInArray(bitCounts, data, _countof(data));

    int gammaRate = 0;
    for (int i = BITS - 1; i >= 0; --i)
    {
        gammaRate <<= 1;
        if (bitCounts[i] > _countof(data) / 2)
            gammaRate |= 1;
    }

    int epsilonRate = (~gammaRate) & (1 << BITS) - 1;

    printf("%d\n", gammaRate * epsilonRate);
}
#endif

#if PART == 2
int ComputeRating(int* buffer, int size, bool (*filter)(int, int))
{
    int bitCounts[BITS] = { 0 };

    for (int count = size, currentBit = BITS - 1; count > 1; --currentBit)
    {
        CountBitsInArray(bitCounts, buffer, count);

        bool keepEntry = filter(bitCounts[currentBit], count - bitCounts[currentBit]);

        int index = 0;
        for (int i = 0; i < count; ++i)
        {
            if (((buffer[i] >> currentBit) & 1) == keepEntry)
                buffer[index++] = buffer[i];
        }

        count = index;
    }

    return buffer[0];
}

bool filterOxygenGeneratorRating(int a, int b) { return a >= b; }
bool filterC02ScrubberRating(int a, int b) { return a < b; }

void SolvePuzzle()
{
    int size = _countof(data);
    int* buffer = (int*)malloc(size * sizeof(int) * 2);
    assert(buffer != NULL && "allocation failed...");
    int* buffer1 = &buffer[size];

    for (int i = 0; i < size; ++i)
    {
        buffer[i] = buffer1[i] = data[i];
    }

    int oxygenGeneratorRating = ComputeRating(buffer, size, filterOxygenGeneratorRating);
    int co2ScrubberRating = ComputeRating(buffer1, size, filterC02ScrubberRating);

    printf("%d\n", co2ScrubberRating * oxygenGeneratorRating);

    free(buffer);
}
#endif

int main()
{
    SolvePuzzle();
}
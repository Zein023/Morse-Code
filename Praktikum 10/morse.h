// morse.h
#ifndef MORSE_H
#define MORSE_H

#include "boolean.h"

#define MAX_NODES 55 // Jumlah total karakter dalam pohon Morse

typedef char infotype;

typedef struct {
    infotype info;     // Karakter yang direpresentasikan
    int left;      // Anak kiri (untuk titik •)
    int right;     // Anak kanan (untuk garis −)
} MorseNode;

typedef MorseNode MorseTree[MAX_NODES+1]; // Indeks 0 tidak digunakan

// Fungsi-fungsi yang diperlukan
void CreateMorseTree(MorseTree T);
void CharToMorse(MorseTree T, char c, char* morseCode);
void StringToMorse(MorseTree T, const char* text, char* morseResult);
void MorseToChar(MorseTree T, const char* morseCode, char* result);
void PrintInOrder(MorseTree T, int root);
void FileToMorse(MorseTree T, const char* inputFile, const char* outputFile);

#endif
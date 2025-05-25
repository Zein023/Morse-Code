#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "morse.h"
#include "nbtrees.h"

int main() {
    MorseTree morseTree;
    CreateMorseTree(morseTree);
    
    char text[55];
    char morse[1000] = ""; // buffer hasil kode Morse
    
    printf("Masukkan Text: ");
    fgets(text, sizeof(text), stdin);

    int len = strlen(text);
    if (text[len - 1] == '\n') {
        text[len - 1] = '\0';
        len--;
    }

    for (int i = 0; i < len; i++) {
        if (text[i] == ' ') {
            strcat(morse, "/ ");
            continue;
        }

        char temp[50];
        CharToMorse(morseTree, text[i], temp);
        strcat(morse, temp);
        strcat(morse, " ");
    }

    printf("Hasil Morse: %s\n", morse);
    
    for (int i = 0; i < len; i++) {
    	char temp[50];
    	CharToMorse(morseTree, text[i], temp);
    	printf("Huruf: %c => Morse: %s\n", text[i], temp); // debug
    	strcat(morse, temp);
    	strcat(morse, " ");
	}
	
	printf("InOrder Traversal : ");
	PrintInOrder(morseTree, 1);
	
	//====== MORSE TO STRING =======//
	
	char inputMorse[256];
    char hasil[256] = "";  // buffer untuk hasil decode

    printf("\n\nMasukkan Kode Morse: ");
    fgets(inputMorse, sizeof(inputMorse), stdin);

    // Hilangkan newline jika ada
    int lenMorse = strlen(inputMorse);
    if (lenMorse > 0 && inputMorse[len - 1] == '\n') {
        inputMorse[lenMorse - 1] = '\0';
    }

    // Pisahkan inputMorse per token (kode Morse per huruf)
    char *token = strtok(inputMorse, " ");

    while (token != NULL) {
    	// Bersihkan newline di akhir token (jika ada)
    	size_t tokenLen = strlen(token);
    	if (tokenLen > 0 && token[tokenLen - 1] == '\n') {
        	token[tokenLen - 1] = '\0';
    	}

    	char hasilChar;
    	MorseToChar(morseTree, token, &hasilChar);

    	if (hasilChar != '\0') {
        	int curLen = strlen(hasil);
        	hasil[curLen] = hasilChar;
        	hasil[curLen + 1] = '\0';
    	} else {
        	printf("[Warning] Kode Morse \"%s\" tidak valid\n", token);
    	}	

    	token = strtok(NULL, " ");
	}

    printf("Hasil Terjemahan: %s\n", hasil);
	
	printf("Memulai konversi file...\n");
	FileToMorse(morseTree, "input.txt", "out.txt");
	printf("FIle berhasil di konversi!\n");


    return 0;
}

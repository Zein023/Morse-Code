#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "morse.h"

void CreateMorseTree(MorseTree T) {
    // Inisialisasi semua node
    for (int i = 0; i <= MAX_NODES; i++) {
        T[i].info = '\0';
        T[i].left = 0;
        T[i].right = 0;
    }

    // Root (tidak merepresentasikan karakter)
    T[1].left = 2;    // E (•)
    T[1].right = 3;   // T (−)

    /* LEVEL 2 */
    T[2].info = 'E';  // E (•)
    T[2].left = 4;     // I (••)
    T[2].right = 5;    // A (•−)
    
    T[3].info = 'T';   // T (−)
    T[3].left = 6;     // N (−•)
    T[3].right = 7;    // M (−−)

    /* LEVEL 3 */
    T[4].info = 'I';   // I (••)
    T[4].left = 8;      // S (•••)
    T[4].right = 9;     // U (••−)
    
    T[5].info = 'A';    // A (•−)
    T[5].left = 10;      // R (•−•)
    T[5].right = 11;     // W (•−−)
    
    T[6].info = 'N';    // N (−•)
    T[6].left = 12;      // D (−••)
    T[6].right = 13;     // K (−•−)
    
    T[7].info = 'M';    // M (−−)
    T[7].left = 14;      // G (−−•)
    T[7].right = 15;     // O (−−−)

    /* LEVEL 4 */
    // Dari I (••)
    T[8].info = 'S';    // S (•••)
    T[8].left = 16;      // H (••••)
    T[8].right = 17;     // V (•••−)
    
    T[9].info = 'U';     // U (••−)
    T[9].left = 18;      // F (••−•)
    T[9].right = 40;     // (Kosong)
    
    // Dari A (•−)
    T[10].info = 'R';    // R (•−•)
    T[10].left = 20;      // L (•−••)
    T[10].right = 41;     // (Kosong)
    
    T[11].info = 'W';    // W (•−−)
    T[11].left = 22;      // P (•−−•)
    T[11].right = 23;     // J (•−−−)
    
    // Dari N (−•)
    T[12].info = 'D';    // D (−••)
    T[12].left = 24;      // B (−•••)
    T[12].right = 25;     // X (−••−)
    
    T[13].info = 'K';    // K (−•−)
    T[13].left = 26;      // C (−•−•)
    T[13].right = 27;     // Y (−•−−)
    
    // Dari M (−−)
    T[14].info = 'G';    // G (−−•)
    T[14].left = 28;      // Z (−−••)
    T[14].right = 29;     // Q (−−•−)
    
    T[15].info = 'O';    // O (−−−)
    T[15].left = 37;      // 3
    T[15].right = 39;     // (Kosong)

    /* LEVEL 5 (Huruf) */
    T[16].info = 'H';    // H (••••)
    T[16].left = 32;
	T[16].right = 31;
    T[17].info = 'V';    // V (•••−) 
	T[17].right = 30;
    T[18].info = 'F';    // F (••−•)
    T[20].info = 'L';    // L (•−••)
    T[22].info = 'P';    // P (•−−•)
    T[23].info = 'J';    // J (•−−−)
    T[23].right = 19;	// 1
    T[24].info = 'B';    // B (−•••)
    T[24].left = 33;	// 6
    T[25].info = 'X';    // X (−••−)
    T[26].info = 'C';    // C (−•−•)
    T[27].info = 'Y';    // Y (−•−−)
    T[28].info = 'Z';    // Z (−−••)
    T[28].left = 34;	// 34
    T[29].info = 'Q';    // Q (−−•−)

    /* ANGKA (Level 5-6) */
    // Angka 1-5
    T[19].info = '1';    // 1 (•−−−−)
    T[21].info = '2';    // 2 (••−−−)
    T[30].info = '3';    // 3 (•••−−)
    T[31].info = '4';    // 4 (••••−)
    T[32].info = '5';    // 5 (•••••)
    
    // Angka 6-0
    T[33].info = '6';    // 6 (−••••)
    T[34].info = '7';    // 7 (−−•••)
    T[35].info = '8';    // 8 (−−−••)
    T[36].info = '9';    // 9 (−−−−•)
    T[37].info = '0';    // 0 (−−−−−)
    T[37].left = 35;	// 8

    /* SPESIAL KARAKTER */
    T[38].info = ' ';    // Spasi (•−••−•)
    T[39].info = '\0';
    T[39].left = 36;	// 9
    T[40].info = '\0';
    T[40].right = 21;	// 2
    T[41].left = 38;	// space
}

void CharToMorse(MorseTree T, char c, char* morseCode) {
    c = toupper(c);
    int parent[MAX_NODES+1] = {0};

    // Bangun array parent
    for (int i = 1; i <= MAX_NODES; i++) {
        if (T[i].left) {
            parent[T[i].left] = i;
        }
        if (T[i].right) {
            parent[T[i].right] = i;
        }
    }

    // Cari posisi huruf
    int found = 0;
    for (int i = 1; i <= MAX_NODES; i++) {
        if (T[i].info == c) {
            found = i;
            break;
        }
    }

    if (found == 0) {
        morseCode[0] = '\0';  // karakter tidak ditemukan, kembalikan string kosong
        return;
    }

    // Bangun Morse dari leaf ke root
    int index = 0;
    char tempCode[10];
    int node = found;

    while (node != 1 && node != 0) {
        int p = parent[node];
        if (T[p].left == node) {
            tempCode[index++] = '.';
        } else if (T[p].right == node) {
            tempCode[index++] = '-';
        }
        node = p;
    }

    // Balik urutan (karena kita mulai dari leaf ke root)
    for (int i = 0; i < index; i++) {
        morseCode[i] = tempCode[index - i - 1];
    }
    morseCode[index] = '\0';  // null-terminate
}


//void StringToMorse(MorseTree T, const char* text, char* morseResult) {
//    morseResult[0] = '\0';
//    
//    for (int i = 0; text[i] != '\0'; i++) {
//        char morseCode[10];
//        
//        if (text[i] == ' ') {
//            strcat(morseResult, "/ "); // Spasi antar kata
//        } else {
//            CharToMorse(T, text[i], morseCode);
//            strcat(morseResult, morseCode);
//            strcat(morseResult, " "); // Spasi antar huruf
//        }
//    }
//}

void PrintInOrder(MorseTree T, int root) {
    if (root == 0) return;
    
    PrintInOrder(T, T[root].left);
    if (T[root].info != '\0') {
        printf("%c ", T[root].info);
    }
    PrintInOrder(T, T[root].right);
}

//void VisualizeTree(MorseTree T, int root, int level) {
//    if (root == 0) return;
//    
//    // Anak kanan dulu (agar tampilan lebih baik)
//    VisualizeTree(T, T[root].right, level + 1);
//    
//    // Indentasi sesuai level
//    for (int i = 0; i < level; i++) {
//        printf("    ");
//    }
//    
//    // Tampilkan node
//    printf("%c\n", T[root].info);
//    
//    // Anak kiri
//    VisualizeTree(T, T[root].left, level + 1);
//}

void MorseToChar(MorseTree T, const char* morseCode, char* result) {
    int current = 1; // Mulai dari root
    
    for (int i = 0; morseCode[i] != '\0'; i++) {
        if (morseCode[i] == '.') {
            current = T[current].left;
        } else if (morseCode[i] == '-') {
            current = T[current].right;
        } else {
            // Karakter tidak valid
            *result = '\0';
            return;
        }
        
        if (current == 0) { // Tidak valid
            *result = '\0';
            return;
        }
    }
    
    *result = T[current].info;
}

void FileToMorse(MorseTree T, const char* inputFile, const char* outputFile) {
    FILE *input = fopen(inputFile, "r");
    FILE *output = fopen(outputFile, "w");
    
    if (input == NULL || output == NULL) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    char line[256];
    char morseLine[1024];
    
    while (fgets(line, sizeof(line), input) != NULL) {
        morseLine[0] = '\0'; // Reset buffer
        
        for (int i = 0; line[i] != '\0'; i++) {
            char morseChar[10];
            
            if (line[i] == '\n') {
                strcat(morseLine, "\n");
                continue;
            }
            
            CharToMorse(T, line[i], morseChar);
            strcat(morseLine, morseChar);
            strcat(morseLine, " ");
        }
        
        fprintf(output, "%s", morseLine);
    }

    fclose(input);
    fclose(output);
}
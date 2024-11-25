#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
#define MAX_LEN 100
#define TOP_N 10
const double ENGLISH_FREQ[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.317, 9.056, 
    2.758, 0.978, 2.560, 0.150, 1.929, 0.095
};
int charToNum(char c) {
    return toupper(c) - 'A';
}

char numToChar(int num) {
    return num + 'A';
}

void calculateFrequencies(const char *text, int *freq) {
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = 0;
    }

    while (*text) {
        if (isalpha(*text)) {
            freq[charToNum(*text)]++;
        }
        text++;
    }
}
void sortFrequencies(int *freq, char *letters) {
    int i, j;
    char temp;
    int tempFreq;

    for (i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (j = i + 1; j < ALPHABET_SIZE; j++) {
            if (freq[i] < freq[j]) {
                tempFreq = freq[i];
                freq[i] = freq[j];
                freq[j] = tempFreq;
                temp = letters[i];
                letters[i] = letters[j];
                letters[j] = temp;
            }
        }
    }
}

void generatePlaintext(const char *ciphertext, char *plaintext, const char *substitution) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            plaintext[i] = substitution[charToNum(ciphertext[i])];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

void printTopPlaintexts(const char *ciphertext, int topN) {
    int freq[ALPHABET_SIZE];
    char letters[ALPHABET_SIZE];
    char substitution[ALPHABET_SIZE];
    char plaintext[MAX_LEN];
    int i;

    for (i = 0; i < ALPHABET_SIZE; i++) {
        letters[i] = numToChar(i);
    }

    calculateFrequencies(ciphertext, freq);

    sortFrequencies(freq, letters);

    printf("Top %d possible plaintexts:\n", topN);
    for (i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        int j;
        for (j = 0; j < ALPHABET_SIZE; j++) {
            substitution[j] = letters[(j + i) % ALPHABET_SIZE]; 
        }
        generatePlaintext(ciphertext, plaintext, substitution);
        printf("%2d: %s\n", i + 1, plaintext);
    }
}

int main() {
    char ciphertext[MAX_LEN];
    int topN;

    printf("Enter the ciphertext (only letters and spaces): ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);
    if (topN <= 0 || topN > TOP_N) {
        printf("Invalid number of top plaintexts.\n");
        return 1;
    }

    printTopPlaintexts(ciphertext, topN);

    return 0;
}
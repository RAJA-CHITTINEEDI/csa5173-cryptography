#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define ALPHABET_SIZE 26

int main() {
    char message[1000];
    char key[ALPHABET_SIZE + 1] = "ZYXWVUTSRQPONMLKJIHGFEDCBA"; 
    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    
    printf("Original message: %s", message); 
    
    for (int i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            char base = isupper(message[i]) ? 'A' : 'a';
            message[i] = key[message[i] - base];
        }
    }
    
    printf("Encrypted message: %s", message);
    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26

double letterFrequency[] = {0.127, 0.093, 0.082, 0.067, 0.126, 0.070, 0.076, 0.087, 0.022, 0.002, 0.022, 0.043, 0.031, 0.085, 0.042, 0.025, 0.020, 0.060, 0.061, 0.091, 0.028, 0.010, 0.024, 0.002, 0.002, 0.001};

void cleanText(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i]; i++) if (isalpha(input[i])) output[j++] = tolower(input[i]);
    output[j] = '\0';
}

void computeFrequency(char *text, int *frequency) {
    for (int i = 0; text[i]; i++) frequency[text[i] - 'a']++;
}

void decryptWithShift(char *cipher, int shift, char *plain) {
    for (int i = 0; cipher[i]; i++) plain[i] = ((cipher[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
    plain[strlen(cipher)] = '\0';
}

double calculateMatchScore(int *frequency) {
    double score = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) score += frequency[i] * letterFrequency[i];
    return score;
}

void frequencyAttack(char *ciphertext, int topN) {
    int freq[ALPHABET_SIZE] = {0};
    double scores[ALPHABET_SIZE];
    char cleanedText[strlen(ciphertext) + 1], plaintext[strlen(ciphertext) + 1];

    cleanText(ciphertext, cleanedText);
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        memset(freq, 0, sizeof(freq));
        decryptWithShift(cleanedText, shift, plaintext);
        computeFrequency(plaintext, freq);
        scores[shift] = calculateMatchScore(freq);
    }

    printf("\nTop %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        int maxIdx = -1;
        double maxScore = -1;
        for (int j = 0; j < ALPHABET_SIZE; j++) if (scores[j] > maxScore) { maxScore = scores[j]; maxIdx = j; }
        decryptWithShift(cleanedText, maxIdx, plaintext);
        printf("Shift %d: %s\n", maxIdx, plaintext);
        scores[maxIdx] = -1;
    }
}

int main() {
    char ciphertext[1000];
    int topN;
    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    printf("Enter top N results: ");
    scanf("%d", &topN);
    frequencyAttack(ciphertext, topN);
    return 0;
}

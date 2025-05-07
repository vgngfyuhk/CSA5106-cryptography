#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to convert a letter to its number (A=0, B=1, ..., Z=25)
int letter_to_number(char letter) {
    return tolower(letter) - 'a';
}

// Function to convert a number to a letter
char number_to_letter(int number) {
    return (char)(number + 'a');
}

// Function to encrypt the message using Hill Cipher
void hill_encrypt(char *plaintext, int key[2][2], char *ciphertext) {
    int n = strlen(plaintext);

    // Loop through plaintext in pairs of 2
    for (int i = 0; i < n; i += 2) {
        int p1 = letter_to_number(plaintext[i]);
        int p2 = letter_to_number(plaintext[i + 1]);
        
        // Apply Hill cipher encryption formula: C = K * P (mod 26)
        int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;
        
        ciphertext[i] = number_to_letter(c1);
        ciphertext[i + 1] = number_to_letter(c2);
    }
    ciphertext[n] = '\0';  // Null terminate the string
}

// Function to find the modular inverse of a number mod 26
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;  // No inverse exists
}

// Function to decrypt the message using Hill Cipher
void hill_decrypt(char *ciphertext, int key[2][2], char *plaintext) {
    // Inverse key matrix calculation
    int determinant = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    int inv_det = mod_inverse(determinant, 26);
    
    // Inverse key matrix
    int key_inv[2][2] = {
        {inv_det * key[1][1] % 26, inv_det * -key[0][1] % 26},
        {inv_det * -key[1][0] % 26, inv_det * key[0][0] % 26}
    };

    // Apply Hill cipher decryption formula: P = K^-1 * C (mod 26)
    int n = strlen(ciphertext);
    for (int i = 0; i < n; i += 2) {
        int c1 = letter_to_number(ciphertext[i]);
        int c2 = letter_to_number(ciphertext[i + 1]);
        
        // Apply Hill cipher decryption formula
        int p1 = (key_inv[0][0] * c1 + key_inv[0][1] * c2) % 26;
        int p2 = (key_inv[1][0] * c1 + key_inv[1][1] * c2) % 26;
        
        plaintext[i] = number_to_letter(p1);
        plaintext[i + 1] = number_to_letter(p2);
    }
    plaintext[n] = '\0';  // Null terminate the string
}

int main() {
    // Original plaintext message
    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";
    char ciphertext[100];
    char decryptedtext[100];

    // Hill cipher key matrix
    int key[2][2] = {{9, 4}, {5, 7}};
    
    // Encrypt the plaintext using Hill cipher
    hill_encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    
    // Decrypt the ciphertext using Hill cipher
    hill_decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted Text: %s\n", decryptedtext);

    return 0;
}

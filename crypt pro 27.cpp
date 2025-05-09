#include <stdio.h>
#include <string.h>
#include <ctype.h>

// RSA modular exponentiation
int mod_exp(int base, int exp, int mod) {
    long long result = 1;
    long long b = base;
    while (exp > 0) {
        if (exp % 2) result = (result * b) % mod;
        b = (b * b) % mod;
        exp >>= 1;
    }
    return (int)result;
}

// Convert char A–Z to number 0–25
int char_to_int(char c) {
    return toupper(c) - 'A';
}

// Convert number 0–25 to char A–Z
char int_to_char(int i) {
    return 'A' + i;
}

int main() {
    // Simulate large RSA public key
    int e = 17;
    int n = 3233; // Not large, for demo; in real use, this would be ~2048-bit

    // Alice's message
    char message[] = "HELLO";
    int encrypted[100];

    printf("Original message: %s\n", message);
    int i,j;

    // Encrypt each letter
    for ( i = 0; i < strlen(message); i++) {
        int m = char_to_int(message[i]);
        encrypted[i] = mod_exp(m, e, n);
        printf("Encrypted '%c' -> %d\n", message[i], encrypted[i]);
    }

    // Attacker brute-forces all 0–25 values
    printf("\nAttacker brute-forces possible values:\n");
    for (i = 0; i < strlen(message); i++) {
        for ( j = 0; j < 26; j++) {
            if (mod_exp(j, e, n) == encrypted[i]) {
                printf("Cipher %d => '%c'\n", encrypted[i], int_to_char(j));
                break;
            }
        }
    }

    return 0;
}

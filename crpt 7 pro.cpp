#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Build reverse mapping from key
void build_decryption_key(const char *key, char *decrypt_key) {
    for (int i = 0; i < 26; i++) {
        decrypt_key[toupper(key[i]) - 'A'] = 'A' + i;
    }
}

// Decrypt the given ciphertext
void decrypt(const char *ciphertext, const char *key, char *plaintext) {
    char decrypt_key[26];
    build_decryption_key(key, decrypt_key);

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (isupper(c)) {
            plaintext[i] = decrypt_key[c - 'A'];
        } else if (islower(c)) {
            plaintext[i] = tolower(decrypt_key[toupper(c) - 'A']);
        } else {
            plaintext[i] = c;
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    const char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM"; // Substitution key
    const char ciphertext[] = "ITSSG VGKR";           // Encrypted "HELLO WORD"
    char plaintext[100];

    decrypt(ciphertext, key, plaintext);

    printf("Decrypted message: %s\n", plaintext); // Should print "HELLO WORD"

    return 0;
}

#include <stdio.h>
#include <stdint.h>

#define NUM_ROUNDS 16

// Simplified DES Key schedule and round function (not full DES)
void generate_keys(uint64_t key, uint64_t keys[NUM_ROUNDS]) {
    // Simple key schedule for illustration (not full DES key generation)
    for (int i = 0; i < NUM_ROUNDS; i++) {
        keys[i] = key ^ i;  // Simplified key generation logic
    }
}

uint64_t des_round(uint64_t left, uint64_t right, uint64_t key) {
    return left ^ (right ^ key);  // Simplified round function (not full DES)
}

uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {
    uint64_t keys[NUM_ROUNDS];
    generate_keys(key, keys);  // Generate round keys

    uint32_t left = ciphertext >> 32, right = ciphertext & 0xFFFFFFFF;
    for (int i = NUM_ROUNDS - 1; i >= 0; i--) {
        uint64_t new_left = right;
        right = left ^ des_round(left, right, keys[i]);
        left = new_left;
    }
    return ((uint64_t)left << 32) | right;  // Combine left and right halves
}

int main() {
    uint64_t key = 0x133457799BBCDFF1, ciphertext = 0x85E813540F0AB405;
    uint64_t decrypted = des_decrypt(ciphertext, key);
    printf("Decrypted: %llx\n", decrypted);
    return 0;
}


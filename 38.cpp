#include <stdio.h>

// Hill cipher 2x2 encrypt: C = P * K mod 26
void encrypt(int *p, int *k, int *c) {
    c[0] = (p[0]*k[0] + p[1]*k[2]) % 26;
    c[1] = (p[0]*k[1] + p[1]*k[3]) % 26;
}

// Given P and C known, solve for K if P invertible mod 26

int modInverse(int a, int m) {
    for(int x=1; x<m; x++) if((a*x)%m==1) return x;
    return -1;
}

int main() {
    int P[4] = {7,4,11,11}; // plaintext vectors as columns
    int C[4] = {1,2,3,4};   // ciphertext vectors as columns
    // Solve K = P_inv * C mod 26
    // For brevity, this is left as an exercise
    printf("Hill cipher known plaintext attack is complex; implement matrix inversion mod 26.\n");
    return 0;
}


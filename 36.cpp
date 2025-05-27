#include <stdio.h>

int modInverse(int a, int m) {
    for(int x=1; x<m; x++) if((a*x)%m==1) return x;
    return -1;
}

void encrypt(char *pt, int a, int b, char *ct, int len) {
    for(int i=0; i<len; i++) {
        int p = pt[i] - 'A';
        ct[i] = ((a*p + b) % 26) + 'A';
    }
    ct[len]=0;
}

void decrypt(char *ct, int a, int b, char *pt, int len) {
    int ainv = modInverse(a,26);
    for(int i=0; i<len; i++) {
        int c = ct[i] - 'A';
        pt[i] = ((ainv*(c - b + 26)) % 26) + 'A';
    }
    pt[len] = 0;
}

int main() {
    char pt[] = "HELLO";
    char ct[10], dt[10];
    int a=5, b=8;  // a must be coprime to 26
    encrypt(pt,a,b,ct,5);
    printf("Enc: %s\n", ct);
    decrypt(ct,a,b,dt,5);
    printf("Dec: %s\n", dt);
    return 0;
}


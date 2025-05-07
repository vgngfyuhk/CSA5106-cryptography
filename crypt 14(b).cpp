#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

void find_key(char *c, char *p, int *k) {
    for (int i = 0; c[i]; i++)
        k[i] = (c[i] - p[i] + ALPHABET_SIZE) % ALPHABET_SIZE;
}

int main() {
    char c[] = "send more money", p[] = "cash not needed";
    int k[50];
    find_key(c, p, k);
    for (int i = 0; c[i]; i++) printf("%d ", k[i]);
    return 0;
}


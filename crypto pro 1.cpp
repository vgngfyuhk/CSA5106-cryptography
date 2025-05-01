#include <stdio.h>

int main() {
    char c;
    int k;
    printf("Enter shift (1-25): ");
    scanf("%d", &k);
    getchar(); // consume newline
    printf("Enter text: ");
    while ((c = getchar()) != '\n') {
        if (c >= 'a' && c <= 'z')
            c = ((c - 'a' + k) % 26) + 'a';
        else if (c >= 'A' && c <= 'Z')
            c = ((c - 'A' + k) % 26) + 'A';
        putchar(c);
    }
    printf("\n");
    return 0;
}

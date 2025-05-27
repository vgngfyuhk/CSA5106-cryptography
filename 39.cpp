#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int key;
    double score;
} KeyScore;

double english_freq[26] = {8.2,1.5,2.8,4.3,13,2.2,2,6.1,7,0.15,0.77,4,2.4,6.7,7.5,1.9,0.095,6,6.3,9.1,2.8,0.98,2.4,0.15,2,0.074};

double score(char *text) {
    int freq[26] = {0};
    int len = 0;
    for(int i=0; text[i]; i++) {
        if(text[i] >= 'A' && text[i] <= 'Z') {
            freq[text[i]-'A']++;
            len++;
        }
    }
    if(len == 0) return 0.0;
    double s = 0;
    for(int i=0; i<26; i++)
        s += ((double)freq[i]/len)*english_freq[i];
    return s;
}

void decrypt(char *ct, int key, char *pt) {
    int i = 0;
    while(ct[i]) {
        if(ct[i] >= 'A' && ct[i] <= 'Z') {
            pt[i] = ((ct[i] - 'A' - key + 26) % 26) + 'A';
        } else {
            pt[i] = ct[i];
        }
        i++;
    }
    pt[i] = '\0';
}

int main() {
    char ct[] = "KHOORZRUOG"; // encrypted "HELLOWORLD" with key=3
    char pt[100];
    KeyScore results[26];

    for(int k=0; k<26; k++) {
        decrypt(ct, k, pt);
        results[k].key = k;
        results[k].score = score(pt);
    }

    // Sort descending by score (simple bubble sort)
    for(int i=0; i<25; i++) {
        for(int j=i+1; j<26; j++) {
            if(results[j].score > results[i].score) {
                KeyScore tmp = results[i];
                results[i] = results[j];
                results[j] = tmp;
            }
        }
    }

    printf("Top 10 keys and plaintexts:\n");
    for(int i=0; i<10; i++) {
        decrypt(ct, results[i].key, pt);
        printf("Key=%2d: %s\n", results[i].key, pt);
    }
    return 0;
}


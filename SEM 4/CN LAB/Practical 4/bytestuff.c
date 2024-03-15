#include <stdio.h>
#include <string.h>

void bitStuffing(char* data, char flag, int numBits) {
    int count = 0;
    int len = strlen(data);

    printf("Stuffed Data: ");

    for (int i = 0; i < len; i++) {
        if (data[i] == flag) {
            count = 0;
        }

        if (data[i] == '1') {
            count++;
        } else {
            count = 0;
        }

        printf("%c", data[i]);

        if (count == numBits) {
            printf("0");
            count = 0;
        }
    }

    printf("\n");
}

void bitDestuffing(char* data, char flag, int numBits) {
    int count = 0;
    int len = strlen(data);

    printf("Destuffed Data: ");

    for (int i = 0; i < len; i++) {
        if (data[i] == flag) {
            count = 0;
        }

        printf("%c", data[i]);

        if (data[i] == '1') {
            count++;
        } else {
            count = 0;
        }

        if (count == numBits && i+1 < len && data[i+1] == '0') {
            i++;
            count = 0;
        }
    }

    printf("\n");
}

int main() {
    char data[100];
    char flag;
    int numBits;

    printf("Enter the data to stuff: ");
    scanf("%s", data);

    printf("Enter the flag character: ");
    scanf(" %c", &flag);

    printf("Enter the number of bits after which to stuff: ");
    scanf("%d", &numBits);

    bitStuffing(data, flag, numBits);
    bitDestuffing(data, flag, numBits);

    return 0;
}

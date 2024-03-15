#include <stdio.h>
#include <string.h>

#define FLAG "01000010"
#define ESCAPE "11100110"
#define XOR 0x20

void bitStuffing(char* data, int len, char* stuffedData, int* stuffedLen) {
    int i, j;
    int count = 0;

    strcpy(stuffedData, FLAG);
    j = strlen(FLAG);

    for (i = 0; i < len; i++) {
        if (data[i] == FLAG[0] && strncmp(&data[i], FLAG, strlen(FLAG)) == 0) {
            strcpy(&stuffedData[j], ESCAPE);
            j += strlen(ESCAPE);
            strcpy(&stuffedData[j], FLAG);
            j += strlen(FLAG);
        } else if (data[i] == ESCAPE[0] && strncmp(&data[i], ESCAPE, strlen(ESCAPE)) == 0) {
            strcpy(&stuffedData[j], ESCAPE);
            j += strlen(ESCAPE);
            strcpy(&stuffedData[j], ESCAPE);
            j += strlen(ESCAPE);
        } else {
            stuffedData[j++] = data[i];
        }
    }

    strcpy(&stuffedData[j], FLAG);
    j += strlen(FLAG);
    *stuffedLen = j;
}

void bitDestuffing(char* stuffedData, int len, char* destuffedData, int* destuffedLen) {
    int i, j;
    int count = 0;

    j = 0;

    for (i = strlen(FLAG); i < len - strlen(FLAG); i++) {
        if (stuffedData[i] == ESCAPE[0] && strncmp(&stuffedData[i], ESCAPE, strlen(ESCAPE)) == 0) {
            if (stuffedData[i + strlen(ESCAPE)] == FLAG[0] && strncmp(&stuffedData[i + strlen(ESCAPE)], FLAG, strlen(FLAG)) == 0) {
                strcpy(&destuffedData[j], FLAG);
                j += strlen(FLAG);
                i += strlen(ESCAPE);
            } else if (stuffedData[i + strlen(ESCAPE)] == ESCAPE[0] && strncmp(&stuffedData[i + strlen(ESCAPE)], ESCAPE, strlen(ESCAPE)) == 0) {
                strcpy(&destuffedData[j], ESCAPE);
                j += strlen(ESCAPE);
                i += strlen(ESCAPE);
            }
        } else {
            destuffedData[j++] = stuffedData[i];
        }
    }

    // Remove extra flag and escape sequences from destuffed data
    int destuffedDataLen = j;
    int destuffedDataIndex = 0;
    int flagLen = strlen(FLAG);
    int escapeLen = strlen(ESCAPE);

    while (destuffedDataIndex < destuffedDataLen) {
        if (destuffedData[destuffedDataIndex] == FLAG[0] && strncmp(&destuffedData[destuffedDataIndex], FLAG, flagLen) == 0) {
            destuffedDataIndex += flagLen;
        } else if (destuffedData[destuffedDataIndex] == ESCAPE[0] && strncmp(&destuffedData[destuffedDataIndex], ESCAPE, escapeLen) == 0) {
            destuffedDataIndex += escapeLen;
        } else {
            destuffedData[j++] = destuffedData[destuffedDataIndex++];
        }
    }

    *destuffedLen = j;
    
    // Null-terminate the destuffedData
    destuffedData[j] = '\0';
}

int main() {
    char data[100];
    char stuffedData[200];
    char destuffedData[100];
    int len, stuffedLen, destuffedLen;

    printf("Enter the data stream: ");
    fgets(data, sizeof(data), stdin);
    len = strlen(data);

    // Remove newline character from input
    if (data[len - 1] == '\n') {
        data[len - 1] = '\0';
        len--;
    }

    bitStuffing(data, len, stuffedData, &stuffedLen);
    bitDestuffing(stuffedData, stuffedLen, destuffedData, &destuffedLen);

    printf("Stuffed data: %s\n", stuffedData);
    printf("Destuffed data: %s\n", destuffedData);

    return 0;
}

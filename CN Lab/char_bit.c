/*1.	Implement the data link layer framing methods such as character-stuffing and bit stuffing.
input =
1
kmit
output =
Choose Framing Method:
1. Character Stuffing
2. Bit Stuffing
Enter your choice:
Enter the data string:
Character Stuffed Output: $kmit$

input =
2
110011001100
output =
Choose Framing Method:
1. Character Stuffing
2. Bit Stuffing
Enter your choice:
Enter the data string:
Bit Stuffed Output: 01111110 110011001100 01111110*/



#include <stdio.h>
#include <string.h>

#define FLAG '$'
#define ESC '@'

void characterStuffing(char data[]) {
    char stuffed[200];
    int i, j = 0;

    stuffed[j++] = FLAG;  // starting flag

    for (i = 0; i < strlen(data); i++) {
        if (data[i] == FLAG || data[i] == ESC) {
            stuffed[j++] = ESC;  // escape character
        }
        stuffed[j++] = data[i];
    }

    stuffed[j++] = FLAG;  // ending flag
    stuffed[j] = '\0';

    printf("Character Stuffed Output: %s\n", stuffed);
}

void bitStuffing(char data[]) {
    char stuffed[300];
    char flag[] = "01111110";
    int i, j = 0, count = 0;

    // add starting flag
    strcpy(stuffed, flag);
    j = strlen(flag);

    for (i = 0; i < strlen(data); i++) {
        stuffed[j++] = data[i];
        if (data[i] == '1') {
            count++;
            if (count == 5) {
                stuffed[j++] = '0'; // stuff a 0 after five consecutive 1s
                count = 0;
            }
        } else {
            count = 0;
        }
    }

    // add ending flag
    strcat(stuffed, flag);

    printf("Bit Stuffed Output: %s\n", stuffed);
}

int main() {
    int choice;
    char data[100];

    printf("Choose Framing Method:\n");
    printf("1. Character Stuffing\n");
    printf("2. Bit Stuffing\n");
    printf("Enter your choice:\n");
    scanf("%d", &choice);

    printf("Enter the data string:\n");
    scanf("%s", data);

    switch (choice) {
        case 1:
            characterStuffing(data);
            break;
        case 2:
            bitStuffing(data);
            break;
        default:
            printf("Invalid choice!\n");
    }
    return 0;
}

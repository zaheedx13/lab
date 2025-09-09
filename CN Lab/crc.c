/*Write a program to compute CRC code for the polynomials. 
Enter data to be transmitted: 11010011101100 
Enter the Generating polynomial: 1011
Data padded with n-1 zeros : 11010011101100000  
CRC or Check value is : 100 
Final data to be sent : 11010011101100100 
Enter the received data: 1101100111111
Data received: 1101100111111 
Error detected */



#include <stdio.h>
#include <string.h>

void mod2div(char *dividend, const char *generator) {
    int n = strlen(dividend), g = strlen(generator);
    for (int i = 0; i <= n - g; i++) {
        if (dividend[i] == '1') {
            for (int j = 0; j < g; j++) {
                dividend[i + j] = ((dividend[i + j] - '0') ^ (generator[j] - '0')) + '0';
            }
        }
    }
}

int main() {
    char data[2048], gen[2048], recv[2048];
    char padded[4096], work[4096], crc[2048], finalData[4096];

    printf("Enter data to be transmitted: ");
    scanf("%2047s", data);

    printf("\n Enter the Generating polynomial: ");
    scanf("%2047s", gen);

    int dataLen = strlen(data);
    int genLen = strlen(gen);

    strcpy(padded, data);
    for (int i = 0; i < genLen - 1; i++) padded[dataLen + i] = '0';
    padded[dataLen + genLen - 1] = '\0';
    printf(" Data padded with n-1 zeros : %s\n", padded);

    strcpy(work, padded);
    mod2div(work, gen);

    for (int i = 0; i < genLen - 1; i++) crc[i] = work[dataLen + i];
    crc[genLen - 1] = '\0';

    printf("CRC or Check value is : %s\n", crc);

    strcpy(finalData, data);
    strcat(finalData, crc);
    printf(" Final data to be sent : %s\n", finalData);

    printf("Enter the received data: ");
    scanf("%2047s", recv);

    printf("Data received: %s\n", recv);

    strcpy(work, recv);
    mod2div(work, gen);

    int n = strlen(recv);
    int error = 0;
    for (int i = n - (genLen - 1); i < n; i++) {
        if (work[i] == '1') { error = 1; break; }
    }

    if (error) printf("Error detected\n");
    else printf("No error detected\n");

    return 0;
}

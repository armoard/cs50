#include<stdio.h>
#include<cs50.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
int main(int argc, string argv[])
{
    if(argc != 2 ) {
        printf("Usage ./caesar key\n");
        return 1;
    }

    for(int j = 0 ; j <strlen(argv[1]); j++)
if(!isdigit(argv[1][j])) 
{
    printf("Usage ./caesar key\n");
    return 1;
}

    string plaintext = get_string("plaintext: ");
    int i = atoi(argv[1]);
    printf("ciphertext: ");

 for(int b = 0 ; plaintext[b] != '\0'; b++)
 {
    if (isupper(plaintext[b]))
    {
        printf("%c", (((plaintext[b] - 65) + i)  %26) + 65); // si no hicieras 27 modulo 26 no wrapearias alrededor de a z sino q te pasarias de largo y a seria igual a \ (65+27) 
    }                                                        // si no sumaras 65 printearias %c de 1 que no es una letra
    else if (islower(plaintext[b]))
    {
        printf("%c", (((plaintext[b] - 97) + i)  %26) + 97);
    }
    else {
        printf("%c", plaintext[b]);
    }

 }
printf("\n");
}

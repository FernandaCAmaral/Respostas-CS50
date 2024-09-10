#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//argc = quantos argumentos tem, argv = onde ta os argumentos(index)
int main(int argc, string argv[])
{
    //os argumentos só podem ser 2, 1° ./ceasar e o 2° é a chave numérica que vai ser colocada
    if (argc != 2)
    {
        printf("Usage: ./ceasar key\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        //checagem para ver se o segundo argumento argv[1] é apenas numérico
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./ceasar key\n");
            return 1;
        }
    }
    //transforma o argumento(key) que recebemos como string em integer
    int k = atoi(argv[1]);
    //Pega o texto normal do user
    string plaintext = get_string("Plaintext: ");
    printf("Ciphertext: ");

    //Cifra caracter por caracter do texto
    for (int j = 0, m = strlen(plaintext); j < m; j++)
    {
        if(isupper(plaintext[j]))
        {
            printf("%c", (plaintext[j] - 65 + k) % 26 + 65);
        }
        else if(islower(plaintext[j]))
        {
            printf("%c", (plaintext[j] - 97 + k) % 26 + 97);
        }
        else
        {
            printf("%c", plaintext[j]);
        }
    }
    printf("\n");
    return 0;
}


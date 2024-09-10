#include <cs50.h>
#include <stdio.h>

int get_height(void);

int main(void)
{
    int h = get_height();

    for(int linha = 0; linha < h; linha++)
    {
        //define espaco antes das hashtags
        for(int space = 0; space < h - linha - 1; space++)
        {
            printf(" ");
        }

        //toda vez que a linha increase, a coluna reseta pra 0
        for(int coluna = 0; coluna <= linha; coluna++)
        {
            printf("#");
        }

        printf(" ");
        printf(" ");

        for(int coluna = 0; coluna <= linha; coluna++)
        {
            printf("#");
        }

        printf("\n");
    }
}

//pede o número da altura para o user
int get_height(void)
{
    int n;
    do
    {
        n = get_int("Altura: ");
    }
    while (n < 1 || n > 8);
    return n;
}

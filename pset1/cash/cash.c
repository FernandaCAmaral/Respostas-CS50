#include <cs50.h>
#include <stdio.h>
#include <math.h>

float get_change(void);

int main(void)
{
    float dollars = get_change();
    //transforma o dollar em cents e cents em inteiros
    int cents = round(dollars * 100);
    int coins = 0;
    //supondo que o valor inserido foi 0.41
    //coins = coins(0) + parte inteira da divisão de cents por 25(1)
    coins += cents / 25;
    cents %= 25; //os centavos restantes são o resto da divisão de cents por 25(16)

    coins += cents / 10;
    cents %= 10;

    coins += cents / 5;
    cents %= 5;

    coins += cents / 1;
    cents %= 1;

    printf("Moedas necessárias para o troco: %i\n", coins);
}

//pega a quantidade de dollars do user
float get_change(void)
{
    float dollars;
    do
    {
        dollars = get_float("Digite o troco: ");
    }
    while(dollars < 0);
    return dollars;
}

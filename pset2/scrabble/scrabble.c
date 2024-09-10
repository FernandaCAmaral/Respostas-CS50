#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Solicitar ao usuário duas palavras
    string word1 = get_string("Player1, digite uma palavra: ");
    string word2 = get_string("Player2, sua vez: ");

    // Calcular os pontos de cada palavra
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Imprimir o vencedor
    if (score1 > score2)
    {
        printf("Player1 venceu! Pontos: %i\nPlayer2: %i\n", score1, score2);
    }
    else if (score2 > score1)
    {
        printf("Player2 venceu! Pontos: %i\nPlayer1: %i\n", score2, score1);
    }
    else
    {
        printf("Empate!\nPontos: %i\n", score1);
    }
}

int compute_score(string word)
{
    // Computa e devolve os pontos de cada palavra
    int score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 65];
        }
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 97];
        }
        else
        {
            score += 0;
        }
    }
    return score;
}

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Maximo de voters e candidatos
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferencia[i][j], i = linha = voter, j = coluna = candidatos, [i][j] = valor = preferencia
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// definindo struct para os candidatos: nome, contagem de votos, status de eliminacao
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array de candidate
candidate candidates[MAX_CANDIDATES];

//definir as variaveis voter_count e candidate_count
int voter_count;
int candidate_count;

//prototipos das funcoes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // checagem para ver se os argumentos sao validos
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    // define os valores para as variaveis dentro do array
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Loop para cada voter
    for (int i = 0; i < voter_count; i++)
    {

        // Loop para definir o rank dos candidatos para o voter
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Salva o voto, isso se não for inválido
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // loop que continua ate haver um vencedor ou empate
    while (true)
    {
        // calcula os votos dos candidatos que n foram eliminados
        tabulate();

        //confere se alguem venceu a eleicao
        bool won = print_winner();
        if (won)
        {
            break; //sai do while
        }

        // elimina os candidatos com menor numero de votos
        int min = find_min();
        bool tie = is_tie(min);

        // se empata, todo mundo vence
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // elimina aqueles que tem o menor numero de votos
        eliminate(min);

        // reseta a contagem de votos para 0
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

//salva o indice do candidato na matriz de preferencias do voter
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++) //passa pelos candidatos
    {
        if (strcmp(name, candidates[i].name) == 0) //se o nome existir
        {
            preferences[voter][rank] = i; //salva o indice do candidato na matriz de preferencias do voter
            return true;
        }
    }
    return false;
}

// Calcula votos para os candidatos não eliminados
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++) //Passa pelos voters(loop externo)
    {
        for (int j = 0; j < candidate_count; j++) //Passa pelos candidatos em ordem de preferencia do i voter (loop interno)
        {
            if (candidates[preferences[i][j]].eliminated == false) //se o candidato da matriz de preferencia do voter n estiver eliminado:
            {
               candidates[preferences[i][j]].votes ++; //soma votos
               break; //e sai do loop interno e volta para o externo
            }
        }
    }
    return;
}

// Printa o vencedor da eleição, se houver um
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) //passa pelos candidatos
    {
        if (candidates[i].votes > voter_count / 2) //se os votos forem maior do que a metade do numero de voters
        {
            printf ("The winner is: %s!\n", candidates[i].name);//mostra na tela o nome do vencedor
            return true;
        }
    }
    return false;
}

// retorna o menor numero de votos que um candidato tem
int find_min(void)
{
    int min = voter_count; //definimos um valor de minimo para realizar comparacoes
    for (int i = 0; i < candidate_count; i ++) //passa por todos os candidatos
    {
        if(candidates[i].votes < min && candidates[i].eliminated == false) //se o numero de votos desse candidato for menos que o min
        {
            min = candidates[i].votes; //os votos dele assumem papel de menor numero
        }
    }
    return min;
}

// Retorna true se a eleicao empatar entre os candidatos validos
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++) //passa por todos candidatos
    {
        //se o candidato n estiver eliminado e seu numero de votos for maior que o minimo registrado, n ha empate
        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// elimina os candidatos em ultimo lugar
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min) //se o candidato ter o menor numero entre os outros
        {
            candidates[i].eliminated = true; //eliminado
        }
    }
    return;
}

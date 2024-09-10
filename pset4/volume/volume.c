// modifica o volume de um arquivo .wav

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// número de bytes em um header de arquivo .wav
// o header descreve o arquivo para a máquina
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // confere se foi digitado todos os argumentos necessários
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // abre os arquivos dados como primeiro e segundo argumentos e atribui eles a uma variavel (input e output)
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    //define a variavel factor, que é o 3 argumento que passamos para o terminal - atof = transforma o argumento(string) em float
    float factor = atof(argv[3]);

    // TODO: copia o header do arquivo de input para o de output(não queremos mudar, pois e a descricao do arquivo)

    uint8_t header[HEADER_SIZE]; /*header é lido em bytes (8 bits), criamos um array do tamanho do header e colocamos o tipo uint8_t,
    que armazena por index um inteiro sem sinal, de comprimento 8 bits*/

    /*os dados lidos são colocados no array header,
      sizeof() especifica o tamanho de cada elemento que vai ser lido,
      HEADER_SIZE é o numero de elementos que vao ser lidos,
      o input é de onde vai ser lido*/
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);


    // TODO: le a amostra do arquivo input e escreve os dados atualizados(com volume)no output

    int16_t buffer; /*o arquivo WAV contém uma sequência de amostras, cada uma é composta por único inteiro de 2 bytes (16 bits)
    representando o sinal de áudio em um determinado momento.*/

    //loop por todas as amostras do input, de uma a uma
    while(fread(&buffer, sizeof(int16_t), 1, input) == 1) /*essa funcao retorna o numero de itens lidos,
    como o passo é de um em um, vai retornar o valor 1, ou seja, enquanto ter pelo menos um item, o while permanecera verdadeiro*/
    {
        //aumenta ou diminui o volume
        buffer *= factor;
        //escreve no output o dado atualizado
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // fecha os arquivos
    fclose(input);
    fclose(output);
}

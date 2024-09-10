#include "helpers.h"

// Converte imagem para escala cinza
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //loop pelas linhas
    {
        for(int j = 0; j < width; j++) //loop pelas colunas da linha
        {
            /*Contanto que os valores de vermelho, verde e azul sejam todos iguais, o resultado será tons de cinza variados,
            por isso pegamos a media do pixel e igualamos os rgb's*/
            int pixelavg_rgb = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = pixelavg_rgb;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++) //loop pelas linhas
    {
        for(int j = 0; j < width; j++) //loop pelas colunas da linha
        {
            sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Refletir imagem horizontalmente
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;
    for (int i = 0; i < height; i++) //loop pelas linhas
    {
        for(int j = 0, halfwidth = width / 2; j < halfwidth; j++) //loop ate a metade das colunas da linha
        {
            buffer = image[i][j]; //guarda o pixel original
            image[i][j] = image[i][width - j - 1]; //'transporta' o pixel original para seu lugar inverso na coluna
            image[i][width - j - 1] = buffer; //'transporta' o pixel que estava no lugar inverso do original para o local de comeco do original
        }
    }
    return;
}

// imagem blur
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_replica[height][width];
    for (int i = 0; i < height; i++) //loop pelas linhas
    {
        for(int j = 0; j < width; j++) //loop pelas colunas da linha
        {
            float somaRed = 0, somaGreen = 0, somaBlue = 0, totalPixel = 0;
            for (int around_i = i - 1; around_i < i + 2; around_i++) //loop pelos pixeis ao redor do [i][j]
            {
                for (int around_j = j - 1; around_j < j + 2; around_j++)
                {
                    if (around_i >= 0 && around_j >= 0 && around_i < height && around_j < width)
                    {
                        somaRed += image[around_i][around_j].rgbtRed;
                        somaGreen += image[around_i][around_j].rgbtGreen;
                        somaBlue += image[around_i][around_j].rgbtBlue;
                        totalPixel++;
                    }
                }
            }
            image_replica[i][j].rgbtRed = round(somaRed / totalPixel); //media dos pixels ao redor para dar novo valor de red
            image_replica[i][j].rgbtGreen = round(somaGreen / totalPixel); //media dos pixels ao redor para dar novo valor de green
            image_replica[i][j].rgbtBlue = round(somaBlue / totalPixel); //media dos pixels ao redor para dar novo valor de blue
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_replica[i][j];
        }
    }
    return;
}

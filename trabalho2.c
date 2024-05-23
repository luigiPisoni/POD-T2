#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct hashNode
{
    int value;

    struct hashNode *next;
} HashNode;

// typedef struct hashTable
// {
//     HashNode *first;
// } HashTable;

int main()
{
    FILE *text = fopen("teste.txt", "rt");
    if (text == NULL)
    {
        printf("Erro ao ler o arquivo\n");
        exit(0);
    }
    
    HashNode hashTable[23]; 
    int n; // Cria uma variável que vai armazenar cada um dos valores vindo da lista

    for (int i = 0; i < (sizeof(hashTable)/sizeof(HashNode)); i++) // Vai calcular o tamanho da lista (mesmo sendo um valora padrão)
    {
        fscanf(text, ";", &n);
        fgetc(text);
        printf("%d, ", n);
    }
    
}

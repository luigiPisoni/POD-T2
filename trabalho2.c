#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define M 23 // Tamanho da tabela hash.

typedef struct node
{
    int value;

    struct node *next;
} Node;

typedef struct linkedList
{
    Node *first;
} LinkedList;

// Vai realizar o cálculo do módulo e inserir o valor em uma lista encadeada.
void addNode(LinkedList *hashTable, int toAdd)
{
    int i = toAdd % M; // Realiza o cálculo do módulo do valor, decidindo a posição onde o valor deve ser inserido.

    Node *newNode = malloc(sizeof(Node)); // Alocação de memória para um novo elemento na lista encadeada da posição i.
    newNode->value = toAdd;               // Atribui o valor do número em um nó.
    newNode->next = NULL;                 // Ancora o ponteiro para que não acabe com um valor aleatório.
    if (hashTable[i].first == NULL)       // Caso o primeiro elemento da lista encadeada esteja vazio, adiciona esse primeiro valor.
    {
        hashTable[i].first = newNode; // Atribuição do novo nó ao primeiro elemento da lista encadeada da posição i.
        // printf("adicionou nao existente: %d, ", toAdd);
    }
    else // Caso o primeiro elemento já estiver ocupado, será um caso de colisão da tabela hash.
    {
        // Desse modo, quando houver um caso de colisão, vai percorrer a lista encadeada até o final dela.
        // Ao chegar no final vai adicionar o novo nó.
        Node *node = hashTable[i].first; // Instancia o primeiro nó da lista encadeada.
        while (node->next != NULL)       // Utiliza esse node para percorrer a lista encadeada até o final dela.
        {
            node = node->next; // Dá o próximo passo, fazendo o node se tornar seu sucessor, fazendo "a lista andar".
        }
        node->next = newNode;
        // printf("adicionou ja existente: %d, ", toAdd);
    }
}

// Imprime toda a tabela hash, separando cada índice em uma linha.
// Em caso de conflito, a lista encadeada completa será imprimida ao lado do índice.
void printHashTable(LinkedList *hashTable)
{
    for (int i = 0; i < M; i++) // Percorre toda a tabela hash.
    {
        if (hashTable[i].first == NULL) // Caso o primeiro elemento do índice ser vazio:
        {
            printf("\n[i=%d]-> Sem elementos", i); // Vai imprimir que não existe um valor nessa posição.
        }
        else // Caso contrário:
        {
            printf("\n[i=%d]-> ", i);
            Node *node = hashTable[i].first; // Recebe o primeiro elemento da lista encadeada do índice i.
            while (node != NULL)
            {
                // Caso não haja um próximo valor imprime sem vírgula.
                if (node->next == NULL)
                {
                    printf("%d", node->value);
                }
                // Senão, imprime com vírgula e espaço.
                else
                {
                    printf("%d, ", node->value);
                }
                node = node->next; // Torna o node o seu sucessor;
            }
        }
    }
}

int main()
{
    // Tenta abrir o arquivo onde todos os números estão contidos. Caso não conseguir, printa um erro.
    // Os parâmetros representam o nome do arquivo e o modo, que nesse caso seria r=read e t=text.
    FILE *numeros = fopen("casos_de_teste.txt", "rt");
    if (numeros == NULL)
    {
        printf("Erro ao ler o arquivo.\n");
        exit(0);
    }

    LinkedList hashTable[M];

    // Percorre a tabela hash ainda vazia e ancora os valores do ponteiros
    // para que não apontem para endereços aleatórios da memória.
    for (int i = 0; i < M; i++)
    {
        hashTable[i].first = NULL;
    }

    // Variável que serve de buffer entre o arquivo e tabela hash.
    int paraAdicionar;

    // Percorre o arquivo até encontrar o final dele. Já que o delimitador dos números é ';',
    // o parâmetro format para a função fscanf será '%d;', dizendo que haverá um inteiro acompanhado por um ponto e vírgula.
    // Ao encontrar esse padrão, o valor do número será armazenado na variável paraAdicionar,
    // que será usada logo em seguida como parâmetro para a função addNode.
    while (fscanf(numeros, "%d;", &paraAdicionar) != EOF)
    {
        // Adiciona o nodo na tabela hash.
        addNode(hashTable, paraAdicionar);
    }

    // Imprime a tebela hash inteira.
    printHashTable(hashTable);

    // Fecha a pasta para que libere espaço na memória.
    fclose(numeros);
}

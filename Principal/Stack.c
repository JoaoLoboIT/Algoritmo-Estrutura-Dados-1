#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct item 
{
    int codigo;
    int quantidade;
    char nome[100];
    float preco;
    char descricao[100];

} TProduto;

typedef struct celula 
{
    TProduto item;
    struct celula *prox;

} TCelula;

typedef struct pilha
{
    TCelula *fundo;
    TCelula *topo;
    int tamanho;
} TPilha;

void FPVazia(TPilha *Pilha)
{
    Pilha->fundo = (TCelula *)malloc(sizeof(TCelula));
    Pilha->topo = Pilha->fundo;
    Pilha->fundo->prox = NULL;
    Pilha->tamanho = 0;
}

int Vazia(TPilha Pilha)
{
    return (Pilha.fundo == Pilha.topo);
}

void Empilhar(TProduto x, TPilha *Pilha)
{
    TCelula *Aux;
    Aux = (TCelula *)malloc(sizeof(TCelula));
    Pilha->topo->item = x;
    Aux->prox = Pilha->topo;
    Pilha->topo = Aux;
    Pilha->tamanho++;
}

void Desempilhar(TPilha *Pilha, TProduto *Item)
{
    TCelula *q;
    if (Vazia(*Pilha))
    {
        printf("Erro: lista vazia\n");
        return;
    }
    q = Pilha->topo;
    Pilha->topo = q->prox;
    *Item = q->prox->item;
    free(q);
    Pilha->tamanho--;
}

void LerProduto(TProduto *p)
{
    printf("Digite o codigo do produto: ");
    scanf("%d", &(p->codigo));
    getchar(); 

    printf("Digite o nome do produto: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0'; 

    printf("Digite a descricao do produto: ");
    fgets(p->descricao, sizeof(p->descricao), stdin);
    p->descricao[strcspn(p->descricao, "\n")] = '\0'; 

    printf("Digite o preco do produto: ");
    scanf("%f", &(p->preco));

    printf("Digite a quantidade do produto: ");
    scanf("%d", &(p->quantidade));
}

void ImprimirProduto(TProduto Item)
{
    printf("\n Codigo: %d\n", Item.codigo);
    printf("\n Nome: %s\n", Item.nome);
    printf("\n Descricao: %s\n", Item.descricao);
    printf("\n Preco: %.2f\n", Item.preco);
    printf("\n Quantidade: %d\n", Item.quantidade);
}

void ImprimirPilha(TPilha *P1)
{
    TPilha Paux;
    TProduto x;
    FPVazia(&Paux);
    while (!Vazia(*P1))
    {
        Desempilhar(P1, &x);
        Empilhar(x, &Paux);
    }
    while (!Vazia(Paux))
    {
        Desempilhar(&Paux, &x);
        Empilhar(x, P1);
        ImprimirProduto(x);
    }
    free(Paux.topo);
}

void inverterOrdem(TPilha *P1)
{
    TProduto x;
    TPilha Paux;
    FPVazia(&Paux);

    while (!Vazia(*P1))
    {
        Desempilhar(P1, &x);
        Empilhar(x, &Paux);
    }

    ImprimirPilha(&Paux);

    while (!Vazia(Paux))
    {
        Desempilhar(&Paux, &x);
        Empilhar(x, P1);
    }
}

void converterNumero(int numero, int base)
{

    if (base < 2 || base > 9)
    {
        printf("Base inválida. Deve estar entre 2 e 9.\n");
        return;
    }
    TPilha pilha;
    TPilha pilha2;
    FPVazia(&pilha);
    FPVazia(&pilha2);
    TProduto aux;

    while (numero > 0)
    {
        aux.codigo = numero % base;
        Empilhar(aux, &pilha);
        numero /= base;
    }

    while (!Vazia(pilha))
    {
        Desempilhar(&pilha, &aux);
        Empilhar(aux, &pilha2);
    }

    ImprimirPilha(&pilha2);
}

void torreDeHanoi(TPilha *p1, TPilha *p2, int tamanho)
{
    TPilha Paux;
    TProduto x;
    FPVazia(&Paux);

    // p1 -> pino da fonte
    // p2 -> pino de destino

    if (tamanho % 2 != 0)
    {
        for (int i = 1; i < (pow(2, tamanho) - 1); i++)
        {
            if (i % 3 == 1)
            {
                Desempilhar(p1, &x);
                Empilhar(x, p2);
            }
            else if (i % 3 == 2)
            {
                Desempilhar(p1, &x);
                Empilhar(x, &Paux);
            }
            else if (i % 3 == 0)
            {
                Desempilhar(&Paux, &x);
                Empilhar(x, p2);
            }
        }
    }
    else
    {
        for (int i = 1; i < (pow(2, tamanho)) - 1; i++)
        {
            if (i % 3 == 1)
            {
                Desempilhar(p1, &x);
                Empilhar(x, &Paux);
            }
            else if (i % 3 == 2)
            {
                Desempilhar(p1, &x);
                Empilhar(x, p2);
            }
            else if (i % 3 == 0)
            {
                Desempilhar(p2, &x);
                Empilhar(x, &Paux);
            }
        }
    }
}

int VeririficarParentesBalancados(char string[])
{
    TPilha pilha;
    FPVazia2(&pilha);
    TProduto aux;
    int tam = strlen(string);
    

    for (int i = 0; i < tam; i++)
    {
        aux.nome = string[i];   
        if(aux.nome == ')') {

            int elementos = 0;
            while (aux.nome != '(')
            {
                elementos++;
                Desempilhar2(&aux, &pilha);
            }
            if (elementos < 1) {
                return 1;
            }
        }
        else {
            Empilhar2(aux, &pilha);
        }
    }

    Liberar2(&pilha);
    return 0;
}


int stringParenteses1(TPilha *p1, int tamanho)
{
    TProduto x;
    TPilha Paux, p3;
    FPVazia(&p3);
    FPVazia(&Paux);
    int cont = 0;
    int a = 0;
    int b = 0;
    while (!Vazia(*p1))
    {
        Desempilhar(p1, &x);
        for (int i = 0; i < tamanho; i++)
        {
            if (x.descricao[i] == '(' && x.descricao[i + 1] == ')')
            {
                Empilhar(x, &p3);
                cont += 2;
            }
            else if (x.descricao[i] == '(' && x.descricao[i + 1] == '(')
            {
                int j = i;
                while (x.descricao[j] == '(')
                {
                    a++;
                    j++;
                }
                while (x.descricao[j] == ')' && b < a)
                {
                    b++;
                    j++;
                }
                if (a == b)
                {
                    Empilhar(x, &p3);
                    cont += a + b;
                    i = j;
                }
            }
        }
        Empilhar(x, &Paux);
    }
    while (!Vazia(*p1))
    {
        Desempilhar(&Paux, &x);
        Empilhar(x, p1);
    }
    return cont;
}

void inverte(TPilha *p1)
{

    TProduto x, y;
    TPilha Paux;
    FPVazia(&Paux);
    int j = 1;
    int n = p1->tamanho;
    for (int i = 0; i < p1->tamanho; i++)
    {
        Desempilhar(p1, &x);
        y = x;
        for (int k = 0; k < n - j; k++)
        {
            Desempilhar(p1, &x);
            Empilhar(x, &Paux);
        }
        j++;
        Empilhar(y, p1);
        while(!Vazia(Paux)){
            Desempilhar(&Paux, &x);
            Empilhar(x, p1);
        }
    }
    
}

int main()
{
    TPilha Pilha1, Pilha2;
    FPVazia(&Pilha1);
    FPVazia(&Pilha2);

    TProduto p;
    int opc;
    int tamanho;
    do
    {
        printf("\n-----------------------------");
        printf("\nDigite qual opcao voce deseja fazer:\n");
        printf("-----------------------------");
        printf("\n1 - Empilhar produto");
        printf("\n2 - Desempilhar produto");
        printf("\n3 - Imprimir a pilha");
        printf("\n4 - Inverter ordem da pilha");
        printf("\n5 - Torre");
        printf("\n6 - Exercicio 4");
        printf("\n7 - Exercicio 5");
        printf("\n8 - Sair do programa");
        printf("\n-----------------------------\n");
        scanf("%d", &opc);
        getchar(); 

        switch (opc)
        {
        case 1:
            printf("\nQuantos produtos vão ser inseridos?");
            scanf("%d", &tamanho);

            for (int i = 0; i < tamanho; i++)
            {
                printf("\nDigite os dados do produto a ser empilhado:\n");
                LerProduto(&p);
                Empilhar(p, &Pilha1);
                printf("\nProduto empilhado com sucesso!\n");
            }
            break;

        case 2:
            if (Vazia(Pilha1))
            {
                printf("\nErro: Pilha vazia\n");
            }
            else
            {
                Desempilhar(&Pilha1, &p);
                printf("\nProduto desempilhado com sucesso!\nInformacoes:\n");
                ImprimirProduto(p);
            }
            break;

        case 3:
            printf("\nImprimindo pilha:\n");
            ImprimirPilha(&Pilha1);
            break;

        case 4:
            inverte(&Pilha1);
            printf("\nOrdem da pilha invertida com sucesso!\n");
            ImprimirPilha(&Pilha1);
            break;

        case 5:
            torreDeHanoi(&Pilha1, &Pilha2, Pilha1.tamanho);
            ImprimirPilha(&Pilha2);
            break;

        case 6:
            int resultado = stringParenteses1(&Pilha1, 9);
            printf("%d", resultado);
            break;
        case 7:
            // int parentesDuplicados = parentesesDuplicados(&Pilha1);
            // printf("%d", parentesesDuplicados);
            break;
        case 8:
            printf("\nSaindo do programa...\n");
            break;

        default:
            printf("\nOpcao invalida.\n");
            break;
        }
    } while (opc != 8);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item 
{
    int codigo;
    int quantidade;
    char nome[100];
    float preco;
    char descricao[100];
    int prioridade;
    char binario[100];

} TProduto;

typedef struct celula 
{
    TProduto item;
    struct celula *prox;

} TCelula;

typedef struct fila
{
    TCelula *frente;
    TCelula *tras;
    int tamanho;
} TFila;

typedef struct filaprior
{
    TFila FilaP1;
    TFila FilaP2;
    TFila FilaP3;
    int tamanho;
} TFilaPrioridade;

void EnQueue(TFilaPrioridade* fila, TProduto x){
    if(x.prioridade == 1)
        Enfileirar(x, &fila->FilaP3);
    if(x.prioridade == 2)
        Enfileirar(x, &fila->FilaP2);
    if(x.prioridade == 3)
        Enfileirar(x, &fila->FilaP1);

}



void FFVazia(TFila *Fila)
{
    Fila->frente = (TCelula *)malloc(sizeof(TCelula));
    Fila->tras = Fila->frente;
    Fila->frente->prox = NULL;
    Fila->tamanho = 0;
}

int Vazia(TFila Fila)
{
    return (Fila.frente == Fila.tras);
}

void Enfileirar(TProduto x, TFila *Fila)
{
    Fila->tras->prox = (TCelula *)malloc(sizeof(TCelula));
    Fila->tras = Fila->tras->prox;
    Fila->tras->item = x;
    Fila->tras->prox = NULL;
    Fila->tamanho++;
}

void Desinfileirar(TFila *Fila, TProduto *Item)
{
    TCelula *aux;
    if (!Vazia(*Fila))
    {
        aux = Fila->frente->prox;
        Fila->frente->prox = aux->prox;
        *Item = aux->item; // ??
        free(aux);
        if (Fila->frente->prox == NULL)
            Fila->tras = Fila->frente;
        Fila->tamanho--;
    }
}

void LerProduto(TProduto *Item)
{
    printf("\n Digite o codigo do produto: \n");
    fflush(stdin);
    scanf("%d", &Item->codigo);
    getchar();

    printf("\n Digite o nome do produto: \n");
    fflush(stdin);
    fgets(Item->nome, 100, stdin);

    printf("\n Digite a descricao:\n");
    fflush(stdin);
    fgets(Item->descricao, 100, stdin);

    printf("\n Digite o valor do produto: \n");
    fflush(stdin);
    scanf("%f", &Item->preco);

    printf("\n Digite a quatidade:\n");
    fflush(stdin);
    scanf("%d", &Item->quantidade);

    printf("\n Digite a prioridade(1 a 3): \n");
    fflush(stdin);
    scanf("%d", &Item->prioridade);
    getchar();
}

void ImprimirProduto(TProduto Item)
{
    printf("\n Codigo: %d\n", Item.codigo);
    printf("\n Nome: %s\n", Item.nome);
    printf("\n Descricao: %s\n", Item.descricao);
    printf("\n Preco: %.2f\n", Item.preco);
    printf("\n Quantidade: %d\n", Item.quantidade);
}

void imprimirFila(TFila *Fila)
{
    TProduto x;
    TFila Faux;
    FFVazia(&Faux);
    int i, n = Fila->tamanho;
    for (i = 0; i < n; i++)
    {
        Desinfileirar(Fila, &x);
        ImprimirProduto(x);
        Enfileirar(x, Fila);
    }
    while (!Vazia(Faux))
    {
        Desinfileirar(&Faux, &x);
        Enfileirar(x, Fila);
    }
    free(Faux.frente);
}

void ImprimirBinario(TFila *Fila)
{
    TProduto x;
    TFila Faux;
    FFVazia(&Faux);
    int i, n = Fila->tamanho;
    for (i = 0; i < n; i++)
    {
        Desinfileirar(Fila, &x);
        printf("\n Descricao: %s\n", x.descricao);
        Enfileirar(x, Fila);
    }
    while (!Vazia(Faux))
    {
        Desinfileirar(&Faux, &x);
        Enfileirar(x, Fila);
    }
    free(Faux.frente);
}

int PesquisarFila(TFila *Fila, TProduto *Item)
{
    TFila Faux;
    FFVazia(&Faux);
    int flag = 0;
    TProduto x;
    while (!Vazia(*Fila))
    {
        Desinfileirar(Fila, &x);
        if (!strcmp(x.nome, Item->nome))
        {
            flag = 1;
            *Item = x;
        }
        Enfileirar(x, &Faux);
    }
    while (!Vazia(Faux))
    {
        Desinfileirar(&Faux, &x);
        Enfileirar(x, Fila);
    }
    if (flag == 0)
    {
        Item->codigo = -1;
    }
    return flag;
}

void Liberar(TFila *Fila)
{
    TProduto x;
    while (!Vazia(*Fila))
    {
        Desinfileirar(Fila, &x);
    }
    free(Fila->frente);
}

void intersecao2(TFila *f1, TFila *f2, TFila *f3)
{
    TProduto x, y;
    TFila faux1, faux2;
    FFVazia(&faux1);
    FFVazia(&faux2);
    while (!Vazia(*f1))
    {
        Desinfileirar(f1, &x);
        while (!Vazia(*f2))
        {
            Desinfileirar(f2, &y);
            if (strcmp(x.nome, y.nome) == 0)
            {
                Enfileirar(x, f3);
            }
            Enfileirar(y, &faux2);
        }
        while (!Vazia(faux2))
        {
            Desinfileirar(&faux2, &y);
            Enfileirar(y, f2);
        }
        Enfileirar(x, &faux1);
    }
    while (!Vazia(faux1))
    {
        Desinfileirar(&faux1, &x);
        Enfileirar(x, f1);
    }
}

void diferenca2(TFila *f1, TFila *f2, TFila *f3)
{
    TProduto x, y;
    TFila faux1, faux2;
    FFVazia(&faux1);
    FFVazia(&faux2);
    while (!Vazia(*f1))
    {
        Desinfileirar(f1, &x);
        while (!Vazia(*f2))
        {
            Desinfileirar(f2, &y);
            if (x.codigo != y.codigo)
            {
                Enfileirar(x, f3);
            }
            Enfileirar(y, &faux2);
        }
        while (!Vazia(faux2))
        {
            Desinfileirar(&faux2, &y);
            Enfileirar(y, f2);
        }
        Enfileirar(x, f1);
    }
    while (!Vazia(faux1))
    {
        Desinfileirar(&faux1, &x);
        Enfileirar(x, f1);
    }
}

int verificaSeDuasIguais(TFila f1, TFila f2)
{
    TFila Faux1, Faux2;
    FFVazia(&Faux1);
    FFVazia(&Faux2);
    int cont = 0;
    TProduto x, y;
    if (f1.tamanho == f2.tamanho)
    {
        while (!Vazia(f1))
        {
            Desinfileirar(&f1, &x);
            while (!Vazia(f2))
            {
                Desinfileirar(&f2, &y);
                if (x.codigo == y.codigo)
                {
                    cont++;
                }
                Enfileirar(y, &Faux2);
            }
            while (!Vazia(Faux2))
            {
                Desinfileirar(&Faux2, &y);
                Enfileirar(y, &f2);
            }
            Enfileirar(x, &Faux1);
        }
        if (cont == Faux1.tamanho) 
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int compararDuasFilas(TFila *Fila1, TFila *Fila2)
{
    if (Fila1->tamanho != Fila2->tamanho)
    {
        return 0;
    }

    TFila Faux1, Faux2;
    FFVazia(&Faux1);
    FFVazia(&Faux2);
    TProduto x, y;

    int iguais = 1;

    while (!Vazia(*Fila1))
    {
        Desinfileirar(Fila1, &x);
        Desinfileirar(Fila2, &y);

        Enfileirar(x, &Faux1);
        Enfileirar(y, &Faux2);

        if (x.codigo != y.codigo)
        {
            iguais = 0;
        }
    }

    while (!Vazia(Faux1))
    {
        Desinfileirar(&Faux1, &x);
        Enfileirar(x, Fila1);
    }

    while (!Vazia(Faux2))
    {
        Desinfileirar(&Faux2, &y);
        Enfileirar(y, Fila2);
    }

    return iguais;
}

void intersecao(TFila *Fila1, TFila *Fila2, TFila *Fila3)
{
    TProduto x, y;
    TFila Faux1, Faux2;
    FFVazia(&Faux1);
    FFVazia(&Faux2);
    while (!Vazia(*Fila1))
    {
        Desinfileirar(Fila1, &x);
        Enfileirar(x, &Faux1);
        while (!Vazia(*Fila2))
        {
            Desinfileirar(Fila2, &y);
            Enfileirar(y, &Faux2);

            if (y.codigo == x.codigo)
            {
                Enfileirar(x, Fila3);
            }
        }
        while (!Vazia(Faux2))
        {
            Desinfileirar(&Faux2, &y);
            Enfileirar(y, Fila2);
        }
    }
    while (!Vazia(Faux1))
    {
        Desinfileirar(&Faux1, &x);
        Enfileirar(x, Fila1);
    }
}

void diferenca(TFila *F1, TFila *F2, TFila *F3)
{
    TProduto x, y;
    TProduto aux;
    TFila Faux1, Faux2;
    FFVazia(&Faux1);
    FFVazia(&Faux2);
    while (!Vazia(*F1))
    {
        Desinfileirar(F1, &x);
        Enfileirar(x, &Faux1);
        aux = x;
        if (!PesquisarFila(F2, &x))
        {
            x.codigo = aux.codigo;
            Enfileirar(x, F3);
        }
    }
    while (!Vazia(Faux1))
    {
        Desinfileirar(&Faux1, &x);
        Enfileirar(x, F1);
    }
    while (!Vazia(Faux2))
    {
        Desinfileirar(&Faux2, &y);
        Enfileirar(y, F2);
    }
}

void EnQueue(TFila *Fila, TProduto item)
{
    if (Vazia(*Fila))
    {
        Enfileirar(item, Fila);
    }
    TFila Faux;
    FFVazia(&Faux);
    TProduto x;
    int inserido = 0;
    while (!Vazia(*Fila))
    {
        Desinfileirar(Fila, &x);
        if (item.prioridade > x.prioridade && inserido == 0)
        {
            Enfileirar(item, &Faux);
            inserido = 1;
        }
        Enfileirar(x, &Faux);
    }
    if (inserido == 0)
    {
        Enfileirar(item, &Faux);
    }
    while (!Vazia(Faux))
    {
        Desinfileirar(&Faux, &x);
        Enfileirar(x, Fila);
    }
}

void CoverterBinario(TFila *fila, int n)
{
    TProduto binario;
    int flag = 0;
    printf("0 ");
    if (Vazia(*fila))
    {
        strcpy(binario.descricao, "1");
        Enfileirar(binario, fila);
    }
    if (n != 0)
    {
        printf("%s ", binario.descricao);
    }
    while (flag < (n / 2))
    {
        TProduto binario0, binario1;
        Desinfileirar(fila, &binario);
        strcpy(binario0.descricao, binario.descricao);
        strcat(binario0.descricao, "0");
        strcpy(binario1.descricao, binario.descricao);
        strcat(binario1.descricao, "1");

        printf("%s ", binario0.descricao);

        if (flag != ((n / 2) - 1) || n % 2 != 0)
        {
            printf("%s ", binario1.descricao);
        }
        Enfileirar(binario0, fila);
        Enfileirar(binario1, fila);
        flag += 1;
    }
}

int main()
{
    TProduto x;
    TFila F1;
    TFila F2;
    TFila F3;
    FFVazia(&F2);
    FFVazia(&F3);
    FFVazia(&F1);

    int tamanho;
    int opc;
    int F;

    do
    {
        printf("\n--------------------------------------");
        printf("\nDigite a opcao que deseja fazer: \n");
        printf("--------------------------------------");
        printf("\n1 - Inserir produtos na fila");
        printf("\n2 - Imprimir fila");
        printf("\n3 - Imprimir produto");
        printf("\n4 - Pesquisar produto na fila");
        printf("\n5 - Comparar se duas filas sao iguais");
        printf("\n6 - Liberar fila");
        printf("\n7 - Fazer uma intersecao");
        printf("\n8 - Diferenca entre duas filas");
        printf("\n9 - Binario");
        printf("\n10 - Sair do programa");
        printf("\n--------------------------------------\n");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            printf("\nEscolha a fila (1 para F1, 2 para F2): \n");
            scanf("%d", &F);
            if (F == 1)
            {
                printf("\nDigite a quantidade de produtos que deseja inserir: \n");
                scanf("%d", &tamanho);
                for (int i = 0; i < tamanho; i++)
                {
                    LerProduto(&x);
                    Enfileirar(x, &F1);
                }
            }
            else if (F == 2)
            {
                printf("\nDigite a quantidade de produtos que deseja inserir: \n");
                scanf("%d", &tamanho);
                for (int i = 0; i < tamanho; i++)
                {
                    LerProduto(&x);
                    Enfileirar(x, &F2);
                }
            }
            else
            {
                printf("Opcao invalida");
            }
            break;
        case 2:
            printf("\nEscolha a fila (1 para F1, 2 para F2): \n");
            scanf("%d", &F);
            if (F == 1)
            {
                printf("\nImprimindo...\n");
                imprimirFila(&F1);
            }
            else if (F == 2)
            {
                printf("\nImprimindo...\n");
                imprimirFila(&F2);
            }
            else
            {
                printf("Opcao invalida");
            }
            break;
        case 3:
            printf("\nEscolha a fila (1 para F1, 2 para F2): \n");
            scanf("%d", &F);
            if (F == 1)
            {
                printf("\nDigite o codigo produto que deseja imprimir: \n");
                scanf("%d", &x.codigo);

                if (PesquisarFila(&F1, &x) == 1)
                {
                    printf("\nO produto foi encontrado com sucesso!\nInformações:\n");
                    ImprimirProduto(x);
                }
                else
                {
                    printf("\nO produto não foi encontrado!\n");
                }
            }
            else if (F == 2)
            {
                printf("\nDigite o codigo produto que deseja imprimir: \n");
                scanf("%d", &x.codigo);

                if (PesquisarFila(&F2, &x) == 1)
                {
                    printf("\nO produto foi encontrado com sucesso!\nInformacoes:\n");
                    ImprimirProduto(x);
                }
                else
                {
                    printf("\nO produto não foi encontrado!\n");
                }
            }
            else
            {
                printf("Opcao invalida");
            }
            break;

        case 4:
            printf("\nEscolha a fila (1 para F1, 2 para F2): \n");
            scanf("%d", &F);
            if (F == 1)
            {
                printf("\nDigite o codigo produto que deseja pesquisar: \n");
                scanf("%d", &x.codigo);

                if (PesquisarFila(&F1, &x) == 1)
                {
                    printf("\nO produto esta na fila!\n");
                }
                else
                {
                    printf("\nO produto não esta na fila!\n");
                }
            }
            else if (F == 2)
            {
                printf("\nDigite o codigo produto que deseja pesquisar: \n");
                scanf("%d", &x.codigo);

                if (PesquisarFila(&F2, &x) == 1)
                {
                    printf("\nO produto esta na fila!\n");
                }
                else
                {
                    printf("\nO produto não esta na fila!\n");
                }
            }
            else
            {
                printf("Opcao invalida");
            }
            break;
        case 5:
            printf("Comparando...");
            if (verificaSeDuasIguais(F1, F2) == 1)
            {
                printf("\nAs duas filas sao iguais\n");
            }
            else
            {
                printf("\nAs duas filas sao diferentes\n");
            }
            break;
        case 6:
            printf("\nEscolha a fila (1 para F1, 2 para F2): \n");
            scanf("%d", &F);
            if (F == 1)
            {
                Liberar(&F1);
                printf("Fila liberada");
            }
            else if (F == 2)
            {
                Liberar(&F2);
                printf("Fila liberada.");
            }
            else
            {
                printf("Opcao invalida");
            }
            break;
        case 7:
            printf("Fazendo a intersecao...");
            intersecao2(&F1, &F2, &F3);
            printf("\nInformacoes da Fila 3: ");
            imprimirFila(&F3);
            break;
        case 8:
            printf("Calculando...");
            diferenca2(&F1, &F2, &F3);
            printf("\nInformacoes da Fila 3: ");
            imprimirFila(&F3);
            break;

        case 9:
            int n = 2;
            CoverterBinario(&F1, n);
            break;

        case 10:
            printf("Saindo...");
            break;
        }

    } while (opc != 10);
}

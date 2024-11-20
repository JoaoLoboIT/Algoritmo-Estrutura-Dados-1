#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
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

typedef struct
{
    TCelula *primeiro;
    TCelula *ultimo;
    int tamanho;
    int inicializada;
} TLista;

void FLVazia(TLista *Lista)
{
    Lista->primeiro = (TCelula *)malloc(sizeof(TCelula));
    Lista->ultimo = Lista->primeiro;
    Lista->primeiro->prox = NULL;
    Lista->tamanho = 0;
    Lista->inicializada = 1;
}

int Vazia(TLista Lista)
{
    return (Lista.primeiro == Lista.ultimo);
}

void Inserir(TProduto x, TLista *Lista)
{
    Lista->ultimo->prox = (TCelula *)malloc(sizeof(TCelula));
    Lista->ultimo = Lista->ultimo->prox;
    Lista->ultimo->item = x;
    Lista->ultimo->prox = NULL;
    Lista->tamanho++;
}

TCelula *Pesquisar(TLista Lista, TProduto Item)
{
    TCelula *Aux;
    Aux = Lista.primeiro;
    while (Aux->prox != NULL)
    {
        if (Aux->prox->item.codigo == Item.codigo)
        {
            return Aux;
        }
        Aux = Aux->prox;
    }
    return NULL;
}

void Excluir(TLista *Lista, TProduto *Item)
{
    TCelula *Aux1, *Aux2;
    Aux1 = Pesquisar(*Lista, *Item);
    if (Aux1 != NULL)
    {
        Aux2 = Aux1->prox;
        Aux1->prox = Aux2->prox;
        *Item = Aux2->item;
        if (Aux1->prox == NULL)
        {
            Lista->ultimo = Aux1;
        }
        free(Aux2);
        Lista->tamanho--;
    }
    else
    {
        Item->codigo = -1;
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
}

void ImprimirProduto(TProduto Item)
{
    printf("\n Codigo: %d\n", Item.codigo);
    printf("\n Nome: %s\n", Item.nome);
    printf("\n Descricao: %s\n", Item.descricao);
    printf("\n Preco: %.2f\n", Item.preco);
    printf("\n Quantidade: %d\n", Item.quantidade);
}

void Imprimir(TLista Lista)
{
    TCelula *Aux;
    Aux = Lista.primeiro->prox;
    while (Aux != NULL)
    {
        ImprimirProduto(Aux->item); 
        Aux = Aux->prox;
    }
}

void LiberarLista(TLista *Lista)
{
    TCelula *Aux1, *Aux2;
    Aux1 = Lista->primeiro;
    while (Aux1 != NULL)
    {
        Aux2 = Aux1->prox;
        free(Aux1);
        Aux1 = Aux2;
    }
    Lista->primeiro = NULL;
}

void LiberarLista2(TLista *Lista)
{ 
    while (!Vazia(*Lista))
    {
        Excluir(Lista, &Lista->primeiro->prox->item);
    }
    free(Lista->primeiro); 
    Lista->primeiro = NULL;
}

TCelula *PesquisarPorNome(TLista Lista, TProduto Item)
{

    TCelula *Aux;
    Aux = Lista.primeiro->prox;
    while (Aux != NULL)
    {
        if (strcmp(Aux->item.nome, Item.nome) == 0)
        {
            return Aux;
        }
        Aux = Aux->prox;
    }
    return NULL;
}

void Atualizar(TLista *Lista, TProduto Item)
{
    TCelula *Aux;
    Aux = PesquisarPorNome(*Lista, Item);
    if (Aux != NULL)
    {
        printf("\nProduto encontrado! Digite os novos dados:\n");
        LerProduto(&Item);
        Aux->prox->item = Item;
        printf("\nProduto atualizado com sucesso!\n");
    }
    else
    {
        printf("\nProduto não encontrado!\n");
    }
}

void InsereCrescente(TLista *Lista, TProduto Item)
{
    if (Vazia(*Lista))
    {
        Inserir(Item, Lista);
    }
    else if (strcmp(Item.nome, Lista->ultimo->item.nome) > 0)
    {
        Inserir(Item, Lista);
    }
    else
    {
        TCelula *aux;
        int flag = 0;
        aux = Lista->primeiro;
        while (!Vazia(*Lista))
        {
            if (strcmp(Item.nome, aux->item.nome) > 0 && strcmp(Item.nome, aux->prox->item.nome) < 0)
            {
                TCelula *novo = (TCelula *)malloc(sizeof(TCelula));
                novo->item = Item;
                novo->prox = aux->prox;
                aux->prox = novo;
                flag = 1;
                Lista->tamanho++;
            }
            if (flag == 1)
            {
                return;
            }
            aux = aux->prox;
        }
    }
}
void verificaDuasLista(TLista *Lista1, TLista *Lista2)
{
    if (Lista1->tamanho == Lista2->tamanho)
    {
        TCelula *aux1;
        TCelula *aux2;
        int iguais = 0;
        aux1 = Lista1->primeiro;
        aux2 = Lista2->primeiro;
        while (aux1->prox != NULL && aux2->prox != NULL)
        {
            if (aux1 = aux2)
            {
                iguais++;
            }
            aux1 = aux1->prox;
            aux2 = aux2->prox;
        }
        if (iguais = Lista1->tamanho)
        {
            printf("\nAs duas listas são iguais\n");
        }
        else
        {
            printf("\nAs listas são diferentes\n");
        }
    }
    else
    {
        printf("\nAs listas são diferentes\n");
    }
}


int verficaIgualdade(TLista l1, TLista l2)
{
    if (l1.tamanho == l2.tamanho)
    {
        TCelula *aux;
        int cont = 0;
        aux = l1.primeiro;
        while (aux != NULL)
        {
            if (PesquisarPorNome(l2, aux->item) != NULL)
            {
                cont++;
            }
            aux = aux->prox;
        }
        if (cont == l1.tamanho)
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

void concatenaDuasLista(TLista *L1, TLista *L2)
{
    TCelula *aux;
    aux = L2->primeiro->prox;
    while (aux != NULL)
    {
        Inserir(aux->item, L1);
        TProduto x = aux->item;
        Excluir(L2, &x);
        aux = aux->prox;
    }
}

void printaIesima(TLista *Lista, int i)
{
    TCelula *aux1;
    int aux2 = i;
    i = 1;
    aux1 = Lista->primeiro->prox;
    while (i != aux2)
    {
        aux1 = aux1->prox;
        i++;
    }
    ImprimirProduto(aux1->item);
}

void excluiIesima(TLista *Lista, int i)
{
    TCelula *aux1;
    int aux2 = i;
    i = 1;
    aux1 = Lista->primeiro->prox;
    while (i != aux2)
    {
        aux1 = aux1->prox;
        i++;
    }
    TProduto x = aux1->item;
    Excluir(Lista, &x);
}

void concatenaDuasListas2(TLista* l1, TLista* l2){
    TCelula* aux = l2->primeiro->prox;
    while(aux != NULL){
        Inserir(aux->item, l1);
        aux = aux->prox;
    }
    Imprimir(*l1);
}

void recursiva(TCelula *celula)
{
    if (celula != NULL)
    {
        ImprimirProduto(celula->item);
        recursiva(celula->prox);
    }
}

void imprimeIesima2(TLista l1, int i){
    TCelula* aux = l1.primeiro->prox;
    for(int j = 1; j < i; j++){
        aux = aux->prox;
    }
    ImprimirProduto(aux->item);
}

void excluiIesima2(TLista* l1, int i){
    TCelula* aux = l1->primeiro->prox;
    for(int j = 1; j < i; j++){
        aux = aux->prox;
    }
    Excluir(l1, &aux->item);
}

void recursiva2(TCelula* x){
    if(x !=NULL){
        ImprimirProduto(x->item);
        recursiva2(x->prox);
    }
}

int main()
{

    TProduto x, y, z;
    TLista L1, L2;
    FLVazia(&L1);
    FLVazia(&L2);
    TCelula *p;

    int tamanho;
    int opc;

    do
    {

        printf("\n-----------------------------");
        printf("\nDigite qual opcao voce deseja fazer:\n");
        printf("-----------------------------");
        printf("\n1 - Inserir produtos na lista");
        printf("\n2 - Imprimir a lista");
        printf("\n3 - Pesquisar algum produto na lista");
        printf("\n4 - Excluir algum produto da lista");
        printf("\n5 - Excluir lista");
        printf("\n6 - Comparar duas listas");
        printf("\n7 - Inserir um produto em ordem crescente");
        printf("\n8 - Atualizar lista");
        printf("\n9 - Concatenar duas listas");
        printf("\n10 - Imprimir iesimo produto");
        printf("\n11 - Excluir iesimo produto");
        printf("\n12 - Recursiva");
        printf("\n13 - Sair do programa");
        printf("\n-----------------------------\n");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            int L;

            printf("\nEscolha a lista (1 para L1, 2 para L2): \n");
            scanf("%d", &L);
            if (L == 1)
            {
                printf("\nDigite a quantidade de produtos que deseja inserir: \n");
                scanf("%d", &tamanho);
                for (int i = 0; i < tamanho; i++)
                {
                    LerProduto(&x);
                    Inserir(x, &L1);
                }
            }
            else if (L == 2)
            {
                printf("\nDigite a quantidade de produtos que deseja inserir: \n");
                scanf("%d", &tamanho);
                for (int i = 0; i < tamanho; i++)
                {
                    LerProduto(&z);
                    Inserir(z, &L2);
                }
            }
            else
            {
                printf("\nOpção inválida.\n");
            }
            break;

        case 2:
            printf("\nEscolha a lista (1 para L1, 2 para L2): \n");
            scanf("%d", &L);
            {
                if (L == 1 && L1.inicializada == 1)
                {
                    Imprimir(L1);
                }
                else if (L == 2 && L2.inicializada == 1)
                {
                    Imprimir(L2);
                }
                else if (L1.inicializada != 1 || L2.inicializada != 1)
                {
                    printf("\nOpção inválida.\n");
                }
            }
            break;

        case 3: // arrumar
            printf("\nEscolha a lista (1 para L1, 2 para L2): \n");
            scanf("%d", &L);
            if (L == 1)
            {
                printf("\nDigite o codigo produto que deseja pesquisar: \n");
                scanf("%d", &y.codigo);

                if (Pesquisar(L1, y) != NULL)
                {
                    printf("\nO produto foi encontrado com sucesso!\nInformações:\n");
                    ImprimirProduto(y);
                }
                else
                {
                    printf("\nO produto não foi encontrado!\n");
                }
            }
            else if (L == 2)
            {
                printf("\nDigite o codigo produto que deseja pesquisar: \n");
                scanf("%d", &y.codigo);

                if (Pesquisar(L2, y) != NULL)
                {
                    printf("\nO produto foi encontrado com sucesso!\nInformações:\n");
                    ImprimirProduto(y);
                }
                else
                {
                    printf("\nO produto não foi encontrado!\n");
                }
            }

            break;

        case 4:
            printf("\nEscolha a lista (1 para L1, 2 para L2): \n");
            scanf("%d", &L);
            if (L == 1)
            {
                printf("\nInforme o codigo do produto que deseja excluir\n");
                scanf("%d", &y.codigo);
                Excluir(&L1, &y);

                if (y.codigo != -1)
                {
                    ImprimirProduto(y);
                }
                else
                {
                    printf("\nNão foi possível excluir o produto\n");
                }
            }
            else if (L == 2)
            {
                printf("\nInforme o codigo do produto que deseja excluir\n");
                scanf("%d", &y.codigo);
                Excluir(&L2, &y);

                if (y.codigo != -1)
                {
                    ImprimirProduto(y);
                }
                else
                {
                    printf("\nNão foi possível excluir o produto\n");
                }
            }
            break;

        case 5:
            printf("\nEscolha a lista (1 para L1, 2 para L2): \n");
            scanf("%d", &L);
            if (L == 1)
            {
                printf("\nExcluindo lista...\n");
                LiberarLista2(&L1); // faz sentido?
                printf("\nLista excluida com sucesso\n");
            }
            else if (L == 2)
            {
                printf("\nExcluindo lista...\n");
                LiberarLista2(&L1);
                printf("\nLista excluida com sucesso\n");
            }
            break;

        case 6:
            printf("\nComparando as duas listas...\n");
            int r = verficaIgualdade(L1, L2);
            printf("%d ", r);
            break;

        case 7:
        {
            printf("\nEscolha a lista (1 para L1, 2 para L2): \n");
            scanf("%d", &L);
            if (L == 1 || L == 2)
            {
                TProduto prod;
                printf("\nDigite os dados do produto a ser inserido:\n");
                LerProduto(&prod);
                if (L == 1)
                {
                    InsereCrescente(&L1, prod);
                }
                else
                {
                    InsereCrescente(&L2, prod);
                }
            }
            else
            {
                printf("\nOpção inválida.\n");
            }
        }
        break;

        case 8:
            printf("Escolha a lista (1 para L1, 2 para L2): ");
            scanf("%d", &L);
            getchar();
            if (L == 1)
            {
                if (L1.inicializada)
                {
                    printf("Digite o nome do produto que deseja atualizar: "); // fgets?
                    scanf("%c", &x.nome);
                    Atualizar(&L1, x);
                }
                else
                {
                    printf("Lista L1 não foi inicializada.\n");
                }
            }
            else if (L == 2)
            {
                if (L2.inicializada)
                {
                    printf("Digite o código do produto que deseja atualizar: ");
                    scanf("%c", &x.nome);
                    Atualizar(&L2, x);
                }
                else
                {
                    printf("Lista L2 não foi inicializada.\n");
                }
            }
            else
            {
                printf("Opção inválida.\n");
            }
            break;

        case 9:
            printf("Concatenando...");
            concatenaDuasListas2(&L1, &L2);

            break;

        case 10:
            int i;
            printf("Escolha a lista (1 para L1, 2 para L2): ");
            scanf("%d", &L);
            printf("\nDigite o valor de i:");
            scanf("%d", &i);
            if (L == 1)
            {
                imprimeIesima2(L1, i);
            }
            else if (L == 2)
            {
                printaIesima(&L2, i);
            }
            else
            {
                printf("Opcao invalida.");
            }
            break;

        case 11:
            printf("Escolha a lista (1 para L1, 2 para L2): ");
            scanf("%d", &L);
            printf("\nDigite o valor de i:");
            scanf("%d", &i);
            if (L == 1)
            {
                excluiIesima(&L1, i);
            }
            else if (L == 2)
            {
                excluiIesima(&L2, i);
            }
            else
            {
                printf("Opcao invalida.");
            }
            break;

        case 12:
            recursiva(L1.primeiro->prox);
            break;

        case 13:
            printf("\nSaindo do programa...\n");
            break;

        default:
            printf("\nOpção inválida.\n");
            break;
        }
    } while (opc != 13);

    return 0;
}
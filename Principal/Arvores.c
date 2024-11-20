#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////// ESTRUTURA PILHA

typedef struct celula 
{
    TItem item;
    struct celula *prox;

} TCelulaPilha;

typedef struct pilha
{
    TCelulaPilha *fundo;
    TCelulaPilha *topo;
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

void Empilhar(TItem x, TPilha *Pilha)
{
    TCelulaPilha *Aux;
    Aux = (TCelulaPilha *)malloc(sizeof(TCelulaPilha));
    Pilha->topo->item = x;
    Aux->prox = Pilha->topo;
    Pilha->topo = Aux;
    Pilha->tamanho++;
}

void Desempilhar(TPilha *Pilha, TItem *Item)
{
    TCelulaPilha *q;
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct item
{
    int chave;
} TItem;

typedef struct celula
{
    TItem item;
    struct celula *pai;
    struct celula *esq;
    struct celula *dir;
} TCelula;

typedef struct arvore
{
    TCelula *raiz;
    int tamanho;
} TArvore;

void Iniciar(TCelula **no)
{
    *no = NULL;
}

TCelula *criaNo(TItem Item)
{
    TCelula *no = (TCelula *)malloc(sizeof(TCelula));
    no->pai = NULL;
    no->esq = NULL;
    no->dir = NULL;
    no->item = Item;
    return no;
}

void Inserir(TCelula **x, TCelula *pai, TItem Item)
{
    if ((*x) == NULL)
    {
        (*x) = criaNo(Item);
        if (pai != NULL)
            (*x)->pai = pai;
        return;
    }
    if ((*x)->item.chave > Item.chave)
    {
        Inserir(&(*x)->esq, (*x), Item);
        return;
    }
    if ((*x)->item.chave <= Item.chave)
        Inserir(&(*x)->dir, (*x), Item);
}

void InserirIterativa2(TCelula **raiz, TCelula *pai, TItem Item)
{
    TCelula *aux = *raiz;
    TCelula *novoNo = criaNo(Item);

    while (aux != NULL)
    {
        pai = aux;
        if (Item.chave < aux->item.chave)
        {
            aux = aux->esq;
        }
        else
        {
            aux = aux->dir;
        }
    }

    if (*raiz == NULL)
    {
        *raiz = novoNo;
    }
    else
    {

        if (Item.chave < pai->item.chave)
        {
            pai->esq = novoNo;
        }
        else
        {
            pai->dir = novoNo;
        }

        novoNo->pai = pai;
    }
}

TCelula *Pesquisar(TCelula *x, TItem Item)
{
    if ((x == NULL) || (x->item.chave == Item.chave))
        return x;
    if (Item.chave < x->item.chave)
        return Pesquisar(x->esq, Item);
    else if (Item.chave > x->item.chave)
        return Pesquisar(x->dir, Item);
}

void Central(TCelula *x)
{
    if (x != NULL)
    {
        Central(x->esq);
        printf("%d ", x->item.chave);
        Central(x->dir);
    }
}

void InserirIterativo(TArvore *Arvore, TItem Item)
{
    TCelula *x, *pai;
    x = Arvore->raiz;
    pai = NULL;
    while (x != NULL)
    { 
        pai = x;
        if (Item.chave < x->item.chave)
            x = x->esq;
        else if (Item.chave >= x->item.chave)
            x = x->dir;
    }
    if (x == NULL)
    {
        x = criaNo(Item); 
        if (pai != NULL)
        {
            x->pai = pai; 
            if (pai->item.chave <= Item.chave)
                pai->dir = x; 
            else
                pai->esq = x; 
        }
        else
            Arvore->raiz = x;
    }
}

void CentralInterativo(TCelula *x)
{
    TPilha Pilha; 
    FPVazia(&Pilha);
    TCelula y;
    do
    {
        while (x != NULL)
        {
            Empilhar(*x, &Pilha);
            x = x->esq;
        }
        Desempilhar(&Pilha, &y);
        printf("%d", y.item.chave);
        x = y.dir;
    } while ((!Vazia(Pilha)) || (x != NULL));
}

void PreOrdemIterativa(TCelula *x)
{
    TPilha p1;
    FPVazia(&p1);
    TCelula y;
    do
    {
        while (x != NULL)
        {
            printf("%d ", x->item.chave);
            Empilhar(*x, &p1);
            x = x->esq;
        }
        Desempilhar(&p1, y);
        x = y.dir;
    } while ((!Vazia(p1) || (x != NULL)));
}

void PosOrdemIterativo(TCelula *x)
{
    TCelula *raiz = x;
    TPilha p1;
    FPVazia(&p1);
    TCelula y;
    do
    {
        while (x != NULL)
        {
            Empilhar(*x, &p1);
            x = x->esq;
        }
        Desempilhar(&p1, y);
        if (y.dir == NULL)
            printf("%d ", y.item.chave);
        x = y.dir;
        while (x != NULL)
        {
            Empilhar(*x, &p1);
            x = x->dir;
        }
    } while ((!Vazia(p1) || (x != NULL)));
}

void PreOrdem(TCelula *x)
{
    if (x != NULL)
    {
        printf("%d ", x->item.chave);
        PreOrdem(x->esq);
        PreOrdem(x->dir);
    }
}

void PosOrdem(TCelula *x)
{
    if (x != NULL)
    {
        PosOrdem(x->esq);
        PosOrdem(x->dir);
        printf("%d ", x->item.chave);
    }
}

TCelula *Minimo(TCelula *x)
{
    if (x == NULL)
        return NULL;
    while (x->esq != NULL)
    {
        x = x->esq;
    }
    return x;
}

TCelula *Maximo(TCelula *x)
{
    if (x == NULL)
        return NULL;
    while (x->dir != NULL)
    {
        x = x->dir;
    }
    return x;
}

TCelula *Sucessor(TCelula *x)
{
    if (x == NULL)
        return NULL;
    if (x->dir != NULL)
        return Minimo(x->dir);
    TCelula *y = x->pai;
    while (y != NULL && x == y->dir)
    {
        x = y;
        y = y->pai;
    }
    return y;
}

TCelula *Predecessor(TCelula *x)
{
    if (x == NULL)
        return x;
    if (x->esq != NULL)
        return Maximo(x->esq);
    TCelula *y = x->pai;
    while (y != NULL && x == y->esq)
    {
        x = y;
        y = y->pai;
    }
    return y;
}

void Transplante(TArvore *Arvore, TCelula **u, TCelula **v)
{
    if ((*u)->pai == NULL)
        Arvore->raiz = (*v);
    else if ((*u) == (*u)->pai->esq)
        (*u)->pai->esq = (*v);
    else
        (*u)->pai->dir = (*v);
    if (*v != NULL)
        (*v)->pai = (*u)->pai;
}

void Retirar(TArvore *Arvore, TCelula **z)
{
    if (*z == NULL)
    {
        printf("\n>>>>> AVISO: NO' \"z\" E' NULO! <<<<<\n");
        return;
    }
    if ((*z)->esq == NULL)
        Transplante(Arvore, z, &(*z)->dir);
    else if ((*z)->dir == NULL)
        Transplante(Arvore, z, &(*z)->esq);
    else
    {
        TCelula *y = Minimo((*z)->dir);
        if (y->pai != (*z))
        {
            Transplante(Arvore, &y, &y->dir);
            y->dir = (*z)->dir;
            y->dir->pai = y;
        }
        Transplante(Arvore, z, &y);
        y->esq = (*z)->esq;
        y->esq->pai = y;
    }
    free(*z);
    *z = NULL;
}

void PercursoInOrder2(TCelula *celula)
{
    TCelula *minimo = Minimo(celula);
    TCelula *maximo = Maximo(celula);
    printf("%d ", minimo->item.chave);

    while (minimo != NULL)
    {
        minimo = Sucessor(minimo);

        printf("%d ", minimo->item.chave);
        if (minimo == maximo)
        {
            break;
        }
    }
}

int main()
{
    TArvore Arvore;
    Arvore.raiz = NULL;

    char elementos[] = {'Y', 'K', 'M', 'L', 'N', 'A', 'S', 'Z', 'X', 'U', 'T'};
    TItem itens[11]; 

    for (int i = 0; i < 11; i++)
    {
        TItem item;
        item.chave = elementos[i];
        Inserir(&Arvore.raiz, NULL, item);
    }

    TItem itemW;
    itemW.chave = 'W';
    Inserir(&Arvore.raiz, NULL, itemW);

    TItem itemY;
    itemY.chave = 'Y';
    TCelula *noY = Pesquisar(Arvore.raiz, itemY);
    Retirar(&Arvore, &noY);

    printf("Pre-Ordem: ");
    PreOrdemIterativa(Arvore.raiz);
    printf("\n");
   
    TArvore Arvore2;
    Arvore2.raiz = NULL;

    int elementos2[] = {50, 20, 10, 30, 28, 27, 33, 70, 60, 90, 55, 53, 56, 57, 63, 62, 67};
    TItem item;

    for (int i = 0; i < 17; i++)
    {
        item.chave = elementos2[i];
        Inserir(&Arvore2.raiz, NULL, item);
    }

    printf("Percurso Central (In-Order) Iterativo: ");
    PercursoInOrder2(Arvore2.raiz);
    printf("\n");

    TItem numeroNovo;
    numeroNovo.chave = 61;
    InserirIterativa2(&Arvore2.raiz, NULL, numeroNovo);
    PercursoInOrder2(Arvore2.raiz);
    printf("\n");
    //  }

    return 0;
}
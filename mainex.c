int main()
{
    TProduto x, y;
    TLista L1;
    FLVazia(&L1);
    TCelula *p;
    bool sair = false;
    int opcao = 0;
    int tamanho;

    do
    {
        printf("--- Menu de Interacao com a Lista ---");
        printf("\nOpcao 1: Inserir Produtos na Lista");
        printf("\nOpcao 2: Imprimir a Lista Completa");
        printf("\nOpcao 3: Pesquisar um Produto da Lista");
        printf("\nOpcao 4: Excluir um Produto da Lista");
        printf("\nOpcao 5: Atualizar Dados do Produto");
        printf("\nOpcao 6: Fechar o Programa\n");
        scanf("%d", &opcao);
        printf("--- - - - - - - - - - - - - - - - ---");

        switch (opcao)
        {
        case 1:
            printf("Digite a quantidade de produtos que deseja inserir: ");
            scanf("%d", &tamanho);
            for (int i = 0; i < tamanho; i++)
            {
                LerProduto(&x);
                Inserir(x, &L1);
            }
            break;
        case 2:
            Imprimir(L1);
            break;
        case 3:
            printf("Digite o codigo do produto que deseja pesquisar: ");
            scanf("%d", &y.codigo); // checar com halisson

            p = Pesquisar(L1, y); 
            if (p != NULL)
            {
                printf("\nO produto foi encontrado com sucesso: ");
                // Imprimir produto específico
                printf("%d\n", p->prox->item.codigo);
            }
            else
            {
                printf("Aviso: o produto nao foi encontrado");
            }
            break;
        case 4:
            printf("Informe o codigo do produto que deseja excluir");
            scanf("%d", y.codigo);

            Excluir(&L1, &y);

            if (y.codigo == -1)
            {
                ImprimirProduto(y);   // checar com halisson
            }
            else
            {
                printf("Aviso: nao foi possivel excluir o produto");
            }
            break;
        case 5:
            printf("Digite o nome do produto que deseja alterar os dados: ");
            fgets(y.nome, 20, stdin);
            Atualizar(&L1, y);

            break;
        case 6:
            printf("Fechando o programa...");
            sair = true;
            break;
        default:
            printf("Opção inválida");
            break; // Tem que retornar pro do while
        }

    } while (sair == false);

LiberarLista(&L1);

    return 0;
}
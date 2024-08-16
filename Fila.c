int PesquisarFila(TFila *Fila, TProduto *Item){
    TFila Faux;
    TProdtuo ItemAux;
    char nome = Item.nome;
    int i, n = Fila->tamanho;
    for(int i = 0; i<n; i++){
        Desinfileirar(Fila, &Item);
        if(Item.nome == nome){
        ItemAux = Item;         
        return 1;    
        } else{
            Item.codigo = -1;
            return 0;
        }
    }

}
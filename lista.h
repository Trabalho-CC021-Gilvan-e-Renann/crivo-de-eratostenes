#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
typedef struct lista Lista;
typedef struct numero Num;
struct numero{
    int num;
    Num* prox;
    int marca;
};
struct lista{
    Num* inicio;
    Num* fim;
};
Lista* InicializaLista();
Num* InicilizaNum(int i, int vBooleano);
void InsereNum(Lista* lista, Num* novo);
void ImprimeNaoMarcados();
void MarcaMultiplos(Lista* lista, int N);
void ImprimeNaoMarcasdos(Lista* lista);
void LiberaLista(Lista* lista);
void LiberaNum(Num *num);


#endif // LISTA_H_INCLUDED

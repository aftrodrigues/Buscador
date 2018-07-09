// Bibliotecas Globais
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Bibliotecas Locais
#include "../headers/operations.h"

// OPERAÇÃO a. Listar as consultas mais realizadas por localidade. A operação recebe como entrada
// o nome da localidade e um número que indica quantas consultas devem ser retornadas como saída.
// Se o número for zero, todas as consultas devem ser listadas. A saída da função é o número que
// representa a quantidade de ocorrências e a respectiva consulta. Restrições: (i) listar um resultado
// por linha; (ii) se a localidade não existir, exibir essa informação; (iii) consultas com a mesma
// frequência devem ser listadas em ordem alfabética.
void operacaoA (AVL* localidades, FILE* saida, char nome[], int TExpected){
    AVL* localAtual = searchAVL(localidades, nome);
    if(localAtual != NULL){
        LDC *actual = localAtual->consultas, *prox = actual->next, *aux;

        printf("Inicia simplificacao de consultas\n");

        if(actual != prox){
            do{
                do{
                    if(isEqualLDC(actual->termos, prox->termos)){
                        prox->next->prev = prox->prev;
                        prox->prev->next = prox->next;
                        aux = prox->next;
                        free(prox);
                        prox = aux;
                        (actual->frequencia)++;
                        // Exclui o valor repetido e incrementa a frequencia do
                        // primeiro encontrado.
                    }
                    else
                        prox = prox->next;
                }while(prox != localAtual->consultas);
                actual = actual->next;
                prox = actual->next;
                // Garante que toda a lista de listas seja percorrida.
            }while(actual != localAtual->consultas->prev);

        }

        printf("Tenta armazenar as consultas no arquivo de saida\n");

        localAtual->consultas = sortFreqLDC(localAtual->consultas);
        actual = localAtual->consultas;

        do{
            fprintf(saida, "%d ", actual->frequencia);
            LDC *aux = actual->termos;
            
            fprintf(saida, "%s", aux->chave);
            aux = aux->next;
    
            while(aux != actual->termos){
                fprintf(saida, ";%s", aux->chave);
                aux = aux->next;
            }
            fprintf(saida, "\n");
            actual = actual->next;
        }while(actual != localAtual->consultas && --TExpected != 0);

        printf("Dados armazenados com sucesso!\n\n");

    }
}

// OPERAÇÃO b. Listar as consultas mais realizadas em todo arquivo. A operação recebe como
// entrada um número que indica quantas consultas devem ser retornadas como saída. Se o número
// for zero, todas as consultas devem ser listadas. A saída da função é o número que representa a
// quantidade de ocorrências e a respectiva consulta. Restrições: (i) listar um resultado por linha; (ii)
// consultas com a mesma frequência devem ser listadas em ordem alfabética.
void operacaoB (LDC *consultas, FILE *saida, int TExpected){
    printf("Removendo redundancia\n");
    consultas = remove_redundancia(consultas);
    consultas = sortFreqLDC(consultas);
    consultas = sortSubLDC(consultas);

    printf("Consultas: \n");
    LDC *aux = consultas;
    do {
        printf("[%d]: ", aux->frequencia);
        show_all(aux->termos);
        aux = aux->next;
        printf("\n");
    } while(aux != consultas);

    LDC *actual = consultas;
    printf("Tenta armazenar as consultas no arquivo de saida\n");

    do{
        fprintf(saida, "%d ", actual->frequencia);
        LDC *aux = actual->termos;

        fprintf(saida, "%s", aux->chave);
        aux = aux->next;

        while(aux != actual->termos){
            fprintf(saida, ";%s", aux->chave);
            aux = aux->next;
        }
        fprintf(saida, "\n");
        actual = actual->next;
    }while(actual != consultas && --TExpected != 0);

    printf("Dados armazenados com sucesso!\n\n");
}


// OPERAÇÃO c. Listar os termos mais consultados por localidade. A operação recebe como entrada
// o nome da localidade e um número que indica quantos termos devem ser retornados como saída.
// Se o número for zero, todas os termos devem ser listados. A saída da função é o número que
// representa a quantidade de ocorrências e o respectivo termo. Restrições: (i) listar um resultado por
// linha; (ii) se a localidade não existir, exibir essa informação; (iii) termos com a mesma frequência
// devem ser listados em ordem alfabética.
void operacaoC (AVL *localidades, FILE *saida, char *local, int TExpected){
    AVL *localAtual = searchAVL(localidades, local);
    if(localAtual == NULL){
        fprintf(saida, "Localidade %s não existe na database\n", local);
    } else {
        LDC* lista = localAtual->consultas;

        lista = remove_redundancia_termos(lista);
        lista = sortFreqLDC(lista);
        lista = sortSubTermos(lista);

        LDC *aux = lista;
        printf("Armazenando daods no arquivo de saída\n");
        do {
            //printf("[%d]%s\n", aux->frequencia, aux->chave);
            fprintf(saida, "%d %s\n", aux->frequencia, aux->chave);
            aux = aux->next;
        } while(aux != lista && --TExpected > 0);
    }
}


// OPERAÇÃO d. Listar os termos mais consultados em todo arquivo. A operação recebe como
// entrada um número que indica quantos termos devem ser retornados como saída. Se o número for
// zero, todas os termos devem ser listados. A saída da função é o número que representa a
// quantidade de ocorrências e o respectivo termo. Restrições: (i) listar um resultado por linha; (ii)
// termos com a mesma frequência devem ser listados em ordem alfabética.



// OPERAÇÃO e. Listar tamanho médio das consultas por localidade. A operação recebe como
// entrada o nome da localidade e retorna como saída a média da quantidade de termos das consultas
// na localidade informada. A saída é do tipo int. Truncar se o resultado não for inteiro.



// OPERAÇÃO f. Listar tamanho médio das consultas em todo arquivo. A operação retorna como
// saída a média da quantidade de termos das consultas do arquivo. A saída é do tipo int. Truncar se o
// resultado não for inteiro.

/**
 * A file containing the structures used throughout the project.
 * 
 * @file: structures.h
 * @author: ist1114613 (João Tamagnini)
 */
#ifndef STRUCTURES
#define STRUCTURES
#include "constants.h"

/// Structure representing a inoculation.
typedef struct {
    char *nomeUtente;
    char lote[MAX_LOTE];
    int dia, mes, ano;
} Inoculacao;

/// Structure representing a vaccine batch.
typedef struct {
    int dia, mes, ano;
    char nome[MAX_NOME];
    int quantidade;
    char lote[MAX_LOTE];
    Inoculacao *inoculacoes;
    int numInoculacoes;
} Lote;

/// Structure representing the vaccination system.
typedef struct {
    Lote lotes[MAX_LOTES];
    int numLotes;
    Inoculacao *inoculacoes;
    int numInoculacoes;
    int dia_atual, mes_atual, ano_atual;
    int capacidadeInoculacoes;
} Sistema;
#endif
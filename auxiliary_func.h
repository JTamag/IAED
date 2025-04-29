/**
 * Declarations for commands used in the main commands
 * that are used for the vaccination system.
 * @file: auxiliary_func.h
 * @author: ist1114613 (João Tamagnini)
 */
#ifndef AUXILIARY_FUNC_H
#define AUXILIARY_FUNC_H
#include "headers.h"

/// @defgroup auxiliary_funcs Auxiliary functions.
/// @{

/// Checks if the system has reached the maximum number of batches.
int valid_amount_of_batches(Sistema *sistema,char *current_language);

/// Checks if the name of a vaccine is valid.
int valid_name(char *nome,char *current_language);

/// Checks if the batch is valid.
int valid_batch(char *current_language, char *lote);

/// Checks if the batch is a duplicate(if the same batch already exists).
int duplicate_batch(Sistema *sistema, char *lote,char *current_language);

/// Checks if the quantity of a batch is valid.
int valid_quantity(int quantidade,char *current_language);

/// Checks if the batch exists in the system.
int existing_batch(Sistema *sistema, char *lote, char *current_language);

/* Checks if the user has already been vaccinated with the same 
vaccine on the same date.*/
int already_vaccinated(Sistema *sistema,char *nomeUtente,char *current_language,
                         Lote *loteSelecionado);

/// Extracts parameters from the input line for the vaccination command.
void extrai_parametros_a(const char *linha, char *nomeUtente, char *nomeVacina);

/// Checks the system for the vaccine batch and sets the selected batch.
void search_for_vaccine(Sistema *sistema,const char *nomeVacina,
                         Lote **loteSelecionado, char *current_language);

/// Deletes inoculations based on the number of arguments
void delete_inocullations(Sistema *sistema, char *nomeUtente,
                         char *current_language, int dia, int mes, int ano,
                          char *lote, int numArgs);

/// Cleans up the system by freeing allocated memory for inoculations.
void cleanupSistema(Sistema *sistema);

/// Gets all batches and prints them.
void all_batches(Sistema *sistema);

/// Gets all inoculations and prints them.
void all_inocullations(Sistema *sistema);

/// Lists all inoculations for a specific user.
void user_inocullations(Sistema *sistema, char *nomeUtente, char *current_language);

/// Vaccination process.
void inocullation(Lote *loteSelecionado, Sistema *sistema, char *nomeUtente,
                 char *current_language);

/// Expands the memory allocated for inoculations.
int expandeInoculacoes(Sistema *sistema, char *current_language);

int datavalidaNein(int dia, int mes, int ano, Sistema *sistema);
/// Checks if the date is valid.
int datavalida(int dia, int mes, int ano, Sistema *sistema,char *current_language);

/// Checks if the date is valid for a future date.
int datavalidaHistory(int dia, int mes, int ano, Sistema *sistema,
                    char *current_language);

/// Sorts the batches in the sistem by date.
void sortLotesPorData(Sistema *sistema);

/// Clears the input buffer.
void clearinput();

/// @}
#endif
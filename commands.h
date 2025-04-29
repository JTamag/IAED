/**
 * Declarations for commands used in the vaccination system.
 * @file: commands.h
 * @author: ist1114613 (João Tamagnini)
 */
#ifndef COMMANDS_H
#define COMMANDS_H
#include "headers.h"

/// @defgroup Commands Command execution functions.
/// @{

/// Creates a new vaccine batch.
void comandoc(Sistema *sistema,char *current_language);

/// Lists all vaccine batches or those matching a specific name.
void comandol(Sistema *sistema,char *current_language);

/// Vaccinates a user with a specific vaccine batch.
void comandoa(Sistema *sistema, char *current_language);

/// Removes a batch's availability.
void comandor(Sistema *sistema,char *current_language);

void comandov(Sistema *sistema);

/// Deletes a user's vaccination history.
void comandod(Sistema *sistema, char *current_language);

/// Lists all vaccinations or those matching a specific user.
void comandou(Sistema *sistema,char *current_language);

/// Updates or gives the current date of the system.
void comandot(Sistema *sistema, char *current_language);

/// @}
#endif
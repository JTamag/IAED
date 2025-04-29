/**
 * Declaration of commands used to print errors based
 * on the current language.
 * @file: error_func.h
 * @author: ist1114613 (João Tamagnini)
 */
#ifndef ERROR_FUNC_H
#define ERROR_FUNC_H

/// @defgroup error_funcs Error functions.
/// @{

/// Prints an error message for an invalid date.
void Error_invalid_date(char *current_language);

/// Prints an error message for exceeding the maximum amount of batches.
void Error_exceeded_batch_limit(char *current_language);

/// Prints an error message for exceeding memory capacity.
void Error_exceeded_memory_capacity(char *current_language);

/// Prints an error message for an invalid name.
void Error_invalid_name(char *current_language);

/// Prints an error message for a duplicated batch number.
void Error_duplicated_batch(char *current_language);

/// Prints an error message for an invalid batch.
void Error_invalid_batch(char *current_language);

/// Prints an error message for an invalid quantity.
void Error_invalid_quantity(char *current_language);

/// Prints an error message for a non-existent vaccine.
void Error_non_existent_vaccine(char *current_language);

/// Prints an error message for an absence of stock.
void Error_no_stock(char *current_language);

/// Prints an error message for a user that has already been vaccinated.
void Error_already_vaccinated(char *current_language);

/// Prints an error message for a non-existent batch.
void Error_non_existent_batch(char *current_language);

/// Prints an error message for a non-existent user.
void Error_non_existent_user(char *current_language);

/// @}
#endif
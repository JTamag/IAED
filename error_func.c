/**
 * Implementation of commands used to print errors based
 * on the current language.
 * 
 * @file: error_func.c
 * @author: ist1114613 (João Tamagnini)
 */

#include "headers.h"

/**
 * @brief Prints an error message for an invalid date.
 * 
 * @param current_language Language for error messages.
 */
void Error_invalid_date(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", EINVDATE_PT);
    } else {
        printf("%s\n", EINVDATE_EN);
    }
}

/**
 * @brief Prints an error message for exceeding the maximum amount of batches.
 * 
 * @param current_language Language for error messages.
 */
void Error_exceeded_batch_limit(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", E2MANYCONT_PT);
    } else {
        printf("%s\n", E2MANYCONT_EN);
    }
}

/**
 * @brief Prints an error message for exceeding memory capacity.
 * 
 * @param current_language Language for error messages.
 */
void Error_exceeded_memory_capacity(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", ENOMEMORY_PT);
    } else {
        printf("%s\n", ENOMEMORY_EN);
    }
}

/**
 * @brief Prints an error message for an invalid name.
 * 
 * @param current_language Language for error messages.
 */
void Error_invalid_name(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", EINVNAME_PT);
    } else {
        printf("%s\n", EINVNAME_EN);
    }
}

/**
 * @brief Prints an error message for a duplicated batch number.
 * 
 * @param current_language Language for error messages.
 */
void Error_duplicated_batch(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", EDUPBATCH_PT);
    } else {
        printf("%s\n", EDUPBATCH_EN);
    }
}

/**
 * @brief Prints an error message for an invalid batch.
 * 
 * @param current_language Language for error messages.
 */
void Error_invalid_batch(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", EINVBATCH_PT);
    } else {
        printf("%s\n", EINVBATCH_EN);
    }
}

/**
 * @brief Prints an error message for an invalid quantity.
 * 
 * @param current_language Language for error messages.
 */
void Error_invalid_quantity(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", EINVQUANT_PT);
    } else {
        printf("%s\n", EINVQUANT_EN);
    }
}

/**
 * @brief Prints an error message for a non-existent vaccine.
 * 
 * @param current_language Language for error messages.
 */
void Error_non_existent_vaccine(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", ENOSUCHV_PT);
    } else {
        printf("%s\n", ENOSUCHV_EN);
    }
}

/**
 * @brief Prints an error message for an absence of stock.
 * 
 * @param current_language Language for error messages.
 */
void Error_no_stock(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", ENOSTOCK_PT);
    } else {
        printf("%s\n", ENOSTOCK_EN);
    }
}

/**
 * @brief Prints an error message for a user that has already been vaccinated.
 * 
 * @param current_language Language for error messages.
 */
void Error_already_vaccinated(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", EALVACC_PT);
    } else {
        printf("%s\n", EALVACC_EN);
    }
}

/**
 * @brief Prints an error message for a non-existent batch.
 * 
 * @param current_language Language for error messages.
 */
void Error_non_existent_batch(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", ENOSUCHBATCH_PT);
    } else {
        printf("%s\n", ENOSUCHBATCH_EN);
    }
}

/**
 * @brief Prints an error message for a non-existent user.
 * 
 * @param current_language Language for error messages.
 */
void Error_non_existent_user(char *current_language) {
    if (strcmp(current_language, "pt") == 0) {
        printf("%s\n", ENOSUCHUSER_PT);
    } else {
        printf("%s\n", ENOSUCHUSER_EN);
    }
}

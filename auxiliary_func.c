/**
 * Implementation of commands used in the main commands.
 * @file: auxiliary_func.c
 * @author: ist1114613 (João Tamagnini)
 */
#include "headers.h"

/**
 * @brief Checks if the system has reached the maximum number of batches.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param current_language Language for error messages.
 * 
 * @return 1 if valid, 0 if not valid.
 */
int valid_amount_of_batches(Sistema *sistema,char *current_language) {
    if (sistema->numLotes >= MAX_LOTES) {
        Error_exceeded_batch_limit(current_language);
        return 0;
    }
    return 1;
}

/**
 * @brief Checks if the name of a vaccine is valid,
 * by checking it it is not to long or if it 
 * contains any invalid characthers.
 * 
 * @param nome Name of the vaccine.
 * @param current_language Language for error messages.
 * 
 * @return 1 if valid, 0 if not valid.
 */
int valid_name(char *nome,char *current_language) {
    // Check if the name surpasses the maximum length.
    if (strlen(nome) > MAX_NOME) {
        Error_invalid_name(current_language);
        return 0;
    }
    // Check if the name contains any invalid characters.
    for (size_t i = 0; i < strlen(nome); i++) {
        if (isspace(nome[i])) {
            Error_invalid_name(current_language);
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Checks if the batch is valid,
 * by checking it it is not to long or if it
 * does not consist of Uppercase hexadecimal digits.
 * 
 * @param current_language Language for error messages.
 * @param lote Batch number.
 * 
 * @return 1 if valid, 0 if not valid.
 */
int valid_batch(char *current_language, char *lote) {
    // Check if the batch number surpasses the maximum length.
    if (strlen(lote) > MAX_LOTE) {
        Error_invalid_batch(current_language);
        return 0;
    }
    /* Check if the batch number contains any invalid characters/non uppercase
        hexadecimal digits.*/
    for (size_t i = 0; i < strlen(lote); i++) {
        if (!isxdigit(lote[i]) || (isalpha(lote[i]) && !isupper(lote[i]))) {
           Error_invalid_batch(current_language);
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Checks if the batch is a duplicate(if the same batch already exists).
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param lote Batch number.
 * @param current_language Language for error messages.
 * 
 * @return 1 if valid, 0 if not valid.
 */
int duplicate_batch(Sistema *sistema, char *lote,char *current_language) {
    // Check if the batch number already exists in the system.
    for (int i = 0; i < sistema->numLotes; i++) {
        if (strcmp(sistema->lotes[i].lote, lote) == 0) {
            Error_duplicated_batch(current_language);
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Checks if the quantity of a batch is valid.
 * 
 * @param quantidade Quantity of the batch.
 * @param current_language Language for error messages.
 * 
 * @return 1 if valid, 0 if not valid.
 */
int valid_quantity(int quantidade,char *current_language) {
    if (quantidade <= 0) {
        Error_invalid_quantity(current_language);
        return 0;
    }
    return 1;
}

/**
 * @brief Checks if the batch exists in the system.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param lote Batch number.
 * @param current_language Language for error messages.
 * 
 * @return 1 if valid, 0 if not valid.
 */
int existing_batch(Sistema *sistema, char *lote, char *current_language) {
    // Initialize a variable to check if the batch exists.
    int loteFound = 0;
    // Check if the batch number exists in the system.
        for (int i = 0; i < sistema->numInoculacoes; i++) {
            if (strcmp(sistema->inoculacoes[i].lote, lote) == 0) {
                loteFound = 1;
                break;
            }
        }
        // If the batch number does not exist, print an error message.
        if (!loteFound) {
            printf("%s: ", lote);
            Error_non_existent_batch(current_language);
            return 0;
        }
    return 1;
}

/**
 * @brief Checks if the user has already been vaccinated with the same 
 * vaccine on the same date.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param nomeUtente Name of the user.
 * @param current_language Language for error messages.
 * @param loteSelecionado Pointer to the selected batch.
 * 
 * @return 1 if valid, 0 if not valid.
 */
int already_vaccinated(Sistema *sistema,char *nomeUtente,char *current_language,
                         Lote *loteSelecionado) {
    // Check if the user has already been vaccinated and get the name of the vaccine.
    for (int i = 0; i < sistema->numInoculacoes; i++) {
        if (strcmp(sistema->inoculacoes[i].nomeUtente, nomeUtente) == 0) {
            char *nomeVacina = NULL;
            for (int j = 0; j < sistema->numLotes; j++) {
                if (strcmp(sistema->lotes[j].lote, sistema->inoculacoes[i].lote) == 0) {
                    nomeVacina = sistema->lotes[j].nome;
                    break;
                }
            }
            // Check if the vaccine name matches and if the date is the same.
            if (nomeVacina != NULL &&
                strcmp(nomeVacina, loteSelecionado->nome) == 0 &&
                sistema->inoculacoes[i].dia == sistema->dia_atual &&
                sistema->inoculacoes[i].mes == sistema->mes_atual &&
                sistema->inoculacoes[i].ano == sistema->ano_atual) {
                Error_already_vaccinated(current_language);
                return 0;
            }
        }
    }
    return 1;
}

/**
 * @brief Extracts parameters from the input line for the vaccination command.
 * 
 * @param linha Input line containing the parameters.
 * @param nomeUtente Name of the user.
 * @param nomeVacina Name of the vaccine.
 */
void extrai_parametros_a(const char *linha, char *nomeUtente, char *nomeVacina){
    /* Extract the user name and vaccine name from the input line.
        If the user name is enclosed in double quotes, extract it accordingly.
        Otherwise, extract it as a regular string.*/
    if (linha[1] == '"') {
        char *start = strchr(linha, '"');
        char *end = strrchr(linha, '"');
        if (start != NULL && end != NULL && start != end) {
            strncpy(nomeUtente, start + 1, end-start-1);
            nomeUtente[end-start-1] = '\0';
            sscanf(end + 1, "%s", nomeVacina);
        }
    } else {
        sscanf(linha, "%s %s", nomeUtente, nomeVacina);
    }
}

/**
 * @brief Checks the system for the vaccine name and sets the selected batch.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param nomeVacina Name of the vaccine.
 * @param loteSelecionado Pointer to the selected batch.
 * @param current_language Language for error messages.
 */
void search_for_vaccine(Sistema *sistema,const char *nomeVacina,
                        Lote **loteSelecionado, char *current_language) {
    // Check if there is a valid batch in the system and select it.
    for (int i = 0; i < sistema->numLotes; i++) {
        if (strcmp(sistema->lotes[i].nome, nomeVacina) == 0 && 
            sistema->lotes[i].quantidade > 0 && datavalidaNein(sistema->lotes[i].dia,
            sistema->lotes[i].mes, sistema->lotes[i].ano, sistema)) {
            *loteSelecionado = &sistema->lotes[i];
            return;
        }
    }
    // If no valid batch is found, print an error message.
    *loteSelecionado = NULL;
    Error_no_stock(current_language);
}

/**
 * @brief Deletes inoculations based on the number of arguments.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param nomeUtente Name of the user.
 * @param current_language Language for error messages.
 * @param dia Day of the inoculation.
 * @param mes Month of the inoculation.
 * @param ano Year of the inoculation.
 * @param lote Batch number.
 * @param numArgs Number of arguments provided.
 * 
 * @note The function deletes inoculations based on the user name,
 *  or user name and date, or user name, date, and batch number.
 */
void delete_inocullations(Sistema *sistema, char *nomeUtente, 
                        char *current_language, int dia, int mes, int ano, char *lote, int numArgs) {
    // Initialize variables to keep track of the number of deleted inoculations.
    int aplicacoesDel = 0;
    int found = 0;

    // Check if the user exists in the system.
    for (int i = 0; i < sistema->numInoculacoes; i++) {
        if (strcmp(sistema->inoculacoes[i].nomeUtente, nomeUtente) == 0) {
            found = 1;

            /* If the user exists, look for inoculations based on the 
                number of arguments provided.*/
            if (numArgs == 1 || 
                (numArgs >= 4 && sistema->inoculacoes[i].dia == dia && 
                    sistema->inoculacoes[i].mes == mes && sistema->inoculacoes[i].ano == ano) ||
                (numArgs == 5 && strcmp(sistema->inoculacoes[i].lote, lote) == 0)) {
                aplicacoesDel++;
                for (int j = i; j < sistema->numInoculacoes - 1; j++) {
                    sistema->inoculacoes[j] = sistema->inoculacoes[j + 1];
                }
                sistema->numInoculacoes--;
                i--;
            }
        }
    }

    // If the user does not exist, print an error message.
    if (!found) {
        printf("%s: ", nomeUtente);
        Error_non_existent_user(current_language);
        return;
    }

    // Print the number of deleted inoculations.
    printf("%d\n", aplicacoesDel);
}

/**
 * @brief Cleans up the system by freeing allocated memory for inoculations.
 * 
 * @param sistema Pointer to the vaccination system structure.
 */
void cleanupSistema(Sistema *sistema) {
    // Free the memory allocated for the usernames.
    for (int i = 0; i < sistema->numInoculacoes; i++) {
        free(sistema->inoculacoes[i].nomeUtente);
    }
    // Free the memory allocated for the inoculations.
    free(sistema->inoculacoes); 
}

/**
 * @brief Gets all batches and prints them.
 * 
 * @param sistema Pointer to the vaccination system structure.
 */
void all_batches(Sistema *sistema) {
    // Iterate through all batches and print their details.
    for (int i = 0; i < sistema->numLotes; i++) {
        printf("%s %s %02d-%02d-%d %d %d\n",sistema->lotes[i].nome,sistema->lotes[i].lote, 
         sistema->lotes[i].dia, sistema->lotes[i].mes, sistema->lotes[i].ano, 
         sistema->lotes[i].quantidade,sistema->lotes[i].numInoculacoes);
     }
}

/**
 * @brief Gets all inoculations and prints them.
 * 
 * @param sistema Pointer to the vaccination system structure.
 */
void all_inocullations(Sistema *sistema){
    // Iterate through all inoculations and print their details.
    for (int i = 0; i < sistema->numInoculacoes; i++) {
        printf("%s %s %02d-%02d-%d\n", sistema->inoculacoes[i].nomeUtente,
            sistema->inoculacoes[i].lote,sistema->inoculacoes[i].dia,
            sistema->inoculacoes[i].mes, sistema->inoculacoes[i].ano);
    }
}

/**
 * @brief Lists all inoculations for a specific user.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param nomeUtente Name of the user.
 * @param current_language Language for error messages.
 * 
 * @note If the user does not exist, an error message is printed in the format
 * <username>: no such user.
 */
void user_inocullations(Sistema *sistema, char *nomeUtente, char *current_language) {
    int found = 0;

    // Iterate through all inoculations and print the details for the specified user.
    for (int i = 0; i < sistema->numInoculacoes; i++) {
        if (strcmp(sistema->inoculacoes[i].nomeUtente, nomeUtente) == 0) {
            printf("%s %s %02d-%02d-%d\n", sistema->inoculacoes[i].nomeUtente, 
                sistema->inoculacoes[i].lote,sistema->inoculacoes[i].dia,
                sistema->inoculacoes[i].mes, sistema->inoculacoes[i].ano);
            found = 1;
        }
    }

    // If the user does not exist, print an error message.
    if (!found) {
        printf("%s: ", nomeUtente);
        Error_non_existent_user(current_language);
    }
}

/**
 * @brief Performs the inoculation process for a user.
 * 
 * @param loteSelecionado Pointer to the selected batch.
 * @param sistema Pointer to the vaccination system structure.
 * @param nomeUtente Name of the user.
 * @param current_language Language for error messages.
 */
void inocullation(Lote *loteSelecionado, Sistema *sistema, char *nomeUtente,
                 char *current_language) {
    // Update the values of the selected batch.
    loteSelecionado->quantidade--;
    loteSelecionado->numInoculacoes++;

    // Create a new inoculation and copy the username.
    Inoculacao novaInoculacao;
    novaInoculacao.nomeUtente = strdup(nomeUtente);

    // Check if memory allocation for the user name was successful.
    if (novaInoculacao.nomeUtente == NULL) {
        Error_exceeded_memory_capacity(current_language);
        return;
    }

    // Copy the rest of the data to the inoculation structure.
    strcpy(novaInoculacao.lote, loteSelecionado->lote);
    novaInoculacao.dia = sistema->dia_atual;
    novaInoculacao.mes = sistema->mes_atual;
    novaInoculacao.ano = sistema->ano_atual;

    // Update the inoculations array with the new inoculation.
    sistema->inoculacoes[sistema->numInoculacoes++] = novaInoculacao;

    // Print the batch number of the inoculation.
    printf("%s\n", loteSelecionado->lote);
}

/**
 * @brief Expands the memory allocated for inoculations.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param current_language Language for error messages.
 * 
 * @return 1 if successful, 0 if not successful.
 */
int expandeInoculacoes(Sistema *sistema, char *current_language) {
    // Increase the capacity of inoculations by 10 times.
    size_t newCapacity = sistema->capacidadeInoculacoes*10;

    // Reallocate memory for the inoculations array.
    Inoculacao *newInoculacoes = (Inoculacao *)realloc(sistema->inoculacoes, newCapacity * sizeof(Inoculacao));
    
    // Check if memory allocation was successful.
    if (newInoculacoes == NULL) {
        Error_exceeded_memory_capacity(current_language);
        free(sistema->inoculacoes);
        exit(1); 
    }

    // Update the system with the new inoculations array and capacity.
    sistema->inoculacoes = newInoculacoes;
    sistema->capacidadeInoculacoes = newCapacity;
    return 1; 
}

/**
 * @brief Checks if the date is valid.
 * 
 * @param dia Day of the date.
 * @param mes Month of the date.
 * @param ano Year of the date.
 * @param sistema Pointer to the vaccination system structure.
 * @param current_language Language for error messages.
 * 
 * @return 1 if valid, 0 if not valid.
 */
int datavalida(int dia, int mes, int ano, Sistema *sistema,char *current_language) {
    // Check if the date is valid based on the current date in the system.
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < sistema->ano_atual ||
        (ano == sistema->ano_atual && mes == sistema->mes_atual && sistema->dia_atual > dia) ||
        (ano == sistema->ano_atual && sistema->mes_atual > mes)) {
        Error_invalid_date(current_language);
        return 0;
    }

    // Determine the number of days in the month.
    int diasNoMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    // Check for leap year, and adjust February's days accordingly.
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) {
        diasNoMes[1] = 29; 
    }

    // Check if the day exceeds the number of days in the month.
    if (dia > diasNoMes[mes - 1]) {
        Error_invalid_date(current_language);
        return 0;
    }
    return 1;
}

int datavalidaNein(int dia, int mes, int ano, Sistema *sistema) {
    // Check if the date is valid based on the current date in the system.
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < sistema->ano_atual ||
        (ano == sistema->ano_atual && mes == sistema->mes_atual && sistema->dia_atual > dia) ||
        (ano == sistema->ano_atual && sistema->mes_atual > mes)) {
        return 0;
    }

    // Determine the number of days in the month.
    int diasNoMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    // Check for leap year, and adjust February's days accordingly.
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) {
        diasNoMes[1] = 29; 
    }

    // Check if the day exceeds the number of days in the month.
    if (dia > diasNoMes[mes - 1]) {
        return 0;
    }
    return 1;
}

/**
 * @brief Checks if the date is valid for future dates.
 * 
 * @param dia Day of the date.
 * @param mes Month of the date.
 * @param ano Year of the date.
 * @param sistema Pointer to the vaccination system structure.
 * @param current_language Language for error messages.
 * 
 * @return 1 if valid, 0 if not valid.
 */
int datavalidaHistory(int dia, int mes, int ano, Sistema *sistema,char *current_language) {
    // Check if the date is valid based on the current date in the system.
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < sistema->ano_atual ||
        (ano == sistema->ano_atual && mes == sistema->mes_atual && sistema->dia_atual < dia) ||
        (ano == sistema->ano_atual && sistema->mes_atual <mes )) {
        Error_invalid_date(current_language);
        return 0;
    }
    return 1;
}

/**
 * @brief Sorts the batches by date in ascending order.
 * 
 * @param sistema Pointer to the vaccination system structure.
 */
void sortLotesPorData(Sistema *sistema) {
    for (int i = 0; i < sistema->numLotes - 1; i++) {
        for (int j = 0; j < sistema->numLotes - 1 - i; j++) {
            
            // Compare the dates of two batches and swap them if necessary.
            Lote *lote1 = &sistema->lotes[j];
            Lote *lote2 = &sistema->lotes[j + 1];
            if (lote1->ano > lote2->ano || 
                (lote1->ano == lote2->ano && lote1->mes > lote2->mes) ||
                (lote1->ano == lote2->ano && lote1->mes == lote2->mes && lote1->dia > lote2->dia) ||
                (lote1->ano == lote2->ano && lote1->mes == lote2->mes && lote1->dia == lote2->dia 
                    && strcmp(lote1->lote, lote2->lote) > 0)) {
                Lote temp = *lote1;
                *lote1 = *lote2;
                *lote2 = temp;
            }
        }
    }
}

/**
 * @brief Clears the input buffer until a newline or EOF is encountered.
 * 
 * @note This function is used to discard any remaining 
 * characters in the input buffer or any input that
 * is invalid at first.
 */
void clearinput() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
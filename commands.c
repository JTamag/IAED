/**
 * Implementation of the commands for the vaccination system.
 * @file: commands.c
 * @author: ist1114613 (João Tamagnini)
 */
#include "headers.h"

/**
 * @brief Creates a new vaccine batch.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param current_language Language for error messages.
 * 
 * @note Possible Errors:
 * - too many vaccines 
 * - invalid name
 * - duplicate batch number
 * - invalid batch
 * - invalid date
 * - invalid quantity
 *
 * @return On success prints the batch number, otherwise prints an error message.
*/
void comandoc(Sistema *sistema,char *current_language) {
    // Check if the system has reached the maximum number of batches.
    if (!valid_amount_of_batches(sistema,current_language)) return;

    // Reading the input line and extracting parameters.
    Lote novoLote;
    char nome[MAX_INSTRUCAO];
    char lote[MAX_INSTRUCAO];
    int dia, mes, ano, quantidade;
    char linha[MAX_INSTRUCAO];
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%s %d-%d-%d %d %s", lote, &dia, &mes, &ano, &quantidade, nome);

    
    // Error checks.
    if (valid_name(nome,current_language) == 0) return;
    if (duplicate_batch(sistema, lote,current_language) == 0) return;
    if (islower(nome[0])) {
        printf("vaccine name cannot begin with a lowercase letter\n");
         return; 
     }
    if (valid_batch(current_language, lote) == 0) return;
    if (!datavalida(dia, mes, ano, sistema,current_language)) return;
    if (valid_quantity(quantidade,current_language) == 0) return;

    // Assigning values to the new batch.
    strcpy(novoLote.lote, lote);
    novoLote.dia = dia;
    novoLote.mes = mes;
    novoLote.ano = ano;
    novoLote.quantidade = quantidade;
    strcpy(novoLote.nome, nome);
    novoLote.numInoculacoes = 0;
    sistema->lotes[sistema->numLotes++] = novoLote;
    printf("%s\n", lote);
}

/**
 * @brief Lists all vaccine batches or those matching specific names.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param current_language Language for error messages.
 * 
 * @note If a batch name is provided and it is not found, the following error 
 * message is printed <vaccine_name>: no such vaccine.
 * 
 * @return Prints the details of the batches or an error message 
 * if a batch name is provided and it is not found.
*/
void comandol(Sistema *sistema,char *current_language) {
    // Reading the input line and extracting batch names.
    char linha[MAX_INSTRUCAO];
    fgets(linha, sizeof(linha), stdin);
    linha[strcspn(linha, "\n")] = 0;
    char *nomes[MAX_LOTES];
    int numNomes = 0;
    char *token = strtok(linha, " ");
    while (token != NULL) {
        nomes[numNomes++] = token;
        token = strtok(NULL, " ");
    }
    sortLotesPorData(sistema);

    /* If batch names are provided, check if the provided names exist in the 
    system,if they do not exist print an error message.*/
    // Otherwise, list all batches. 
    if (numNomes>0) {
        for (int i = 0; i < numNomes; i++) {
            int existe = 0;
            for (int j = 0; j < sistema->numLotes; j++) {
                if (strcmp(sistema->lotes[j].nome, nomes[i]) == 0) {
                    printf("%s %s %02d-%02d-%d %d %d\n",sistema->lotes[j].nome,sistema->lotes[j].lote,
                           sistema->lotes[j].dia,sistema->lotes[j].mes,sistema->lotes[j].ano,
                           sistema->lotes[j].quantidade,sistema->lotes[j].numInoculacoes);
                existe = 1;}
            }if (!existe) {
                printf("%s: ", nomes[i]);
                Error_non_existent_vaccine(current_language);
            }
        }
    } else {
        all_batches(sistema);
    }
}

/**
 * @brief Vaccinates a user with a specific vaccine batch
 * with the oldest vaccine in the systems as long as that
 * vaccine is available and if it is not expired.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param current_language Language for error messages.
 * 
 * @note Possible Errors:
 * - no stock
 * - already vaccinated
 * - exceeded memory capacity
 *
 * @return On success prints the batch number, otherwise prints an error message.
 */
void comandoa(Sistema *sistema, char *current_language) {
    // Extracting user and vaccine names from the input line.
    char linha[MAX_INSTRUCAO];
    if (!fgets(linha, sizeof(linha), stdin)){
        return;
    }
    linha[strcspn(linha, "\n")] = '\0';
    char nomeUtente[MAX_INSTRUCAO];
    char nomeVacina[MAX_NOME];
    extrai_parametros_a(linha, nomeUtente, nomeVacina);

    // Sort the batches by date.
    sortLotesPorData(sistema); 

    /* Looking for the vaccine batch in the system
    if no valid vaccine is found or if the user has been
    vaccinated by a vaccine with the same name on the 
    same date print an error.*/
    Lote *loteSelecionado = NULL;
    search_for_vaccine(sistema, nomeVacina, &loteSelecionado, current_language);
    if (loteSelecionado == NULL) {
        return;
    }
    if (!already_vaccinated(sistema, nomeUtente, current_language, loteSelecionado)) {
        return;
    }
    /* Check if the system has reached the maximum number of inoculations
    and if it has increase the memory allocated towards inoculations*/
    if (sistema->numInoculacoes >= sistema->capacidadeInoculacoes) {
        if (!expandeInoculacoes(sistema,current_language)) {
            return; 
        }
    }
    // Vaccination process.
    inocullation(loteSelecionado, sistema, nomeUtente, current_language);
}

/**
 * @brief Deletes a vaccine batch or sets its quantity to zero.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param current_language Language for error messages.
 * 
 * @note If the batch is not found, an error message is printed
 * in the format <batch>: no such batch.
 * 
 * @return Prints the number of inoculations deleted or an error 
 * message if the batch is not found.
 */
void comandor(Sistema *sistema,char *current_language) {
    // Initialize variables and read batch from input.
    char lote[MAX_INSTRUCAO];
    scanf("%s", lote);
    int found = 0;
    int numInoculacoesV = 0;

    /* Check if the batch exists in the system and count the number of 
    inoculations and if said number is 0 delete the batch.*/
    for (int i = 0; i < sistema->numLotes; i++) {
        if (strcmp(sistema->lotes[i].lote, lote) == 0) {
            found = 1;
            for (int j = 0; j < sistema->numInoculacoes; j++) {
                if (strcmp(sistema->inoculacoes[j].lote, lote) == 0) {
                    numInoculacoesV++;
                }
            }
            if (numInoculacoesV == 0) {
                sistema->lotes[i] = sistema->lotes[--sistema->numLotes];
            } else {
                sistema->lotes[i].quantidade = 0;
            }
            printf("%d\n", numInoculacoesV);
            break;
        }
    }

    // If the batch was not found print the error message <batch>: no such batch.
    if (!found) {
        printf("%s: ",lote);
        Error_non_existent_batch(current_language);
    }
}


void comandov(Sistema *sistema){
    char lote[MAX_LOTE];
    int dia, mes, ano;
    scanf("%s %d-%d-%d",lote, &dia, &mes, &ano);
    int i;
    int existe = 0;
    for (i=0;i < sistema->numLotes;i++){
        if (strcmp(sistema->lotes[i].lote,lote)==0){
            existe= 1;
            break;
        }
    }
    if (!existe) {
        printf("%s: no such batch\n",lote);
        return;
    }
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < sistema->ano_atual ||
        (ano == sistema->ano_atual && mes == sistema->mes_atual && sistema->dia_atual > dia) ||
        (ano == sistema->ano_atual && sistema->mes_atual > mes)) {
        printf("invalid date\n");     
        return;
    }

    // Determine the number of days in the month.
    int diasNoMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    // Check for leap year, and adjust February's days accordingly.
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) {
        diasNoMes[1] = 29; 
    }

    // Check if the day exceeds the number of days in the month.
    if (dia > diasNoMes[mes - 1]) {
        printf("invalid date\n");
        return;
    }
    sistema->lotes[i].dia = dia;
    sistema->lotes[i].mes = mes;   
    sistema->lotes[i].ano = ano;
    printf("%d\n",sistema->lotes[i].quantidade);
    return;
}
/**
 * @brief Deletes inoculations from the system.
 * @details This function deletes inoculations based on the user name
 *  or user name and date or username,date and batch number.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param current_language Language for error messages.
 * 
 * @note Possible Errors:
 * - <username>: no such user
 * - invalid date
 * - <batch>: no such batch
 *
 * @return Prints the number of inoculations deleted or an error message.
*/
void comandod(Sistema *sistema, char *current_language) {
    // Initialize variables and read input line.
    char linha[MAX_INSTRUCAO];
    char nomeUtente[N_UTENTE];
    int dia = -1, mes = -1, ano = -1;
    int numArgs = 0;
    char lote[MAX_LOTE] = "";

    fgets(linha, sizeof(linha), stdin);
    linha[strcspn(linha, "\n")] = 0;
    numArgs = sscanf(linha, "%s %d-%d-%d %s", nomeUtente, &dia, &mes, &ano, lote);

    // If no arguments are provided, return.
    if (numArgs < 1) {
        return;
    }
    // Check if the batch exists in the system.
    if (numArgs == 5) {
        if (!existing_batch(sistema, lote, current_language)) {
            return;
        }
    }
    // Check if the data is valid.
    if (numArgs >= 4 && !datavalidaHistory(dia, mes, ano, sistema, current_language)) {
        return;
    }
    /* Check if the user exists in the system and delete
    inoculations based on the provided arguments.*/    
    delete_inocullations(sistema, nomeUtente, current_language, dia, mes,
         ano, lote, numArgs);
}

/**
 * @brief Lists all inoculations or those matching a specific user.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param current_language Language for error messages.
 * 
 * @note If a user name is provided and it is not found, an error message 
 * is printed in the format <username>: no such user.
 * 
 * @return Prints the details of the inoculations or an error message
 *  if a user name is provided and it is not found.
 */
void comandou(Sistema *sistema,char *current_language) {
    // Initialize variables and read input line.
    char linha[MAX_INSTRUCAO];
    fgets(linha, sizeof(linha), stdin);
    linha[strcspn(linha, "\n")] = 0;
    // If no user name is provided, list all inoculations.
    if (strlen(linha) == 0) {
        all_inocullations(sistema);
    } else {
        // Extract user name from the input line.
        char nomeUtente[MAX_INSTRUCAO];
        if (linha[1] == '"') {
            char *start = strchr(linha, '"');
            char *end = strrchr(linha, '"');
            if (start != NULL && end != NULL && start != end) {
                strncpy(nomeUtente, start + 1, end-start-1);
                nomeUtente[end-start-1] = '\0';
            }
        } else {
            sscanf(linha, "%s", nomeUtente);
        }
        // Check if the user exists in the system and list their inoculations.
        user_inocullations(sistema, nomeUtente, current_language);
    }
}

/**
 * @brief Updates or gives the current date of the system.
 * 
 * @param sistema Pointer to the vaccination system structure.
 * @param current_language Language for error messages.
 * 
 * @note If the date is invalid, an error message is printed
 * with the message "invalid date".
 * 
 * @return Prints the updated date in the format dd-mm-yyyy.
 */
void comandot(Sistema *sistema, char *current_language) {
    // Initialize variables and read input line.
    char data[MAX_DATA];

    // If no date is provided, print the current date.
    if (fgets(data, sizeof(data), stdin) == NULL || data[0] == '\n') {
        printf("%02d-%02d-%d\n", sistema->dia_atual, sistema->mes_atual,
             sistema->ano_atual);
        return;
    }
    
    // Extract day, month, and year from the input line.
    int dia, mes, ano;

    // Check if the input format is valid.
    if (sscanf(data, "%d-%d-%d", &dia, &mes, &ano) != 3) {
        return;
    }
    
    // Check if the date is valid.
    if (!datavalida(dia, mes, ano, sistema, current_language)){
        return;
    }
    
    // Update the system date and print it.
    sistema->dia_atual = dia;
    sistema->mes_atual = mes;
    sistema->ano_atual = ano;
    printf("%02d-%02d-%d\n", sistema->dia_atual, sistema->mes_atual, 
        sistema->ano_atual);
}
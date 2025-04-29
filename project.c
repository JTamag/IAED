/* iaed25 - ist1114613 - project */
/**
 * A program exemplifying a vaccine management system in C
 * Each vaccine has a batch number, name, date, and quantity
 * @file: project.c
 * @author: ist1114613 (João Tamagnini)
 */
#include "headers.h"
/**
 * @brief Main function of the vaccination management program.
 * 
 * This function initializes the system, sets the language based on 
 * command-line arguments, and enters a command-processing loop.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * 
 * @return int Returns 0 on program termination.
 */
int main(int argc,const char *argv[]) {
    char *current_language = "en";

    /**
     * @brief Set language to Portuguese if specified via command-line.
     */
    if (argc > 1 && strcmp(argv[1], "pt") == 0) {
        current_language = "pt";
    }

    /**
     * @brief Initialize the vaccination system structure.
     */
    Sistema sistema;
    sistema.numLotes = 0;
    sistema.numInoculacoes = 0;
    sistema.capacidadeInoculacoes = MAX_LOTES;
    sistema.dia_atual = 1;
    sistema.mes_atual = 1;
    sistema.ano_atual = 2025;
    sistema.inoculacoes = (Inoculacao *)malloc(MAX_LOTES * sizeof(Inoculacao));

    /**
     * @brief Command processing loop. Reads commands from stdin and dispatches them.
     */
    char comando;
    while (scanf(" %c", &comando) != EOF) {
        switch(comando) {
            case 'q':cleanupSistema(&sistema);return 0;
            case 'c': comandoc(&sistema, current_language); break;
            case 'l': comandol(&sistema, current_language); break;
            case 'a': comandoa(&sistema, current_language); break;
            case 'r': comandor(&sistema, current_language); break;
            case 'd': comandod(&sistema, current_language); break;
            case 'u': comandou(&sistema, current_language); break;
            case 't': comandot(&sistema, current_language); break;
            case 'v': comandov(&sistema); break;
            default:  clearinput();break;
        }   
    }
    /**
     * @brief Ensure that memory is freed in case of wrong termination.
     */
    cleanupSistema(&sistema);
    return 0;
}
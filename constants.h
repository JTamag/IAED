/** 
* A file to include all the constants used in the project 
* @file constants.h
* @author: ist1114613 (João Tamagnini)
*/

#ifndef CONSTANTS
#define CONSTANTS

/// @defgroup Constants_Mem constants used for memory allocation and limits.
/// @{

/// Maximum number of vaccine batches.
#define MAX_LOTES 1000

/// Maximum length of a vaccine name.
#define MAX_NOME 50

/// Maximum length of a batch number.
#define MAX_LOTE 20

/// Maximum length of a date string.
#define MAX_DATA 20

/// Maximum length of an instruction string.
#define MAX_INSTRUCAO 65535

/// Usual length of a user name.
#define N_UTENTE 200

/// @}

/// @defgroup Constants_Errors constants used for error messages in english.
/// @{

/// Error message for exceeding memory capacity.
#define ENOMEMORY_EN "No memory."

/// Error message for exceeding the maximum number of vaccine batches.
#define E2MANYCONT_EN "too many vaccines"

/// Error message for creating a batch with a duplicate batch number.
#define EDUPBATCH_EN "duplicate batch number"

/// Error message for creating a batch with invalid characters or exceeding the maximum length.
#define EINVBATCH_EN "invalid batch"

/// Error message for creating a vaccine name with invalid characters or exceeding the maximum length.
#define EINVNAME_EN "invalid name"

/// Error message for providing an invalid date.
#define EINVDATE_EN "invalid date"

/// Error message for providing an invalid quantity.
#define EINVQUANT_EN "invalid quantity"

/// Error message for attempting to use a vaccine batch with no stock.
#define ENOSTOCK_EN "no stock"

/// Error message for attempting to vaccinate a user who has already been vaccinated.
#define EALVACC_EN "already vaccinated"

/// Error message for referencing a non-existent vaccine.
#define ENOSUCHV_EN "no such vaccine"

/// Error message for referencing a non-existent batch.
#define ENOSUCHBATCH_EN "no such batch"

/// Error message for referencing a non-existent user.
#define ENOSUCHUSER_EN "no such user"

/// @}

/// @defgroup Constants_Errors_PT constants used for error messages in portuguese.
/// @{

/// Mensagem de erro para capacidade de memória excedida.
#define ENOMEMORY_PT "sem memória"

/// Mensagem de erro para exceder o número máximo de lotes de vacinas.
#define E2MANYCONT_PT "demasiadas vacinas"

/// Mensagem de erro para criar um lote com um número duplicado.
#define EDUPBATCH_PT "número de lote duplicado"

/// Mensagem de erro para criar um lote com caracteres inválidos ou comprimento excedido.
#define EINVBATCH_PT "lote inválido"

/// Mensagem de erro para criar um nome de vacina com caracteres inválidos ou comprimento excedido.
#define EINVNAME_PT "nome inválido"

/// Mensagem de erro para fornecer uma data inválida.
#define EINVDATE_PT "data inválida"

/// Mensagem de erro para fornecer uma quantidade inválida.
#define EINVQUANT_PT "quantidade inválida"

/// Mensagem de erro para tentar usar um lote de vacinas sem stock.
#define ENOSTOCK_PT "esgotado"

/// Mensagem de erro para tentar vacinar um utente já vacinado.
#define EALVACC_PT "já vacinado"

/// Mensagem de erro para referenciar uma vacina inexistente.
#define ENOSUCHV_PT "vacina inexistente"

/// Mensagem de erro para referenciar um lote inexistente.
#define ENOSUCHBATCH_PT "lote inexistente"

/// Mensagem de erro para referenciar um utente inexistente.
#define ENOSUCHUSER_PT "utente inexistente"

/// @}

#endif 
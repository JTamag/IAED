/**
 * This project consists of building a vaccine management system that handles:
 * - Registration of vaccine batches, including their name, batch number, expiration date, and doses.
 * - Management of vaccine applications (inoculations) to users, tracking the batch used and application date.
 * - Commands to interact with the system:
 *   - `q`: Terminates the program.
 *   - `c`: Adds a new vaccine batch to the system.
 *   - `l`: Lists all vaccine batches or those matching specific names.
 *   - `a`: Applies a vaccine dose to a user.
 *   - `r`: Removes the availability of a vaccine batch.
 *   - `d`: Deletes a user's vaccination history.
 *   - `u`: Lists all vaccinations or those of a specific user.
 *   - `t`: Updates or retrieves the current system date.
 * - Constraints:
 *   - Maximum of 1000 vaccine batches.
 *   - No global variables allowed.
 *   - Dynamic memory management is required.
 * - Error handling for invalid inputs, memory exhaustion, and other edge cases.
 * - The program must support both English and Portuguese error messages.
 * - Input and output must strictly follow the specified format.
 * Format:
 * - Input:
 *   - Commands are provided via standard input.
 *   - Each command follows a specific format (e.g., `c <name> <batch> <date> <quantity>`).
 *   - Dates can be entered with one or two digits for day and month.
 *   - User names can include spaces and are enclosed in quotes if they do.
 * - Output:
 *   - Results of commands are printed to standard output.
 *   - Dates are always displayed with two digits for day and month.
 *   - Error messages are displayed in the selected language (English or Portuguese).
 * - Constraints:
 *   - Input and output must strictly adhere to the specified format.
 */
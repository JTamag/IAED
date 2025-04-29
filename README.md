# Vaccine Management System

## Project Overview
This project consists of building a vaccine management system that handles:
- **Registration of Vaccine Batches**:
  - Includes their name, batch number, expiration date, and doses.
- **Management of Vaccine Applications (Inoculations)**:
  - Tracks users, the batch used, and the application date.
- **Commands**:
  - `q`: Terminates the program.
  - `c`: Adds a new vaccine batch to the system.
  - `l`: Lists all vaccine batches or those matching specific names.
  - `a`: Applies a vaccine dose to a user.
  - `r`: Removes the availability of a vaccine batch.
  - `d`: Deletes a user's vaccination history.
  - `u`: Lists all vaccinations or those of a specific user.
  - `t`: Updates or retrieves the current system date.
  - `v`: updates the expiration date of a specific vaccine batch in the system.

## Constraints
- Maximum of 1000 vaccine batches.
- No global variables allowed.
- Dynamic memory management is required.
- Error handling for invalid inputs, memory exhaustion, and other edge cases.
- The program must support both English and Portuguese error messages.

## Input/Output Format
### Input:
- Commands are provided via standard input.
- Each command follows a specific format (e.g., `c <name> <batch> <date> <quantity>`).
- Dates can be entered with one or two digits for day and month.
- User names can include spaces and are enclosed in quotes if they do.

### Output:
- Results of commands are printed to standard output.
- Dates are always displayed with two digits for day and month.
- Error messages are displayed in the selected language (English or Portuguese).

## Additional Notes
- Input and output must strictly adhere to the specified format.

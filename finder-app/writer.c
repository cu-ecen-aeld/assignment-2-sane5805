/*==========================================================================
  File Name: writer.c
  This file contains the writer code for writing a string to a file.

  Author: Saurav Negi
========================================================================== */

/*==========================================================================
  Include files
========================================================================== */
#include <stdio.h>    // Standard I/O operations
#include <stdlib.h>   // Standard library functions
#include <string.h>   // String manipulation functions
#include <syslog.h>   // System logging functions

/* Description: writeToFile
 * Writes a string to a file.
 *
 * Parameters:
 * writefile : The name of the file to write to.
 * writestr  : The string to write to the file.
 *
 * Return Type:
 * int : Returns 0 on success, 1 on failure.
 */
int writeToFile(char *writefile, char *writestr);

/* Description: main
 * The main function of the program. It handles command-line arguments, opens a connection
 * to the system log, writes a string to a file, logs messages, and closes the connection to the log.
 *
 * Parameters:
 * argc : The number of command-line arguments.
 * argv : An array of strings containing the command-line arguments.
 *
 * Return Type:
 * int : Returns 0 on success, 1 on failure.
 */
int main(int argc, char *argv[]) {
    
    // Open a connection to the system log
    openlog("log", LOG_PID, LOG_USER);
    
    // Check if both arguments are provided
    if (argc != 3) {
        syslog(LOG_ERR, "Usage: ./writer <writefile> <writestr>\n");
        return 1;
    }

    // Assign command line arguments to variables
    char *writefile = argv[1];
    char *writestr = argv[2];

    // Check if 'writefile' argument is not empty
    if (writefile == NULL || strlen(writefile) == 0) {
        syslog(LOG_ERR, "Error: 'writefile' argument is empty.\n");
        return 1;
    }

    // Check if 'writestr' argument is not empty
    if (writestr == NULL || strlen(writestr) == 0) {
        syslog(LOG_ERR, "Error: 'writestr' argument is empty.\n");
        return 1;
    }

    // Call the writeToFile function to handle writing to the file
    int result = writeToFile(writefile, writestr);

    // Log the message with syslog
    syslog(LOG_DEBUG, "Writing '%s' to '%s'", writestr, writefile);
    
    // Close the connection to the system log
    closelog();

    // Exit with success or failure status
    return result;
}

/* Description: writeToFile
 * Writes a string to a file.
 *
 * Parameters:
 * writefile : The name of the file to write to.
 * writestr  : The string to write to the file.
 *
 * Return Type:
 * int : Returns 0 on success, 1 on failure.
 */
int writeToFile(char *writefile, char *writestr) {
    // Open the file for writing
    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error: Failed to open file '%s' for writing.\n", writefile);
        return 1; // Return failure status
    }

    // Write the content to the file
    if (fprintf(file, "%s", writestr) < 0) {
        syslog(LOG_ERR, "Error: Failed to write to file '%s'.\n", writefile);
        fclose(file);
        return 1; // Return failure status
    }

    // Close the file
    fclose(file);

    return 0; // Return success status
}

#include <unistd.h> // Required for the read() and write() system calls
#include <stdio.h>  // Required for perror() to display error messages

// Define a constant for the size of our buffer.
// This determines how many bytes we try to read at a time.
#define BUFFER_SIZE 1024

/**
 * This program demonstrates the use of basic I/O system calls.
 * It reads data from Standard Input (file descriptor 0) and writes it
 * to Standard Output (file descriptor 1). It acts like a simple
 * version of the 'cat' command when run without arguments.
 */
int main() {
    // Create a character array (buffer) to temporarily store data.
    char buffer[BUFFER_SIZE];
    
    // 'ssize_t' is a data type used to represent the size of an object,
    // which can also return a negative value to indicate an error.
    // It's the return type for read() and write().
    ssize_t bytes_read;

    // This is the core loop of the program.
    // 1. read() attempts to read data from STDIN (file descriptor 0) into our buffer.
    // 2. The number of bytes successfully read is stored in 'bytes_read'.
    // 3. The loop continues as long as read() returns a value greater than 0.
    //
    // A return value of 0 means "End of File" (e.g., user pressed Ctrl+D).
    // A negative value means an error occurred.
    while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0) {
        // Now, write the data we just read from the buffer to STDOUT (file descriptor 1).
        // We tell write() to write exactly 'bytes_read' bytes.
        ssize_t bytes_written = write(1, buffer, bytes_read);

        // It's good practice to check if the write operation was successful.
        // A short write (writing fewer bytes than requested) can indicate a problem.
        if (bytes_written != bytes_read) {
            perror("Error writing to STDOUT");
            return 1; // Exit with a non-zero status code to indicate an error.
        }
    }

    // If the loop terminates, we check if it was due to a read error.
    if (bytes_read < 0) {
        perror("Error reading from STDIN");
        return 1; // Exit with an error code.
    }

    // If we reach here, the program completed successfully (end of file was reached).
    return 0;
}

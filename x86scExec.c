/*
	Author: G.Narasimha Reddy

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

// Function pointer to the shellcode
typedef void (*ShellcodeFunction)();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Tool: x86 (32 bit) shellcode executor\n");
		printf("Author: G Narasimha Reddy\n\n");
		printf("Usage: %s <shellcode_file>\n", argv[0]);
        return 1;
    }

    FILE *file;
    long file_size;
    char *buffer;
    ShellcodeFunction shellcode;

    // Open the binary file containing the shellcode
    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Error: Unable to open file %s.\n", argv[1]);
        return 1;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    // Allocate memory to store the shellcode
    buffer = (char *)VirtualAlloc(NULL, file_size, MEM_COMMIT, PAGE_READWRITE);
    if (buffer == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    // Read the shellcode into memory
    fread(buffer, 1, file_size, file);
    fclose(file);

    // Make the allocated memory executable
    DWORD oldProtect;
    if (!VirtualProtect(buffer, file_size, PAGE_EXECUTE_READ, &oldProtect)) {
        printf("Error: Failed to make memory executable.\n");
        VirtualFree(buffer, 0, MEM_RELEASE);
        return 1;
    }

    // Print the location of the loaded file
    printf("[+] Loaded file: %s\n", argv[1]);

    // Print the size of the shellcode
    printf("[+] Size of shellcode: %ld bytes\n", file_size);

    // Convert buffer to a function pointer
    shellcode = (ShellcodeFunction)buffer;

    // Print the address where the shellcode is loaded in memory
    printf("[+] Address at which shellcode is loaded: 0x%p\n", shellcode);

    // Pause the execution to allow for debugging
    printf("[!] Attach a debugger to '%s'. Place a breakpoint at the above address.\n(Note: If using x32Dbg, you can use 'bp 0x%p' to set breakpoint from the 'Command' window at the bottom).\n\nPress 'Enter' to start execution of shellcode...\n", argv[0], shellcode);
    getchar();

    // Execute the shellcode
    printf("Executing shellcode...\n");
	printf("Breakpoint must have hit in debugger. Good luck with your shellcode analysis!\n");
    shellcode();

    // Free the allocated memory
    // VirtualFree(buffer, 0, MEM_RELEASE);

    return 0;
}

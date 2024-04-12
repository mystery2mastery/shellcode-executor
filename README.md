# shellcode executor

This is a small program to execute x86 and x64 shellcodes. This is primarily intended to aid debugging of shellcode. This tool loads the shellcode into memory and waits for the user input to start execution. Meanwhile, the user can attach a debugger to the tool and follow along.



## Usage:

1. For 64bit shellcode execution use x64scExec.exe
2. For 32bit shellcode execution use x86scExec.exe



## Example:

```bat
C:\Users\ElNino\Desktop\shellcode_executor>x64scExec.exe sample_shellcodes\x64msgbox.dat
[+] Loaded file: sample_shellcodes\x64msgbox.dat
[+] Size of shellcode: 433 bytes
[+] Address at which shellcode is loaded: 0x000001E613890000
[!] Attach a debugger to 'x64scExec.exe'. Place a breakpoint at the above address.
(Note: If using x64Dbg, you can use 'bp 0x000001E613890000' to set breakpoint from the 'Command' window at the bottom).

Press 'Enter' to start execution of shellcode...
```



## How does this tool work?

1. Opens the given shellcode blob and gets its size.
2. Allocates the required memory using `VirtualAlloc()` as 'RW'.
3. Copies the contents into the allocated region.
4. Modifies the memory access permission to 'RX' using `VirtualProtect()`.
5. Waits for the user input to start execution.
6. Calls the allocated address and starts execution.

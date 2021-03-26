#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "functions.h"

int main()
{
    compilate compilation;
    compilation.file = fopen ("Code.txt", "rb");
    compilation.read_file ();
    if (compilation.status == PROBLEM) {
        printf ("Mistake in finding file\n");
        return 1;
    }

    struct Instruction* command = (struct Instruction*) calloc (compilation.num_strings, sizeof (struct Instruction));
    compilation.commands = command;

    compilation.read_strings ();
    if (compilation.status == PROBLEM) {
        printf ("Mistake in writing code in %dth operation\n", compilation.mistake_string);
        return 1;
    }

    compilation.check_logic ();
    if (compilation.status == PROBLEM) {
        printf("Mistake in logic in %dth operation\n", compilation.mistake_string);
        return 1;
    }
    else
        printf("Your program is ready to do!\n");


    compilation.read_code = fopen ("./Processor/read_code.bin", "wb");
    compilation.write_code ();
    if (compilation.status == PROBLEM) {
        printf("Mistake in lables in %dth operation\n", compilation.mistake_string);
    }

    //for (uint32_t i = 0; i < compilation.num_strings; ++i)
      //  printf("CMD_flag: %c\tCMD_code: %c\tARG_flag: %c\tvalue: %ld\n", compilation.commands[i].CMD_flag, compilation.commands[i].CMD_code, compilation.commands[i].ARG_flag, compilation.commands[i].value);

    compilation.close_programm ();
    if (compilation.status == PROBLEM)
        return 0;
    else {
        return 1;
    }
}

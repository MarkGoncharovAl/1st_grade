#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "tables.h"

struct operation {
    char CMD_flag;
    char CMD_code;
    char ARG_flag;
    int64_t value;
};

class process {
    public:
        uint32_t mistake_string;
        uint32_t num_strings;
        uint32_t num_cur_string;
        uint32_t num_labels;
        int32_t labels[200];

        char status;
        int64_t CMP_value;
        operation* opr;
        Stack program;
        Stack programE;
        FILE* file;

        int64_t trash;
        char trash_char[3];

        void open_file ();
        void do_program ();
        int64_t check_var ();

        void do_push ();
        void do_pop ();
        void do_add ();
        void do_sub ();
        void do_mult ();
        void do_div ();
        void do_scan ();
        void do_print ();

        void do_pushE ();
        void do_popE ();
        void do_addE ();
        void do_subE ();
        void do_multE ();
        void do_divE ();
        void do_printE ();

        void do_cmp ();

        void close_program ();
};

int main()
{
    process processing;

    processing.open_file ();
    processing.do_program ();

    if (processing.status == PROBLEM) {
        printf("Mistake in processing in %dth operation\n", processing.mistake_string);
        processing.program.OK();
        return 1;
    }

    processing.close_program ();
    return 0;
}



void process::open_file ()
{
    file = fopen ("read_code.bin", "rb");

    fread (&num_strings, sizeof (uint32_t), 1, file);
    fread (&num_labels, sizeof (uint32_t), 1, file);

    for (int i = 0; i < 200; ++i)
        labels[i] = -1;

    for (uint32_t i = 0; i < num_labels; ++i) {
        fread (trash_char, sizeof (char), 3, file);
        fread (&trash, sizeof (int64_t), 1, file);
        labels[trash_char[2] - '0'] = trash;
    }

    opr = (struct operation*) calloc (num_strings, sizeof (struct operation));
    for (uint32_t i = 0; i < num_strings; ++i) {
        fread (&opr[i].CMD_flag, sizeof (char), 1, file);
        fread (&opr[i].CMD_code, sizeof (char), 1, file);
        fread (&opr[i].ARG_flag, sizeof (char), 1, file);
        fread (&opr[i].value, sizeof (int64_t), 1, file);
    }
}

void process::do_program ()
{
    program.init (num_strings * 10);
    programE.init (num_strings * 10);
    status = ORDINARY;

    num_cur_string = 0;
    while (num_cur_string < num_strings) {

        switch (opr[num_cur_string].CMD_code) {
        case (CMD_push):
            do_push ();
            if (program.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_pushE):
            do_pushE ();
            if (programE.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_pop):
            do_pop ();
            if (program.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_popE):
            do_popE ();
            if (programE.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_add):
            do_add ();
            if (program.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_addE):
            do_addE ();
            if (programE.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_sub):
            do_sub ();
            if (program.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_subE):
            do_subE ();
            if (programE.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_mult):
            do_mult ();
            if (program.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_multE):
            do_multE ();
            if (programE.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_div):
            do_div ();
            if (program.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_divE):
            do_divE ();
            if (programE.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_scan):
            do_scan ();
            if (program.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_print):
            do_print ();
            if (program.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_printE):
            do_printE ();
            if (programE.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            break;
        case (CMD_jump):
            if (labels[opr[num_cur_string].value] == -1) {
                printf("LABELS:\n");
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            num_cur_string = labels[opr[num_cur_string].value] - 2;
            break;
        case (CMD_cmp):
            do_cmp ();
            break;
        case (CMD_equal):
            if (labels[opr[num_cur_string].value] == 0) {
                printf("COMPARING = :\n");
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            if (CMP_value == 0)
                num_cur_string = labels[opr[num_cur_string].value] - 2;
            break;
        case (CMD_nequal):
            if (labels[opr[num_cur_string].value] == 0) {
                printf("COMPARING != :\n");
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            if (CMP_value != 0)
                num_cur_string = labels[opr[num_cur_string].value] - 2;
            break;
        case (CMD_big):
            if (labels[opr[num_cur_string].value] == 0) {
                printf("COMPARING:\n");
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            if (CMP_value > 0)
                num_cur_string = labels[opr[num_cur_string].value] - 2;
            break;
        case (CMD_small):
            if (labels[opr[num_cur_string].value] == 0) {
                printf("COMPARING:\n");
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            if (CMP_value < 0)
                num_cur_string = labels[opr[num_cur_string].value] - 2;
            break;
        case (CMD_bigeq):
            if (labels[opr[num_cur_string].value] == 0) {
                printf("COMPARING:\n");
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            if (CMP_value >= 0)
                num_cur_string = labels[opr[num_cur_string].value] - 2;
            break;
        case (CMD_smalleq):
            if (labels[opr[num_cur_string].value] == 0) {
                printf("COMPARING:\n");
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            if (CMP_value <= 0)
                num_cur_string = labels[opr[num_cur_string].value] - 2;
            break;
        case (CMD_exit):
            printf("Program is turning off...\n");
            if (program.status != ORDINARY_CASE) {
                mistake_string = num_cur_string + 1;
                status = PROBLEM;
                return;
            }
            return;
            break;
        default:
            status = PROBLEM;
            return;
            break;

        }
        num_cur_string++;
    }
    status = ORDINARY;
    return;
}

int64_t process::check_var ()
{
    switch (opr[num_cur_string].value) {
    case (1):
        return program.ax;
        break;
    case (2):
        return program.bx;
        break;
    case (3):
        return program.cx;
        break;
    case (4):
        return program.dx;
        break;
    }
    status = PROBLEM;
    return -1;
}

void process::do_push ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        program.push (check_var ());
        return;
    }
    program.push (opr[num_cur_string].value);
}
void process::do_pushE ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        programE.push (check_var ());
        return;
    }
    programE.push (opr[num_cur_string].value);
}
void process::do_pop ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        switch (opr[num_cur_string].value) {
        case (1):
            program.ax = program.pop ();
            break;
        case (2):
            program.bx = program.pop ();
            break;
        case (3):
            program.cx = program.pop ();
            break;
        case (4):
            program.dx = program.pop ();
            break;
        }
        return;
    }
    trash = program.pop ();
}
void process::do_popE ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        switch (opr[num_cur_string].value) {
        case (1):
            program.ax = programE.pop ();
            break;
        case (2):
            program.bx = programE.pop ();
            break;
        case (3):
            program.cx = programE.pop ();
            break;
        case (4):
            program.dx = programE.pop ();
            break;
        }
        return;
    }
    trash = programE.pop ();
}
void process::do_add ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        switch (opr[num_cur_string].value) {
        case (1):
            program.ax = program.sum ();
            break;
        case (2):
            program.bx = program.sum ();
            break;
        case (3):
            program.cx = program.sum ();
            break;
        case (4):
            program.dx = program.sum ();
            break;
        }
        return;
    }
    trash = program.sum ();
}
void process::do_addE ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        switch (opr[num_cur_string].value) {
        case (1):
            program.ax = programE.sum ();
            break;
        case (2):
            program.bx = programE.sum ();
            break;
        case (3):
            program.cx = programE.sum ();
            break;
        case (4):
            program.dx = programE.sum ();
            break;
        }
        return;
    }
    trash = programE.sum ();
}
void process::do_sub ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        switch (opr[num_cur_string].value) {
        case (1):
            program.ax = program.sub ();
            break;
        case (2):
            program.bx = program.sub ();
            break;
        case (3):
            program.cx = program.sub ();
            break;
        case (4):
            program.dx = program.sub ();
            break;
        }
        return;
    }
    trash = program.sub ();
}
void process::do_subE ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        switch (opr[num_cur_string].value) {
        case (1):
            program.ax = programE.sub ();
            break;
        case (2):
            program.bx = programE.sub ();
            break;
        case (3):
            program.cx = programE.sub ();
            break;
        case (4):
            program.dx = programE.sub ();
            break;
        }
        return;
    }
    trash = programE.sub ();
}
void process::do_mult ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        switch (opr[num_cur_string].value) {
        case (1):
            program.ax = program.mult ();
            break;
        case (2):
            program.bx = program.mult ();
            break;
        case (3):
            program.cx = program.mult ();
            break;
        case (4):
            program.dx = program.mult ();
            break;
        }
        return;
    }
    trash = program.mult ();
}
void process::do_multE ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        switch (opr[num_cur_string].value) {
        case (1):
            program.ax = programE.mult ();
            break;
        case (2):
            program.bx = programE.mult ();
            break;
        case (3):
            program.cx = programE.mult ();
            break;
        case (4):
            program.dx = programE.mult ();
            break;
        }
        return;
    }
    trash = programE.mult ();
}
void process::do_div ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        switch (opr[num_cur_string].value) {
        case (1):
            program.ax = program.div ();
            break;
        case (2):
            program.bx = program.div ();
            break;
        case (3):
            program.cx = program.div ();
            break;
        case (4):
            program.dx = program.div ();
            break;
        }
        return;
    }
    trash = program.div ();
}
void process::do_divE ()
{
    if (opr[num_cur_string].ARG_flag == flag_REG) {
        switch (opr[num_cur_string].value) {
        case (1):
            program.ax = programE.div ();
            break;
        case (2):
            program.bx = programE.div ();
            break;
        case (3):
            program.cx = programE.div ();
            break;
        case (4):
            program.dx = programE.div ();
            break;
        }
        return;
    }
    trash = programE.div ();
}
void process::do_scan ()
{
    switch (opr[num_cur_string].value) {
    case (1):
        printf ("Enter ax: ");
        if (scanf ("%ld", &program.ax) != 1) {
            status = PROBLEM;
            program.status = NO_DATA;
        }
        break;
    case (2):
        printf ("Enter bx: ");
        if (scanf ("%ld", &program.bx) != 1) {
            status = PROBLEM;
            program.status = NO_DATA;
        }
        break;
    case (3):
        printf ("Enter cx: ");
        if (scanf ("%ld", &program.cx) != 1) {
            status = PROBLEM;
            program.status = NO_DATA;
        }
        break;
    case (4):
        printf ("Enter dx: ");
        if (scanf ("%ld", &program.dx) != 1) {
            status = PROBLEM;
            program.status = NO_DATA;
        }
        break;
    }
}

void process::do_cmp ()
{
    if (opr[num_cur_string].ARG_flag == flag_NUM) {
        CMP_value = opr[num_cur_string].value;
        return;
    }
    if (opr[num_cur_string].ARG_flag > '4') {
        switch (opr[num_cur_string].ARG_flag) {
        case ('5'):
            CMP_value = program.ax;
            break;
        case ('6'):
            CMP_value = program.bx;
            break;
        case ('7'):
            CMP_value = program.cx;
            break;
        case ('8'):
            CMP_value = program.dx;
            break;
        }
        switch (opr[num_cur_string].value) {
        case (1):
            CMP_value -= program.ax;
            break;
        case (2):
            CMP_value -= program.bx;
            break;
        case (3):
            CMP_value -= program.cx;
            break;
        case (4):
            CMP_value -= program.dx;
            break;
        }
    }
    else {
        switch (opr[num_cur_string].ARG_flag) {
        case ('1'):
            CMP_value = program.ax;
            break;
        case ('2'):
            CMP_value = program.bx;
            break;
        case ('3'):
            CMP_value = program.cx;
            break;
        case ('4'):
            CMP_value = program.dx;
            break;
        }
        CMP_value -= opr[num_cur_string].value;
    }
    return;
}

void process::do_print ()
{
    if (opr[num_cur_string].ARG_flag == flag_NULL) {
        printf("Printing status of your program:\n");
        for (size_t i = 0; i < program.Size; ++i) {
            printf("[%ld/%ld]: %ld\n", i + 1, program.Size, program.Data[i]);
        }
        return;
    }
    switch (opr[num_cur_string].value) {
    case (1):
        printf("Your ax: %ld\n", program.ax);
        break;
    case (2):
        printf("Your bx: %ld\n", program.bx);
        break;
    case (3):
        printf("Your cx: %ld\n", program.cx);
        break;
    case (4):
        printf("Your dx: %ld\n", program.dx);
        break;
    }
}

void process::do_printE ()
{
    if (opr[num_cur_string].ARG_flag == flag_NULL) {
        printf("Printing status of your programE:\n");
        for (size_t i = 0; i < programE.Size; ++i) {
            printf("[%ld/%ld]: %ld\n", i + 1, programE.Size, programE.Data[i]);
        }
        return;
    }
    switch (opr[num_cur_string].value) {
    case (1):
        printf("Your ax: %ld\n", program.ax);
        break;
    case (2):
        printf("Your bx: %ld\n", program.bx);
        break;
    case (3):
        printf("Your cx: %ld\n", program.cx);
        break;
    case (4):
        printf("Your dx: %ld\n", program.dx);
        break;
    }
}

void process::close_program ()
{
    program.destroy();
    fclose (file);
}

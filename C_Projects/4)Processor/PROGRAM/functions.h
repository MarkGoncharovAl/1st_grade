#include "tables.h"
struct Instruction {
        char CMD_flag;
        char CMD_code;
        char ARG_flag;
        int64_t value;
};

struct labels {
    char label_str[200];
    uint32_t num;
};

class compilate {
    public:
        uint32_t mistake_string;
        uint32_t num_strings;
        uint32_t num_cur_string;

        int64_t trash;
        char* str;

        labels label[200];
        labels jumping[200];
        char* current_string;
        char* compare;

        Instruction* commands;
        uint32_t current_lable;
        uint32_t current_jumping;

        FILE* file;
        FILE* read_code;
        char status;


        void read_file ();

        void read_strings ();
        void read_command ();

        int64_t read_int ();
        void read_label ();

        void read_two_value ();
        void read_value ();
        void check_label ();

        void skip_spaces ();
        void make_str ();
        int64_t read_int (char** String);

        void check_logic ();

        void write_code ();
        bool check_operation (char checking);
        int64_t find_label (uint32_t num);
        void close_programm ();
};


void compilate::read_file ()
{
    if (file == NULL) {
        status = PROBLEM;
        return;
    }

    fseek (file, 0, SEEK_END);
    int64_t Size = ftell (file);
    fseek (file, 0, 0);

    str = (char*) calloc (Size, sizeof (char));
    if (str == NULL)
        abort();

    fread (str, sizeof (char), Size, file);

    for (int64_t i = 0; i < Size; ++i) {
        if (str[i] == ';')
            (num_strings)++;
    }

    status = ORDINARY;
}

void compilate::read_strings ()
{
    current_string = strtok (str, ";");

    current_lable = 0;
    current_jumping = 0;
    compare = (char*) calloc (100, sizeof (char));
    num_cur_string = 0;

    while (num_cur_string < num_strings) {

        skip_spaces();
        read_command();

        if (status == PROBLEM) {
            mistake_string = num_cur_string + 1;
            return;
        }
        if (status == ORDINARY) {
            skip_spaces ();
            read_value ();
            if (status == PROBLEM) {
                mistake_string = num_cur_string + 1;
                return;
            }
        }
        if (status == NULL_OP) {
            commands[num_cur_string].ARG_flag = flag_NULL;
            commands[num_cur_string].value = 0;
        }
        if (status == COMPARING) {
            skip_spaces();
            read_two_value ();
            if (status == PROBLEM) {
                mistake_string = num_cur_string + 1;
                return;
            }
        }
        if (status == JUMP) {
            skip_spaces();
            check_label ();
            if (status == PROBLEM) {
                mistake_string = num_cur_string + 1;
                return;
            }
        }

        status = ORDINARY;
        num_cur_string++;
        current_string = strtok (NULL, ";");
    }
    return;
}

void compilate::skip_spaces ()
{
    if (current_string[0] == '\0')
        return;
    int length = 0;
    for (; current_string[length] == ' ' || current_string[length] == '\n' || current_string[length] == '\t'; ++length);
    current_string += length;
}

void compilate::make_str ()
{
    int i = 0;
    for (; current_string[i] != ' ' && current_string[i] != '\0' && i < 100; ++i)
        compare[i] = current_string[i];
    compare[i] = '\0';
    return;
}

int64_t compilate::read_int (char** String)
{
    int answer = 0;
    int num = 0;
    for (; *String[num] >= '0' && *String[num] <= '9'; ++num)
        answer = answer * 10 + (*String[num] - '0');

    *String += num;
    return answer;
}

void compilate::read_label ()
{
    compare += 1;

    int i = 0;
    for (; compare[i] != '\0'; ++i) {
        label[current_lable].label_str[i] = compare[i];
    }
    label[current_lable].label_str[i] = '\0';
}

void compilate::read_command ()
{
    if (!current_string) {
        status = PROBLEM;
        return;
    }

    make_str();
    commands[num_cur_string].CMD_flag = flag_CMD;

    if (!strcmp (compare, "push")) {
        commands[num_cur_string].CMD_code = CMD_push;
        current_string += 4;
        return;
    }
    if (!strcmp (compare, "pushE")) {
        commands[num_cur_string].CMD_code = CMD_pushE;
        current_string += 5;
        return;
    }
    if (!strcmp (compare, "pop")) {
        commands[num_cur_string].CMD_code = CMD_pop;
        current_string += 3;
        return;
    }
    if (!strcmp (compare, "popE")) {
        commands[num_cur_string].CMD_code = CMD_popE;
        current_string += 4;
        return;
    }
    if (!strcmp (compare, "add")) {
        commands[num_cur_string].CMD_code = CMD_add;
        current_string += 3;
        return;
    }
    if (!strcmp (compare, "addE")) {
        commands[num_cur_string].CMD_code = CMD_addE;
        current_string += 4;
        return;
    }
    if (!strcmp (compare, "mult")) {
        commands[num_cur_string].CMD_code = CMD_mult;
        current_string += 4;
        return;
    }
    if (!strcmp (compare, "multE")) {
        commands[num_cur_string].CMD_code = CMD_multE;
        current_string += 5;
        return;
    }
    if (!strcmp (compare, "sub")) {
        commands[num_cur_string].CMD_code = CMD_sub;
        current_string += 3;
        return;
    }
    if (!strcmp (compare, "subE")) {
        commands[num_cur_string].CMD_code = CMD_subE;
        current_string += 4;
        return;
    }
    if (!strcmp (compare, "div")) {
        commands[num_cur_string].CMD_code = CMD_div;
        current_string += 3;
        return;
    }
    if (!strcmp (compare, "divE")) {
        commands[num_cur_string].CMD_code = CMD_divE;
        current_string += 4;
        return;
    }
    if (!strcmp (compare, "scan")) {
        commands[num_cur_string].CMD_code = CMD_scan;
        current_string += 4;
        return;
    }
    if (!strcmp (compare, "print")) {
        commands[num_cur_string].CMD_code = CMD_print;
        current_string += 5;
        return;
    }
    if (!strcmp (compare, "printE")) {
        commands[num_cur_string].CMD_code = CMD_printE;
        current_string += 6;
        return;
    }
    if (!strcmp (compare, "cmp")) {
        commands[num_cur_string].CMD_code = CMD_cmp;
        current_string += 3;
        status = COMPARING;
        return;
    }
    if (!strcmp (compare, "exit")) {
        commands[num_cur_string].CMD_code = CMD_exit;
        current_string += 4;
        return;
    }
    if (!strcmp (compare, "jump")) {
        commands[num_cur_string].CMD_code = CMD_jump;
        commands[num_cur_string].ARG_flag = flag_NUM;
        current_string += 4;
        status = JUMP;
        return;
    }
    if (!strcmp (compare, "=")) {
        commands[num_cur_string].CMD_code = CMD_equal;
        commands[num_cur_string].ARG_flag = flag_NUM;
        current_string += 1;
        status = JUMP;
        return;
    }
    if (!strcmp (compare, "!=")) {
        commands[num_cur_string].CMD_code = CMD_nequal;
        commands[num_cur_string].ARG_flag = flag_NUM;
        current_string += 2;
        status = JUMP;
        return;
    }
    if (!strcmp (compare, ">")) {
        commands[num_cur_string].CMD_code = CMD_big;
        commands[num_cur_string].ARG_flag = flag_NUM;
        current_string += 1;
        status = JUMP;
        return;
    }
    if (!strcmp (compare, "<")) {
        commands[num_cur_string].CMD_code = CMD_small;
        commands[num_cur_string].ARG_flag = flag_NUM;
        current_string += 1;
        status = JUMP;
        return;
    }
    if (!strcmp (compare, ">=")) {
        commands[num_cur_string].CMD_code = CMD_bigeq;
        commands[num_cur_string].ARG_flag = flag_NUM;
        current_string += 2;
        status = JUMP;
        return;
    }
    if (!strcmp (compare, "<=")) {
        commands[num_cur_string].CMD_code = CMD_smalleq;
        commands[num_cur_string].ARG_flag = flag_NUM;
        current_string += 2;
        status = JUMP;
        return;
    }
    if (compare[0] == ':') {
        read_label ();
        commands[num_cur_string].CMD_code = CMD_label;
        commands[num_cur_string].ARG_flag = current_lable + '0';
        commands[num_cur_string].value = (int64_t) num_cur_string - current_lable + 1;

        label[current_lable].num = current_lable;
        status = LABEL;
        current_lable++;
        return;
    }

    if (current_string[0] == '\0') {
        status = NULL_OP;
        return;
    }

    status = PROBLEM;
    return;
}

void compilate::read_value ()
{
    if (current_string[0] == '\0') {
        commands[num_cur_string].ARG_flag = flag_NULL;
        commands[num_cur_string].value = 0;
        return;
    }

    if ((current_string[0] > '9' || current_string[0] < '0') && current_string[0] != '-') {

        make_str ();

        commands[num_cur_string].ARG_flag = flag_REG;
        current_string += 2;

        if (!strcmp (compare, "ax")) {
            commands[num_cur_string].value = 1;
            return;
        }
        if (!strcmp (compare, "bx")) {
            commands[num_cur_string].value = 2;
            return;
        }
        if (!strcmp (compare, "cx")) {
            commands[num_cur_string].value = 3;
            return;
        }
        if (!strcmp (compare, "dx")) {
            commands[num_cur_string].value = 4;
            return;
        }

        status = PROBLEM;
        return;
    }

    int sign = 1;
    if (current_string[0] == '-') {
        current_string++;
        sign = -1;
    }
    commands[num_cur_string].value = read_int(&current_string);


    if (current_string[0] == '\0' || current_string[0] == ' ') {
        commands[num_cur_string].ARG_flag = flag_NUM;
        status = ORDINARY;
        commands[num_cur_string].value *= sign;
        return;
    }

    status = PROBLEM;
    return;
}

void compilate::read_two_value ()
{
    trash = 0;
    while (current_string[trash] != ',' && current_string[trash] != '\0'  && current_string[trash] != ' ' && trash < 15) {
        compare[trash] = current_string[trash];
        trash++;
    }
    if (trash == 15 || current_string[trash] == '\0') {
        status = PROBLEM;
        return;
    }
    current_string = current_string + trash + 1;
    compare[trash] = '\0';


    bool isdigit = false;
    if (compare[0] >= '0' && compare[0] <= '9') {
        isdigit = true;
        commands[num_cur_string].value = read_int(&compare);
    }
    else {
        bool isfind = false;
        if (!strcmp (compare, "ax")) {
            commands[num_cur_string].ARG_flag = '1';
            isfind = true;
        }
        if (!strcmp (compare, "bx")) {
            commands[num_cur_string].ARG_flag = '2';
            isfind = true;
        }
        if (!strcmp (compare, "cx")) {
            commands[num_cur_string].ARG_flag = '3';
            isfind = true;
        }
        if (!strcmp (compare, "dx")) {
            commands[num_cur_string].ARG_flag = '4';
            isfind = true;
        }
        if (!isfind) {
            status = PROBLEM;
            return;
        }
    }


    trash = 0;
    skip_spaces();
    while (current_string[trash] != ' ' && current_string[trash] != '\0' && trash < 15) {
        compare[trash] = current_string[trash];
        trash++;
    }
    if (trash == 15) {
        status = PROBLEM;
        return;
    }
    compare[trash] = '\0';

    if (compare[0] >= '0' && compare[0] <= '9') {
        if (isdigit) {
            commands[num_cur_string].ARG_flag = flag_NUM;
            commands[num_cur_string].value = commands[num_cur_string].value - read_int (&compare);
        }
        else {
            commands[num_cur_string].value = read_int(&compare);
        }
    }
    else {
        if (!isdigit) {
            commands[num_cur_string].ARG_flag += 4;
            bool isfind = false;
            if (!strcmp (compare, "ax")) {
                commands[num_cur_string].value = 1;
                isfind = true;
            }
            if (!strcmp (compare, "bx")) {
                commands[num_cur_string].value = 2;
                isfind = true;
            }
            if (!strcmp (compare, "cx")) {
                commands[num_cur_string].value = 3;
                isfind = true;
            }
            if (!strcmp (compare, "dx")) {
                commands[num_cur_string].value = 4;
                isfind = true;
            }
            if (!isfind) {
                status = PROBLEM;
                return;
            }
        }
        else {
            bool isfind = false;
            if (!strcmp (compare, "ax")) {
                commands[num_cur_string].ARG_flag = '1';
                isfind = true;
            }
            if (!strcmp (compare, "bx")) {
                commands[num_cur_string].ARG_flag = '2';
                isfind = true;
            }
            if (!strcmp (compare, "cx")) {
                commands[num_cur_string].ARG_flag = '3';
                isfind = true;
            }
            if (!strcmp (compare, "dx")) {
                commands[num_cur_string].ARG_flag = '4';
                isfind = true;
            }
            if (!isfind) {
                status = PROBLEM;
                return;
            }
        }
    }
    status = ORDINARY;
    return;
}

void compilate::check_label ()
{
    make_str();

    strcpy (jumping[current_jumping].label_str, compare);
    jumping[current_jumping].num = num_cur_string;

    current_jumping++;
    return;
}

void compilate::check_logic ()
{
    for (uint32_t i = 0; i < num_strings; ++i) {

        if (commands[i].CMD_flag != flag_CMD) {
            mistake_string = i + 1;
            status = PROBLEM;
            return;
        }

        switch (commands[i].CMD_code) {
        case (CMD_push):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            if (commands[i].ARG_flag == flag_NUM)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_pushE):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            if (commands[i].ARG_flag == flag_NUM)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_pop):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            if (commands[i].ARG_flag == flag_NULL)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_popE):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            if (commands[i].ARG_flag == flag_NULL)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_add):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            if (commands[i].ARG_flag == flag_NULL)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_addE):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            if (commands[i].ARG_flag == flag_NULL)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_mult):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            if (commands[i].ARG_flag == flag_NULL)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_sub):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            if (commands[i].ARG_flag == flag_NULL)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_subE):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            if (commands[i].ARG_flag == flag_NULL)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_div):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            if (commands[i].ARG_flag == flag_NULL)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_divE):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            if (commands[i].ARG_flag == flag_NULL)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_scan):
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_print):
            if (commands[i].ARG_flag == flag_NULL)
                break;
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_printE):
            if (commands[i].ARG_flag == flag_NULL)
                break;
            if (commands[i].ARG_flag == flag_REG && (commands[i].value < 5 || commands[i].value > 0))
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_cmp):
            break;
        case (CMD_exit):
            if (commands[i].ARG_flag == flag_NULL)
                break;
            mistake_string = i + 1;
            status = PROBLEM;
            return;
            break;
        case (CMD_jump):
            break;
        case (CMD_equal):
            break;
        case (CMD_nequal):
            break;
        case (CMD_big):
            break;
        case (CMD_small):
            break;
        case (CMD_bigeq):
            break;
        case (CMD_smalleq):
            break;
        case (CMD_label):
            status = ORDINARY;
            break;
        }
    }
    return;
}

bool compilate::check_operation (char checking)
{
    switch (checking) {
    case (CMD_jump):
        return true;
    case (CMD_big):
        return true;
    case (CMD_equal):
        return true;
    case (CMD_nequal):
        return true;
    case (CMD_small):
        return true;
    case (CMD_bigeq):
        return true;
    case (CMD_smalleq):
        return true;
    }
    return false;
}

 int64_t compilate::find_label (uint32_t num)
 {
     for (uint32_t i = 0; i < current_lable; ++i) {
        if (!strcmp (label[i].label_str, jumping[num].label_str)) {
            return ((int64_t)i);
        }
     }
     return -1;
 }

void compilate::write_code ()
{
    uint32_t print_num = num_strings - current_lable;
    fwrite (&print_num, sizeof (uint32_t), 1, read_code);
    fwrite (&current_lable, sizeof (uint32_t), 1, read_code);

    for (uint32_t i = 0; i < num_strings; ++i) {
        if (commands[i].CMD_code == CMD_label) {
            fwrite (&commands[i].CMD_flag, sizeof (char), 1, read_code);
            fwrite (&commands[i].CMD_code, sizeof (char), 1, read_code);
            fwrite (&commands[i].ARG_flag, sizeof (char), 1, read_code);
            fwrite (&commands[i].value, sizeof (int64_t), 1, read_code);
        }
    }

    uint32_t num_jumping = 0;
    for (uint32_t i = 0; i < num_strings; ++i) {
        if (commands[i].CMD_code != CMD_label) {

            if (check_operation (commands[i].CMD_code)) {
                commands[i].value = find_label (num_jumping);
                num_jumping++;
                if (commands[i].value == -1) {
                    mistake_string = i + 1;
                    status = PROBLEM;
                    return;
                }
            }

            fwrite (&commands[i].CMD_flag, sizeof (char), 1, read_code);
            fwrite (&commands[i].CMD_code, sizeof (char), 1, read_code);
            fwrite (&commands[i].ARG_flag, sizeof (char), 1, read_code);
            fwrite (&commands[i].value, sizeof (int64_t), 1, read_code);
        }
    }
}

void compilate::close_programm ()
{
    fclose (file);
    fclose (read_code);
    free (str);
    free (commands);
    return;
}

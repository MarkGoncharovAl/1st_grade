const char CMD_push = 1 + '0';
const char CMD_pop = 2 + '0';
const char CMD_add = 3 + '0';
const char CMD_sub = 4 + '0';
const char CMD_mult = 5 + '0';
const char CMD_div = 6 + '0';
const char CMD_scan = 7 + '0';
const char CMD_print = 8 + '0';
const char CMD_exit = 9 + '0';
const char CMD_label = 10 + '0';
const char CMD_jump = 11 + '0';
const char CMD_cmp = 12 + '0';
const char CMD_equal = 13 + '0';
const char CMD_nequal = 14 + '0';
const char CMD_big = 15 + '0';
const char CMD_small = 16 + '0';
const char CMD_bigeq = 17 + '0';
const char CMD_smalleq = 18 + '0';
const char CMD_pushE = 19 + '0';
const char CMD_popE = 20 + '0';
const char CMD_addE = 21 + '0';
const char CMD_subE = 22 + '0';
const char CMD_multE = 23 + '0';
const char CMD_divE = 24 + '0';
const char CMD_printE = 25 + '0';


const char flag_CMD = 1 + 'a';
const char flag_NUM = 2 + 'a';
const char flag_REG = 3 + 'a';
const char flag_NULL = 4 + 'a';


const char REG_ax = 1 + 'A';
const char REG_bx = 2 + 'A';
const char REG_cx = 3 + 'A';
const char REG_dx = 4 + 'A';

const char PROBLEM = '0';
const char ORDINARY = '1';
const char NULL_OP = '2';
const char LABEL = '3';
const char COMPARING = '4';
const char JUMP = '5';

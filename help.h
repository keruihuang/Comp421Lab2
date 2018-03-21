#include <comp421/hardware.h>
#include <comp421/yalnix.h>
#include <comp421/loadinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


typedef struct pte pte;
extern int free_page_num;

typedef struct physical_address_linked_list {
    unsigned int physical_page_num;
    struct physical_address_linked_list *next;
} free_page;
extern free_page *physical_free_page;

unsigned long get_free_page(void);
extern int current_brk;
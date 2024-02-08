#include "hash.h"

hash_node* hash_table[TABLE_SIZE];

void init_table(void) {
    for (int i=0;i<TABLE_SIZE;i++) {
        hash_table[i] = NULL;
    }
}

int hash(char *entry) {
    int hash_code = 0;

    for (char ch=*entry;ch!='\0';ch=*entry++) {
        hash_code = ((int)ch + hash_code*37) % TABLE_SIZE;
    }

    return hash_code;
}

hash_node* insert_node(char *entry, int type) {
    hash_node* new_node;
    int code = hash(entry);

    // checks if is duplicate
    new_node = get_node(entry);
    if (new_node != NULL) {
        return new_node;
    }
    
    new_node = (hash_node*)malloc(sizeof(hash_node));
    new_node->type = type;
    new_node->value = (char*)calloc(strlen(entry) + 1, sizeof(char));
    strcpy(new_node->value, entry);

    // "magic lines" to insert a new node - credited to prof. Johann
    new_node->next_node = hash_table[code];
    hash_table[code] = new_node;
    return new_node;
}

hash_node* get_node(char *entry) {
    hash_node* node;
    int calculated_code = hash(entry);

    // iterates through the list, starting by the calculated hash code
    // returns if and only if found string is same as entry
    for (node=hash_table[calculated_code]; node!=NULL; node=node->next_node) {
        int found = strcmp(node->value, entry);
        if (found == 0) {
            return node;
        }        
    }

    return NULL;
}

hash_node* delete_table(void) {
    return NULL;
}

void print_table(void) {
    // iterates through whole table
    for (int i=0; i<TABLE_SIZE; i++) {
        // iterates through collisions
        for (hash_node* node=hash_table[i]; node != NULL; node=node->next_node) {
            printf("hash_table: %s value with %d type at %d index\n", node->value, node->type, i);
        }        
    }
} 

hash_node* create_temp(void) {
    static int serial = 0;
    char buffer[256] = "";

    sprintf(buffer,"teeeemp_var_temp%d", serial++);
    return insert_node(buffer, SYMBOL_VARIABLE);
}

hash_node* create_label(void) {
    static int serial = 0;
    char buffer[256] = "";

    sprintf(buffer,"mylabeeel_mylabel_my%d", serial++);
    return insert_node(buffer, SYMBOL_LABEL);
}

void printAsm(FILE *fout) {
    int i;
    hash_node *node;
    fprintf(fout, 
                "## DATA SECTION\n"
    );

    for(i=0;i<TABLE_SIZE;i++) {
        for(node=hash_table[i]; node; node = node->next_node) {
            fprintf(fout, "_%s:\t.long\t0\n", node->value);
        }
    }
}
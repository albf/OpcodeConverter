/*
 * Copyright 2014 Alexandre Luiz Brisighello Filho <albf.unicamp@gmail.com>
 *
 *
 */

#ifndef JOURNAL_H
#define JOURNAL_H

//#include <semaphore.h>
//#include <time.h>
//#include <pthread.h>

struct journal {
    // Entries part.
    struct j_entry ** entries;
    int * size;
    int * capacity;
    int num_threads;
    //struct timeval zero;
    char * id_type;
    int parallel;
    int time;

    // Id part.
    //pthread_mutex_t id_lock;
    int c_id;
};

struct j_entry {
    char * action;
    //struct timeval start;
    //struct timeval end;
    int size;
};

// Diary manipulation functions.
void JOURNAL_init(struct journal *dia, int num_threads, int parallel, int time);
int JOURNAL_get_id(struct journal *dia, char my_type);
struct j_entry * JOURNAL_new_entry(struct journal *dia, int id);
void JOURNAL_insert_text(struct j_entry * entry, char * text);
void JOURNAL_remove_entry(struct journal *dia, int id);
void JOURNAL_free(struct journal *dia);

// Info
char * JOURNAL_generate_info(struct journal *dia, char * filename);

// Auxiliary
//int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1);

#endif	/* JOURNAL_H */


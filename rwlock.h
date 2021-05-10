#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct read_write_lock
{
    int readers; //readers currently reading
    int writers; //writers waiting
    int is_writing; //whether a something is being written
    pthread_cond_t c; //writing over 
    pthread_mutex_t lock; //general lock
    pthread_mutex_t write_lock; //used in read
};

void InitalizeReadWriteLock(struct read_write_lock * rw);
void ReaderLock(struct read_write_lock * rw);
void ReaderUnlock(struct read_write_lock * rw);
void WriterLock(struct read_write_lock * rw);
void WriterUnlock(struct read_write_lock * rw);

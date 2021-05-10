// algorithm taken from: https://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock

#include "rwlock.h"

void InitalizeReadWriteLock(struct read_write_lock * rw)
{
	rw->readers = 0; 
    rw->writers = 0; 
    rw->is_writing = 0;
}

void ReaderLock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->lock);
	while (rw->writers > 0 || rw->is_writing == 1)
		pthread_cond_wait(&rw->c,&rw->lock);
	rw->readers++;
	pthread_mutex_unlock(&rw->lock);
}

void ReaderUnlock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->lock);
	rw->readers--;
	if (rw->readers==0)
		pthread_cond_broadcast(&rw->c);
	pthread_mutex_unlock(&rw->lock);
}

void WriterLock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->lock);
	rw->writers++;
	while (rw->readers > 0 || rw->is_writing==1)
		pthread_cond_wait(&rw->c,&rw->lock);
	rw->is_writing=1;
	pthread_mutex_unlock(&rw->lock);
}

void WriterUnlock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->lock);
	rw->writers--;
	rw->is_writing=0;
	pthread_cond_broadcast(&rw->c);
	pthread_mutex_unlock(&rw->lock);
}

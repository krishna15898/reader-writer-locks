// reference: https://pages.cs.wisc.edu/~remzi/OSTEP/threads-locks.pdf

#include "rwlock.h"

void InitalizeReadWriteLock(struct read_write_lock* rw)
{
	rw->readers = 0;
}

void ReaderLock(struct read_write_lock* rw)
{
	pthread_mutex_lock(&rw->lock);
	rw->readers++;
	if (rw->readers == 1) // first reader gets writelock
		pthread_mutex_lock(&rw->write_lock);
	pthread_mutex_unlock(&rw->lock);
}

void ReaderUnlock(struct read_write_lock* rw)
{
	pthread_mutex_lock(&rw->lock);
	rw->readers--;
	if (rw->readers == 0) // last reader lets it go
		pthread_mutex_unlock(&rw->write_lock);
	pthread_mutex_unlock(&rw->lock);
}

void WriterLock(struct read_write_lock* rw)
{
	pthread_mutex_lock(&rw->write_lock);
}

void WriterUnlock(struct read_write_lock* rw)
{
	pthread_mutex_unlock(&rw->write_lock);

}

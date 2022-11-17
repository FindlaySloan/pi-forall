// https://stackoverflow.com/questions/4803900/object-oriented-semaphore-usage-in-c
// Just a c++ wrapper for the semaphore.h from c
#include <semaphore.h>
#include <errno.h>

#ifndef SRC_SEM_HPP
#define SRC_SEM_HPP

class Semaphore {
    sem_t sem;

  public:
    Semaphore(int shared, unsigned value) { 
        sem_init(&sem, shared, value); 
    }

    ~Semaphore() {
         sem_destroy(&sem);
    }

    int wait() {
        int r;
        do {
            r = sem_wait(&sem);
        } while (r == -1 && errno == EINTR);
        return r;
    }
    
    int try_wait() {
        return sem_trywait(&sem);
    }

    int post() {
        return sem_post(&sem);
    }
};

#endif
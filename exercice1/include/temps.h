#ifndef __TEMPS_H
#define __TEMPS_H

static const int CONTINUER = 0;
static const int FIN_DES_TEMPS = 1;

/* 1 : fin, les producteurs enverront -1. */
typedef struct temps
{
    int _fin_des_temps;
    sem_t _semaphore_des_temps;
} findestemps;

static inline void init_fin_des_temps(findestemps * t)
{
    sem_init(&t->_semaphore_des_temps, 0, 1);
    t->_fin_des_temps = CONTINUER;
}

static inline int est_ce_la_fin_des_temps(findestemps * t)
{
    sem_wait(&t->_semaphore_des_temps);
    int temps = t->_fin_des_temps;
    sem_post(&t->_semaphore_des_temps);
    return temps == FIN_DES_TEMPS;
}

static inline void cest_la_fin_des_temps(findestemps * t)
{
    sem_wait(&t->_semaphore_des_temps);
    t->_fin_des_temps = FIN_DES_TEMPS;
    sem_post(&t->_semaphore_des_temps);
}

#endif /* __TEMPS_H */

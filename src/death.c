/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** death
*/

#include "../include/lemipc.h"

void death_loop(t_proc *pSeg, t_proc *proc, t_proc *opponent)
{
	int j = 0;

	while (pSeg != NULL && pSeg[j].id != 0 && opponent->alive == 1) {
		if (pSeg[j].id != proc->id && pSeg[j].id != opponent->id &&
			pSeg[j].alive == 1 && pSeg[j].team == proc->team &&
			(pSeg[j].pos_x - opponent->pos_x <= 1) &&
			(pSeg[j].pos_x - opponent->pos_x >= -1) &&
			(pSeg[j].pos_y - opponent->pos_y <= 1) &&
			(pSeg[j].pos_y - opponent->pos_y >= -1)) {
			opponent->alive = 0;
			return;
			}
		j++;
	}
}

void check_death(t_proc *proc, key_t key)
{
	int i = 0;
	int msize = sizeof(t_proc) * SIZE_X * SIZE_Y;
	int shmid = shmget(key, msize, 0666);
	t_proc *pSeg = (t_proc *)shmat(shmid, NULL, 0);
	t_proc *opponent = NULL;

	while (pSeg != NULL && pSeg[i].id != 0) {
		if (pSeg[i].id != proc->id && pSeg[i].alive == 1 &&
			pSeg[i].team != proc->team &&
			(pSeg[i].pos_x - proc->pos_x <= 1) &&
			(pSeg[i].pos_x - proc->pos_x >= -1) &&
			(pSeg[i].pos_y - proc->pos_y <= 1) &&
			(pSeg[i].pos_y - proc->pos_y >= -1)) {
			opponent = &pSeg[i];
			death_loop(pSeg, proc, opponent);
		}
		i++;
	}
}
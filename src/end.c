/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** end
*/

#include "../include/lemipc.h"

int lastOnline(t_proc *pSeg, int pos)
{
	int i = 0;

	while (pSeg[i].id != 0) {
		if (i != pos && pSeg[i].left == false)
			return (false);
		i++;
	}
	return (true);
}

void leave(t_proc *pSeg, int pos, int shmid)
{
	pSeg[pos].left = true;
	if (pos == 0)
		print_map(pSeg);
	if (lastOnline(pSeg, pos) == true) {
		shmctl(shmid, IPC_RMID, NULL);
	}
	shmdt(pSeg);
	exit(0);
}

bool gameOver(t_proc *pSeg, int *times, int shmid)
{
	int team;
	int i = 0;

	usleep(500000);
	pSeg = (t_proc *)shmat(shmid, NULL, 0);
	*times += 1;
	if (*times < 30)
		return (false);
	if (pSeg[0].id == 0)
		return (false);
	team = -1;
	while (pSeg[i].id != 0) {
		if (pSeg[i].alive == 1 && team == -1)
			team = pSeg[i].team;
		else if (pSeg[i].alive == 1 && pSeg[i].team != team)
			return (false);
		i++;
	}
	return (true);
}
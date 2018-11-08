/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** map
*/

#include "../include/lemipc.h"

int isFull(int x, int y, t_proc *pSeg)
{
	int i = 0;

	while (pSeg != NULL && pSeg[i].id != 0) {
		if (pSeg[i].alive == 1 && pSeg[i].pos_x == x
			&& pSeg[i].pos_y == y)
			return (i);
		i++;
	}
	return (-1);
}

int isEmpty(int x, int y, key_t key)
{
	int i = 0;
	int msize = sizeof(t_proc) * SIZE_X * SIZE_Y;
	int shmid = shmget(key, msize, 0666);
	t_proc *pSeg = (t_proc *)shmat(shmid, NULL, 0);

	while (pSeg != NULL && pSeg[i].id != 0) {
		if (pSeg[i].alive == 1 && pSeg[i].pos_x == x
			&& pSeg[i].pos_y == y)
			return (false);
		i++;
	}
	return (true);
}

void	print_map(t_proc *pSeg)
{
	int x = 0;
	int y = 0;
	int ret;

	for (int i = 0; i < 30; i++)
		printf("_");
	printf("\n");
	while (y < SIZE_Y) {
		while (x < SIZE_X) {
			ret = isFull(x, y, pSeg);
			if (ret != -1)
				printf("%d ", pSeg[ret].team);
			else
				printf(". ");
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}
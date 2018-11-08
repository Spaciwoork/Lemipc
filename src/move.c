/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** move
*/

#include "../include/lemipc.h"

int find_move_s(t_proc *pSeg, int j, int i)
{
	if (pSeg[j].pos_y > pSeg[i].pos_y)
		return (TOP);
	else if (pSeg[j].pos_y < pSeg[i].pos_y)
		return (BOTTOM);
	else
		return (rand() % 4);
}

int find_move(t_proc *pSeg, int j)
{
	int i = 0;

	i = j - 1;
	while (pSeg[i].id != 0 && pSeg[i + 1].id != 0)
		i++;
	while (i > 0 && pSeg[i].team == pSeg[j].team)
		i--;
	if (i == 0 && pSeg[j].team == pSeg[0].team)
		return (rand() % 4);
	if (pSeg[j].pos_x > pSeg[i].pos_x)
		return (LEFT);
	else if (pSeg[j].pos_x < pSeg[i].pos_x)
		return (RIGHT);
	else
		return (find_move_s(pSeg, j, i));
}

int find_move_first(t_proc *pSeg)
{
	int end = 0;

	srand(time(NULL) + getpid());
	while (pSeg[end].id != 0)
		end++;
	end -= 1;
	while (end > 0 && pSeg[end].team == pSeg[0].team)
		end--;
	if (end == -1 || end == 0)
		return (rand() % 4);
	if (pSeg[0].id != 0 && pSeg[end].id != pSeg[0].id)
	{
		if (pSeg[0].pos_x > pSeg[end].pos_x)
			return (LEFT);
		else if (pSeg[0].pos_x < pSeg[end].pos_x)
			return (RIGHT);
		else
			return (find_move_s(pSeg, 0, end));
	}
}

void move(t_proc *proc, int way, key_t key)
{
	int a = proc->alive;
	int x = proc->pos_x;
	int y = proc->pos_y;

	if (way == TOP && a == 1 && y > 0 && isEmpty(x, y - 1, key) == true)
		proc->pos_y -= 1;
	else if (way == RIGHT && a == 1 && x < 29
		&& isEmpty(x + 1, y, key) == true)
		proc->pos_x += 1;
	else if (way == BOTTOM && a == 1 && y < 29
		&& isEmpty(x, y + 1, key) == true)
		proc->pos_y += 1;
	else if (way == LEFT && a == 1 && x > 0
		&& isEmpty(x - 1, y, key) == true)
		proc->pos_x -= 1;
	check_death(proc, key);
}
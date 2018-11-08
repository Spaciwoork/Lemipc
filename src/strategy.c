/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** strategy
*/

#include "../include/lemipc.h"

int check_inertia(t_proc *proc, int way, key_t key)
{
	int ret = 0;

	srand(time(NULL) + getpid());
	if ((proc->i[0] == proc->i[1] && proc->i[1] == proc->i[2]) ||
		(proc->i[0] == proc->i[2] && proc->i[1] == proc->i[3]))
		ret = rand() % 4;
	else
		ret = way;
	proc->i[proc->it] = ret;
	proc->it++;
	if (proc->it == 4)
		proc->it = 0;
	move(proc, ret, key);
	return (ret);
}
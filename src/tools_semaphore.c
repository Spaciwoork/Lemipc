/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** tools_semaphore
*/


#include "../include/lemipc.h"

void init_semaphore(t_proc *proc, key_t key)
{
	proc->semId = semget(key, 1, IPC_CREAT | SHM_R | SHM_W);
	semctl(proc->semId, 0, SETVAL, 1);
}

void lock_semaphore(t_proc *proc)
{
	int ret;
	struct sembuf oper;

	oper.sem_num = 0;
	oper.sem_flg = SEM_UNDO;
	oper.sem_op = -1;
	ret = semop(proc->semId, &oper, 1);
	if (ret == -1)
		printf("error locking semaphore\n");
}

void unlock_semaphore(t_proc *proc)
{
	int ret;
	struct sembuf oper;

	oper.sem_num = 0;
	oper.sem_flg = SEM_UNDO;
	oper.sem_op = 1;
	ret = semop(proc->semId, &oper, 1);
	if (ret == -1)
		printf("error unlocking semaphore\n");
}

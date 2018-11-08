/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** game
*/

#include "../include/process.h"

t_data *init_data(int opt, key_t key)
{
	t_data *data = malloc(sizeof(t_data));

	if (data == NULL)
		exit(84);
	data->i = opt;
	data->j = 0;
	data->way = 0;
	if (opt == 0)
		data->msgq = msgget(key, 0660);
	else
		data->msgq = msgget(key, IPC_CREAT | 0660);
	return (data);
}

void secondary_p(int shmid, t_proc *proc, key_t key)
{
	t_proc *pSeg = (t_proc *)shmat(shmid, NULL, 0);
	t_data *data = init_data(0, key);

	while (pSeg[data->i].id != 0)
		data->i++;
	proc->id = data->i + 1;
	memcpy(&pSeg[data->i], proc, sizeof(t_proc));
	while (gameOver(pSeg, &data->j, shmid) == false) {
		lock_semaphore(proc);
		if (pSeg[data->i].alive == 0)
			leave(pSeg, data->i, shmid);
		data->way = find_move(pSeg, data->i);
		check_inertia(&pSeg[data->i], data->way, key);
		msgsnd(data->msgq, "Go", 2, 0);
		msgrcv(data->msgq, NULL, 2, 0, 0);
		unlock_semaphore(proc);
	}
	leave(pSeg, data->i, shmid);
}

void first_p(key_t key, t_proc *proc)
{
	t_data *data = init_data(sizeof(t_proc) * SIZE_X * SIZE_Y, key);
	int shmid = shmget(key, data->i, IPC_CREAT | 0666);
	t_proc *pSeg = (t_proc *)shmat(shmid, NULL, 0);

	if (shmid == -1)
		exit(84);
	proc->id = 1;
	memcpy(pSeg, proc, sizeof(t_proc));
	while (gameOver(pSeg, &data->j, shmid) == false) {
		lock_semaphore(proc);
		if (pSeg[0].alive == 1) {
			data->way = find_move_first(pSeg);
			check_inertia(&pSeg[0], data->way, key);
		}
		msgsnd(data->msgq, "Go", 2, 0);
		msgrcv(data->msgq, NULL, 2, 0, 0);
		print_map(pSeg);
		unlock_semaphore(proc);
	}
	leave(pSeg, 0, shmid);
}

t_proc *create_p(int team, key_t key)
{
	t_proc *proc = malloc(sizeof(t_proc));
	srand(time(NULL) + getpid());
	int rnd;

	proc->id = 0;
	proc->team = team;
	proc->alive = 1;
	rnd = rand() % 30;
	proc->pos_x = rnd;
	rnd *= 2;
	if (rnd >= 30)
		rnd = (rnd - 7) / 4 + 3;
	proc->pos_y = rnd;
	proc->left = false;
	for (int i = 0; i < 4; i++)
		proc->i[i] = 0;
	proc->it = 0;
	init_semaphore(proc, key);
	return (proc);
}

void start_game(char *path, int team)
{
	key_t key = ftok(path, 0);
	t_proc *proc = NULL;

	if (key == -1)
		exit(84);
	proc = create_p(team, key);
	int shmid = shmget(key, 1, 0666);
	if (shmid == -1)
		first_p(key, proc);
	else
		secondary_p(shmid, proc, key);
}
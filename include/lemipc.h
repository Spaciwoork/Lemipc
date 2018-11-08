/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** lemipc
*/

#ifndef PSU_LEMPIC_2017_LEMIPC_H
#define PSU_LEMPIC_2017_LEMIPC_H

#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <sys/sem.h>

#define SIZE_X 30
#define SIZE_Y 30
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

typedef struct s_proc
{
	int id;
	int team;
	int alive;
	int pos_x;
	int pos_y;
	int semId;
	bool left;
	int i[4];
	int it;
} t_proc;

int	parser_dir(const char *);
void	print_help(void);
void	start_game(char *, int);
bool	gameOver(t_proc *, int *, int);
void	move(t_proc *, int, key_t);
int	isEmpty(int, int, key_t);
void	print_map(t_proc *);
void	leave(t_proc *, int, int);
int 	find_move(t_proc *, int);
void 	init_semaphore(t_proc *, key_t);
void 	lock_semaphore(t_proc *);
void 	unlock_semaphore(t_proc *);
int	find_move_first(t_proc *);
int	check_inertia(t_proc *, int, key_t);
void	check_death(t_proc *, key_t);

#endif /* PSU_LEMPIC_2017_LEMIPC_H */

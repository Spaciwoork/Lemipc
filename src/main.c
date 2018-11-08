/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** main
*/

#include "../include/lemipc.h"

void	print_help(void)
{
	printf("USAGE\n"
		"\t./lemipc PATH TEAM_NUMBER\n"
		"DESCRIPTION\n"
		"\tPATH\t\tpath you'll give to ftok\n"
		"\tTEAM_NUMBER\tteam number of the current "
		"champion (greater than 0)\n");
}

int	main(int ac, char **av)
{
	char *path;
	int team;

	if (ac != 3)
		print_help();
	else {
		for (int i = 0; i < strlen(av[2]); i++) {
			if (isdigit(av[2][i]) == 0) {
				print_help();
				return (84);
			}
		}
		path = av[1];
		team = atoi(av[2]);
		start_game(path, team);
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:47:57 by chiarakappe       #+#    #+#             */
/*   Updated: 2025/03/19 19:49:37 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"



static void	_init_files(char **av, t_data *data)
{
	data->fd_inp = open(av[1], O_RDONLY);
	if (data->fd_inp < 0)
		error_handler("cant open input file", errno);
	data->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out < 0)
		error_handler("error with output file", errno);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		fd[2];

	if (ac != 5)
		error_handler("wrong parameters", 3);
	_init_files(av, &data);
	_init_data(av, &data, env);
	if (pipe(fd) == -1)
		error_handler("pipe failed", errno);
	pipex(&data, env, fd);
	freedata(&data);
}
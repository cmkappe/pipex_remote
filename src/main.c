/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:47:57 by chiarakappe       #+#    #+#             */
/*   Updated: 2025/04/24 14:52:34 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_exec(t_data *data, char **cmd, char **dirs)
{
	char	*path;
	char	*tmp;

	if (!cmd || !cmd[0])
		error_handler(data, "Invalid command", errno, 1);
	while (*dirs)
	{
		tmp = ft_strjoin(*dirs, "/");
		if (!tmp)
			error_handler(data, "Memory allocation failed", errno, 1);
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (!path)
			error_handler(data, "Memory allocation failed", errno, 1);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		dirs++;
	}
	error_handler(data, "command not found", errno, 1);
	return (NULL);
}

static char	*_get_path(char **envp)
{
	char	*path;

	while (*envp)
	{
		path = ft_strnstr(*envp, "PATH=", 5);
		if (path != NULL)
			break ;
		envp++;
	}
	return (path + 5);
}

static void	_init_files(char **av, t_data *data)
{
	data->fd_inp = open(av[1], O_RDONLY);
	if (data->fd_inp < 0)
		error_handler(data, "cant open input file", errno, 0);
	data->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out < 0)
		error_handler(data, "error with output file", errno, 0);
}

static void	_init_data(char **av, t_data *data, char **env)
{
	char	**all_env_paths;

	data->cmd1 = ft_split(av[2], ' ');
	data->cmd2 = ft_split(av[3], ' ');
	data->env_path = _get_path(env);
	all_env_paths = ft_split(data->env_path, ':');
	data->cmd1_path = find_exec(data, data->cmd1, all_env_paths);
	data->cmd2_path = find_exec(data, data->cmd2, all_env_paths);
	free2d(all_env_paths);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		fd[2];

	if (ac != 5)
		error_handler(&data, "wrong parameters", 3, 0);
	_init_files(av, &data);
	_init_data(av, &data, env);
	if (pipe(fd) == -1)
		error_handler(&data, "pipe failed", errno, 1);
	pipex(&data, env, fd);
	freedata(&data, 2);
}

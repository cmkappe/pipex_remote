/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:47:57 by chiarakappe       #+#    #+#             */
/*   Updated: 2025/04/17 15:50:49 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_exec(char **cmd, char **dirs)
{
	char	*path;
	char	*tmp;

	if (!cmd || !cmd[0])
		error_handler("Invalid command", errno);
	while (*dirs)
	{
		tmp = ft_strjoin(*dirs, "/");
		if (!tmp)
			error_handler("Memory allocation failed", errno);
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (!path)
			error_handler("Memory allocation failed", errno);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		dirs++;
	}
	error_handler("command not found", errno);
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
		error_handler("cant open input file", errno);
	data->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out < 0)
		error_handler("error with output file", errno);
}

static void	_init_data(char **av, t_data *data, char **env)
{
	char	**all_env_paths;

	data->cmd1 = ft_split(av[2], ' ');
	data->cmd2 = ft_split(av[3], ' ');
	data->env_path = _get_path(env);
	all_env_paths = ft_split(data->env_path, ':');
	data->cmd1_path = find_exec(data->cmd1, all_env_paths);
	data->cmd2_path = find_exec(data->cmd2, all_env_paths);
	free2d(all_env_paths);
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

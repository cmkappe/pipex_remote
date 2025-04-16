/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:25:20 by ckappe            #+#    #+#             */
/*   Updated: 2025/04/16 15:24:02 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	_close_fds(t_data *data, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	close(data->fd_inp);
	close(data->fd_out);
}

/*
The pipe is used to connect the output of the first command to the 
input of the second command:
In the first child process:
	fd[1] (write end) is redirected to STDOUT_FILENO (standard output).
In the second child process:
	fd[0] (read end) is redirected to STDIN_FILENO (standard input).
After setting up the redirection, the parent process closes both ends 
of the pipe to avoid interference.
 */

 void	pipex(t_data *data, char **env, int *fd)
{
	data->pid1 = fork();
	if (data->pid1 < 0)
		error_handler("fork failed", errno);
	if (data->pid1 == 0)
	{
		dup2(data->fd_inp, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		_closefds(data, fd);
		execve(data->cmd1_path, data->cmd1, env);
	}
	data->pid2 = fork();
	if (data->pid2 < 0)
	 error_handler("fork failed", errno);
	if (data->pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		_closefds(data, fd);
		execve(data->cmd2_path, data->cmd2, env);
	}
	_closefds(data, fd);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
}


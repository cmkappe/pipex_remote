/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:12:08 by ckappe            #+#    #+#             */
/*   Updated: 2025/04/16 18:15:34 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_handler(char *error, int exit_flag)
{
	perror(error);
	exit(exit_flag);
}

void	free2d(char **a)
{
	while (*a)
	{
		free(*a);
		a++;
	}
	free(a);
}


void	freedata(t_data *data)
{
	free2d(data->cmd1);
	free2d(data->cmd2);
	free(data->cmd1_path);
	free(data->cmd2_path);
}

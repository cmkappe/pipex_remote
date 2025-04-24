/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:12:08 by ckappe            #+#    #+#             */
/*   Updated: 2025/04/24 14:53:12 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_handler(t_data *data, char *error, int exit_flag, int num)
{
	perror(error);
	if (num != 0)
		freedata(data, num);
	exit(exit_flag);
}

void	free2d(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}

void	freedata(t_data *data, int num)
{
	if (num != 0)
	{
		free2d(data->cmd1);
		free2d(data->cmd2);
	}
	if (num == 2)
	{
		free(data->cmd1_path);
		free(data->cmd2_path);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:59:13 by ckappe            #+#    #+#             */
/*   Updated: 2025/04/16 15:00:37 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_exec(char **cmd, char **dirs)
{
	char	*path;
	char	*tmp;

	while (*dirs)
	{
		tmp = ft_strjoin(*dirs, "/");
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		dirs++;
	}
	error_handler("command not found", errno);
	return (NULL);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:46:03 by ckappe            #+#    #+#             */
/*   Updated: 2025/04/16 18:55:42 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>

typedef struct s_data
{
	int		fd_inp;
	int		fd_out;
	char	**cmd1;
	char	**cmd2;
	char	*env_path;
	char	*cmd1_path;
	char	*cmd2_path;
	int		pid1;
	int		pid2;
}			t_data;

//--------------------------------Source-----------------------------------//
void	pipex(t_data *data, char **env, int *fd);

void	error_handler(char *error, int exit_flag);
void	free2d(char **a);
void	freedata(t_data *data);

//--------------------------------Utils-----------------------------------//
char	*find_exec(char **cmd, char **dirs);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlen(const char *s);
char	**ft_split(const char *s, char c);
void	*ft_calloc(size_t count, size_t size);

#endif
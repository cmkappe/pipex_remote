/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:59:13 by ckappe            #+#    #+#             */
/*   Updated: 2025/04/16 18:56:48 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	_ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	arr = (void *)malloc(count * size);
	if (!arr)
		return (NULL);
	_ft_bzero(arr, count * size);
	return ((void *)arr);
}

size_t	ft_strlen(const char *s)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	return (str);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hstck;
	char	*ndl;
	size_t	i;
	size_t	j;

	hstck = (char *)haystack;
	ndl = (char *)needle;
	i = 0;
	if (ndl[i] == '\0' || ndl == NULL)
		return (hstck);
	while (hstck[i] && i < len)
	{
		j = 0;
		while (hstck[i + j] == ndl[j] && i + j < len)
		{
			if (ndl[j + 1] == '\0')
				return (hstck + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

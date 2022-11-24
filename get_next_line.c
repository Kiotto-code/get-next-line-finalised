/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:23:47 by yichan            #+#    #+#             */
/*   Updated: 2022/08/22 22:20:29 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	modlen;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	modlen = ft_strlen(s + start);
	if (modlen < len)
		len = modlen;
	substr = malloc(sizeof(char) * len +1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*readline(int fd, char *str)
{
	char	*buff;
	int		r_ret;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	r_ret = 1;
	while (!ft_strchr(str, '\n') && r_ret != 0)
	{
		r_ret = read(fd, buff, BUFFER_SIZE);
		if (r_ret == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[r_ret] = '\0';
		str = joinfree(str, buff);
	}
	free(buff);
	return (str);
}

char	*currentline(char **string)
{
	int		c_len;
	char	*tmp;
	char	*ret;

	c_len = 0;
	if (!((*string)[c_len]))
	{
		free(*string);
		*string = NULL;
		return (NULL);
	}
	while ((*string)[c_len] && (*string)[c_len] != '\n')
		c_len++;
	if (!(*string)[c_len])
	{
		ret = *string;
		*string = NULL;
		return (ret);
	}
	ret = ft_substr(*string, 0, c_len + 1);
	tmp = ft_strdup((*string) + c_len + 1);
	free(*string);
	*string = tmp;
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*ret;

	if (BUFFER_SIZE <= 0 || fd > 1024 || fd < 0)
		return (NULL);
	str = readline(fd, str);
	if (!str)
		return (NULL);
	ret = currentline (&str);
	return (ret);
}

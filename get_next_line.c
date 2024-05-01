/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmachuca <fmachuca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:17:18 by fmachuca          #+#    #+#             */
/*   Updated: 2024/05/01 20:50:43 by fmachuca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>
#include <errno.h>
#include <stdarg.h>
#include <wchar.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "get_next_line.h"

char *get_next_line(int fd)
{
	static	t_list	*list = NULL;
	char	*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	ft_new_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = ft_get_line(list);
	ft_polish_list(&list);
	return (next_line);
}

void	ft_new_list(t_list **list, int fd)
{
	int		char_read;
	char	*buffer;

	while (!ft_found_new_line(*list))//gets out of the loop if a new line is found (1)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);//integer # of characters read
		if (!char_read)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] = '\0';
		ft_append(list, buffer);
	}
}

int	ft_found_new_line(t_list *list)
{
	int i;

	if (NULL == list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buff[i] && i < BUFFER_SIZE)
		{
			if (list->str_buff[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

void	ft_append(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (NULL == new_node)
		return ;
	if (NULL == last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buff = buffer;
	new_node->next = NULL;
}

t_list	*ft_find_last_node(t_list *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

char *ft_get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (NULL == list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

int	len_to_new_line(t_list *list)
{
	int	i;
	int	len;

	if (NULL == list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buff[i])
		{
			if (list->str_buff[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;			
		}
		list = list->next;
	}
	return (len);
}

void	copy_str(t_list *list, char *str)
{
	int	i;
	int	j;

	if (NULL == list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->str_buff[i])
		{
			if (list->str_buff[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->str_buff[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

int main()
{
	int		fd;
	char	buf[256];
	int		chars_read;

	fd = open("file.txt", O_RDONLY);
	while ((chars_read = read(fd, buf, 5)))
	{
		buf[chars_read] = '\0';
		printf("buffer -> %s\n", buf);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-mont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 09:19:42 by yde-mont          #+#    #+#             */
/*   Updated: 2020/12/09 09:20:15 by yde-mont         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "get_next_line_bonus.h"

int		clear(t_file *sfile, int status)
{
	t_segment *seg;
	t_segment *nseg;

	seg = sfile->fseg;
	while (seg && (ERROR == status || CONTINUE == status))
	{
		status = (ERROR == status) ? ERROR : seg->status;
		nseg = seg->next;
		free(seg->str);
		free(seg);
		seg = nseg;
		sfile->fseg = seg;
	}
	if (ERROR == status)
		return (ERROR);
	if (!seg)
		return (0);
	sfile->status = seg->status;
	return (1);
}

int		indexof(char *str, char c, int start)
{
	int i;

	i = 0;
	while (start--)
		str++;
	if (!str)
		return (-1);
	while (*str)
	{
		if (c == *str)
			return (i);
		i++;
		str++;
	}
	return (-1);
}

int		mod_strlen(char *str)
{
	int i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (*str++)
	{
		i++;
	}
	return (i);
}

char	*mod_substr(char *s, int start, int len)
{
	char	*pt;
	int		i;

	i = 0;
	if (!(pt = malloc(len * sizeof(char) + 1)))
		return (NULL);
	while (start--)
		s++;
	while (len-- && *s)
		pt[i++] = *s++;
	pt[i] = 0;
	return (pt);
}

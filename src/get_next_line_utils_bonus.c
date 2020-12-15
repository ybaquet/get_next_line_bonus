/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-mont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 09:19:42 by yde-mont          #+#    #+#             */
/*   Updated: 2020/12/12 09:53:20 by yde-mont         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "get_next_line_bonus.h"

void	clear_file(t_file **firstfile_pt)
{
	t_file	*wfile;
	t_file	*pfile;
	t_file	*current;

	wfile = *firstfile_pt;
	current = wfile->current;
	pfile = NULL;
	while (wfile)
	{
		if (wfile == (*firstfile_pt)->current)
		{
			if (NULL != pfile)
				pfile->next = wfile->next;
			else
				*firstfile_pt = wfile->next;
		}
		pfile = wfile;
		wfile = wfile->next;
	}
	free(current);
}

int		clear(t_file **firstfile_pt, int status)
{
	t_segment *seg;
	t_segment *nseg;

	seg = (*firstfile_pt)->current->fseg;
	while (seg && (ERROR == status || CONTINUE == status))
	{
		status = (ERROR == status) ? ERROR : seg->status;
		nseg = seg->next;
		free(seg->str);
		free(seg);
		seg = nseg;
		(*firstfile_pt)->current->fseg = seg;
	}
	if (ERROR == status || !seg)
	{
		clear_file(firstfile_pt);
		return (ERROR == status) ? ERROR : END;
	}
	(*firstfile_pt)->current->status = seg->status;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-mont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:58:05 by yde-mont          #+#    #+#             */
/*   Updated: 2020/12/08 18:02:47 by yde-mont         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#include <stdlib.h>
#include <unistd.h>

int		process_buffer(t_file *sfile, char *str, int len)
{
	int			pos;
	int			start;
	t_segment	*segment;

	pos = 0;
	start = 0;
	str[len] = 0;
	while (NOTFOUND != pos)
	{
		pos = indexof(str, '\n', start);
		if (!(segment = (t_segment *)malloc(sizeof(t_segment))))
			return (ERROR);
		segment->str = mod_substr(str, start, (-1 == pos) ? len : pos);
		segment->next = NULL;
		sfile->fseg = (sfile->fseg) ? sfile->fseg : segment;
		if (sfile->lseg)
			sfile->lseg->next = segment;
		sfile->lseg = segment;
		segment->status = (-1 == pos) ? CONTINUE : FINAL;
		sfile->status = (FINAL == segment->status) ? FINAL : sfile->status;
		start = start + pos + 1;
	}
	return (OK);
}

void	supply_str(int status, t_segment *seg, char *str)
{
	char		*s;

	while (CONTINUE == status && seg)
	{
		s = seg->str;
		while ((*str = *s++))
			str++;
		status = seg->status;
		seg = seg->next;
	}
	*str = 0;
}

int		process_line(t_file **firstfile_pt, char **line)
{
	int			len;
	t_segment	*seg;
	char		*str;
	int			status;

	if (ERROR == (*firstfile_pt)->current->status)
		return (clear(firstfile_pt, ERROR));
	len = 0;
	status = CONTINUE;
	seg = (*firstfile_pt)->current->fseg;
	while (CONTINUE == status && seg)
	{
		len = len + mod_strlen(seg->str);
		status = seg->status;
		seg = seg->next;
	}
	status = CONTINUE;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (clear(firstfile_pt, ERROR));
	*line = str;
	seg = (*firstfile_pt)->current->fseg;
	supply_str(status, seg, str);
	return (clear(firstfile_pt, CONTINUE));
}

t_file	*get_file(t_file *firstfile, int fd)
{
	t_file			*wf;

	wf = (NULL == firstfile) ? NULL : firstfile;
	while (wf && fd != (wf)->fd)
		wf = wf->next;
	if ((!wf || fd != wf->fd) && (wf = (t_file *)malloc(sizeof(t_file))))
	{
		wf->fd = fd;
		wf->fseg = NULL;
		wf->lseg = NULL;
		wf->status = CONTINUE;
		if ((!firstfile))
			wf->next = NULL;
		else
			wf->next = firstfile;
		firstfile = wf;
	}
	firstfile->current = wf;
	return (firstfile);
}

int		get_next_line(int fd, char **line)
{
	static t_file	*firstfile = NULL;
	char			*str;
	int				len;

	firstfile = get_file(firstfile, fd);
	if (!firstfile || 0 >= BUFFER_SIZE || 0 > fd)
		return (ERROR);
	while (CONTINUE == (firstfile)->current->status)
	{
		if (!(str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
			return (clear(&firstfile, ERROR));
		if ((len = read((firstfile)->current->fd, str, BUFFER_SIZE)) > 0)
		{
			if (ERROR == process_buffer((firstfile)->current, str, len))
				return (clear(&firstfile, ERROR));
		}
		else
			(firstfile)->current->status = (0 == len) ? END : ERROR;
		free(str);
	}
	return (process_line(&firstfile, line));
}

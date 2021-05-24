/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremarqu <jremarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 19:50:17 by jremarqu          #+#    #+#             */
/*   Updated: 2021/05/25 01:17:27 by jremarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	end_of_line(t_stock *stock)
{
	while (stock->lineu > stock->line_end - stock->shed
		   && *(stock->line_end) != '\n')
		stock->line_end++;
	if (*(stock->line_end) == '\n')
		return (stock->lineu > stock->line_end - stock->shed);
	return (0);
}

static int	increase_shed_size(t_stock *stock)
{
	char		*new_shed;
	long		new_size;

	new_size = stock->length * SHED_MULT;
	if (new_size < stock->length + BUF_SIZE)
		new_size += BUF_SIZE;
	new_shed = malloc((new_size + 1) * sizeof(char));
	if (!new_shed)
		return (1);
	ft_strcpy(new_shed, stock->shed);
	new_shed[new_size] = '\0';
	stock->line_end = new_shed + (stock->line_end - stock->shed);
	free(stock->shed);
	stock->shed = new_shed;
	stock->length = new_size;
	return (0);
}

static int	setup(t_stock **stock)
{
	*stock = malloc(sizeof(t_stock));
	if (!*stock)
		return (1);
	(*stock)->length = BUF_SIZE;
	(*stock)->shed = malloc(((*stock)->length + 1) * sizeof(char));
	if (!(*stock)->shed)
		return (1);
	(*stock)->shed[(*stock)->length] = '\0';
	(*stock)->lineu = 0;
	(*stock)->line_end = (*stock)->shed;
	(*stock)->read_res = 1;
	return (0);
}

static int	deal_with_results(t_stock **pointer_to_stock
		, t_stock *stock, char **line)
{
	if (stock->read_res < 0)
		return (-1);
	*line = ft_strsub(stock->shed, 0, stock->line_end - stock->shed);
	if ((stock->read_res <= 0 || stock->lineu <= 0))
	{
		if (stock->shed)
			free(stock->shed);
		free(stock);
		*pointer_to_stock = NULL;
		return (0);
	}
	stock->lineu += stock->shed - stock->line_end - (stock->read_res > 0
			&& *(stock->line_end) == '\n'
			&& stock->lineu != stock->line_end - stock->shed);
	ft_memcpy(stock->shed, stock->line_end + 1, stock->lineu);
	stock->line_end = stock->shed;
	return (1);
}

int	get_next_line(int const fd, char **line)
{
	static t_stock	*stocks[MAX_FD];

	if (fd >= MAX_FD || fd < 0 || line == NULL)
		return (-1);
	if (stocks[fd] && stocks[fd]->read_res == 0)
		return (0);
	if (!stocks[fd] && setup(&stocks[fd]))
		return (-1);
	while (stocks[fd]->read_res > 0 && !((end_of_line(stocks[fd]))))
	{
		while (stocks[fd]->lineu + BUF_SIZE > stocks[fd]->length)
			if (increase_shed_size(stocks[fd]))
				return (-1);
		stocks[fd]->read_res = read(fd, stocks[fd]->shed + stocks[fd]->lineu,
				BUF_SIZE);
		stocks[fd]->lineu += stocks[fd]->read_res;
	}
	return (deal_with_results(&stocks[fd], stocks[fd], line));
}

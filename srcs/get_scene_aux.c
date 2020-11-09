/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: appinha <appinha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:45:07 by appinha           #+#    #+#             */
/*   Updated: 2020/11/08 19:43:48 by appinha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	scene_line_split(t_scene *scene, short int qty, char *msg_nbr)
{
	scene->split = ft_split(scene->line, ' ');
	if (ft_strlen_2(scene->split) != (size_t)qty)
		error_msg(msg_nbr, scene, 0);
}

void	lstadd_front_elem(t_elem **lst, t_elem *new, int *qty)
{
	new->next = NULL;
	if ((*qty) == 0)
		(*lst) = new;
	else
	{
		while ((*lst)->next != NULL)
			(*lst) = (*lst)->next;
		(*lst)->next = new;
	}
	(*qty)++;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:37:28 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/17 20:58:32 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	lst_free(t_data **hold)
{
	t_data	*tmp;
	t_data	*ptr;

	if (!hold || !*hold)
		return ;
	tmp = *hold;
	while (tmp)
	{
		ptr = tmp;
		tmp = tmp->next;
		free(ptr->data);
		free(ptr);
	}
	*hold = NULL;
}

void	*my_malloc(size_t size, int mode)
{
	static t_data	*head;
	t_data			*node;
	void			*data;

	if (mode == 1)
	{
		data = malloc(size);
		if (!data)
			return (lst_free(&head), exit(1), NULL);
		node = malloc(sizeof(t_data));
		if (!node)
			return (lst_free(&head), exit(1), NULL);
		node->data = data;
		node->next = NULL;
		if (head != NULL)
			node->next = head;
		head = node;
		return (data);
	}
	if (!mode)
		return (lst_free(&head), exit(1), NULL);
	return (lst_free(&head), exit(0), NULL);
}
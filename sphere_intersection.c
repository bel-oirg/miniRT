/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 06:22:35 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/01 10:37:41 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	insert_sphere(t_sphere sph)
{
	t_object	new;

	new.type = SPHERE;
	new.sphere = my_malloc(sizeof(t_sphere), 1);
	new.sphere->sphere_o = sph.sphere_o;
	new.sphere->raduis = sph.raduis;
	new.sphere->material = sph.material;
	new.sphere->transform = sph.transform;
	new.sphere->next = NULL;            //TODO
	return (new);
}

void    replace_node(t_intersection *current, t_intersection *new)
{
    new->next = my_malloc(sizeof(t_intersection), 1);
    new->next->count = current->count;
    new->next->t = current->t;
    new->next->object = current->object;
    new->next->next = current->next;

    current->count = new->count;
    current->object = new->object;
    current->t = new->t;
    current->next = new->next;
}

void    add_intersection(t_intersection *head, t_intersection *new)
{
    t_intersection  *current;

    current = head;
    if (!head->count)
    {
        head->count = new->count;
        head->t = new->t;
        head->object = new->object;
        head->next = NULL;
    }
    else
    {
        while(current && current->t < new->t)
            current = current->next;
        if (!current)
        {
            current = my_malloc(sizeof(t_intersection), 1);
            current->count = new->count;
            current->t = new->t;
            current->object = new->object;
            current->next = NULL;
        }
        else
            replace_node(current, new);
    }
}

/*
    Rotate
    Scale
    Translate
*/

void    intersect_sphere(t_sphere sph, t_ray ray, t_intersection *head)
{
	t_intersection  inter1;
	t_intersection  inter2;
	double          delta;
	t_tuple         sphere_to_ray;
	double			abc[3];

	sphere_to_ray = t_t(ray.origin, '-', get_tup(0, 0, 0, 0)); //get_tup(0, 0, 0, 1)
    abc[0] = _dot4(ray.direction, ray.direction);
	abc[1] = 2 * _dot4(ray.direction, sphere_to_ray);
    abc[2] = _dot4(sphere_to_ray, sphere_to_ray) - pow(sph.raduis, 2);
    delta = pow(abc[1], 2) - 4 * abc[0] * abc[2];
    if (delta < EPSILON)
		return ;
    inter1.count = 2;
	inter2.count = 2;
	inter1.t = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
	inter2.t = (-abc[1] + sqrt(delta)) / (2 * abc[0]);
    printf ("t %f\n", inter1.t);
	inter1.object = insert_sphere(sph);
	inter2.object = insert_sphere(sph);
    add_intersection(head, &inter1);
    add_intersection(head, &inter2);
}

/*
    The hit point cannot be negative
*/
t_intersection	*_hit(t_intersection *head)
{
	t_intersection  *current;

    current = head;
	while (current && current->count && current->t < EPSILON)
		current = current->next;
	if (!current || current->count == 0)
		return (NULL);  //maybe in one line
	return (current);
}

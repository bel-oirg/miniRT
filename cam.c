/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:09:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/01 11:47:40 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam   *init_cam()
{
    t_cam   *cam;

    cam = my_malloc(sizeof(t_cam), 1);
    cam->ratio = (double) WIDTH/HEIGHT;
    cam->field_of_view = 1.3f;
    cam->half_view = tan(cam->field_of_view / 2);
    // cam->transf = get_vec(0.0f, 0.0f, 0.0f);
    // cam->cam_o = get_tup(0.0, 0.0, 0.0, 0.0);
    if (cam->ratio >= 1)
        cam->half_width = cam->half_view,
        cam->half_height = cam->half_view / cam->ratio;
    else
        cam->half_width = cam->half_view * cam->ratio,
        cam->half_height = cam->half_view;
    cam->pixel_move = (cam->half_width * 2) / WIDTH;
    return (cam);
}
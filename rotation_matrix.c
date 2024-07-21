/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:57:23 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/21 18:00:48 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_dot	*rot_x(t_dot ray, double norm_angle)
{
    t_dot l1;
    t_dot l2;
    t_dot l3;
    t_dot *rotated;
    double angle;

    /*
    [-1, 1] -> [-PI, PI]
    */
    angle = M_PI * norm_angle;
    l1 = (t_dot){1.0f, 0.0f, 0.0f};
    l2 = (t_dot){0.0f, cos(angle), -sin(angle)};
    l3 = (t_dot){0.0f, sin(angle), cos(angle)};

    rotated = get_vec(ray.x * l1.x + ray.y * l1.y+ ray.z * l1.z,
                      ray.x * l2.x + ray.y * l2.y+ ray.z * l2.z,
                      ray.x * l3.x + ray.y * l3.y+ ray.z * l3.z);
    return (rotated);
}

t_dot	*rot_y(t_dot ray, double norm_angle)
{
    t_dot l1;
    t_dot l2;
    t_dot l3;
    t_dot *rotated;
    double angle;

    /*
    [-1, 1] -> [-PI, PI]
    */
    angle = M_PI * norm_angle;
    l1 = (t_dot){cos(angle), 0.0f, sin(angle)};
    l2 = (t_dot){0.0f, 1.0f, 0.0f};
    l3 = (t_dot){-sin(angle), 0.0f, cos(angle)};
    rotated = get_vec(ray.x * l1.x + ray.y * l1.y+ ray.z * l1.z,
                      ray.x * l2.x + ray.y * l2.y+ ray.z * l2.z,
                      ray.x * l3.x + ray.y * l3.y+ ray.z * l3.z);
    return (rotated);
}

t_dot	*rot_z(t_dot ray, double norm_angle)
{
    t_dot l1;
    t_dot l2;
    t_dot l3;
    t_dot *rotated;
    double angle;

    /*
    [-1, 1] -> [-PI, PI]
    */
    angle = M_PI * norm_angle;
    l1 = (t_dot){cos(angle), -sin(angle), 0.0f};
    l2 = (t_dot){sin(angle), cos(angle), 0.0f};
    l3 = (t_dot){0.0f, 0.0f, 1.0f};
    rotated = get_vec(ray.x * l1.x + ray.y * l1.y+ ray.z * l1.z,
                      ray.x * l2.x + ray.y * l2.y+ ray.z * l2.z,
                      ray.x * l3.x + ray.y * l3.y+ ray.z * l3.z);
    return (rotated);
}



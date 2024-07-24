/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 04:11:34 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/24 08:11:53 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int rgb_conv(float r, float g, float b)
{
    u_int8_t             red;
    u_int8_t             green;
    u_int8_t             blue;

    if (r > 1.0f)
        r = 1.0f;
    if (g > 1.0f)
        g = 1.0f;
    if (b > 1.0f)
        b = 1.0f;
    // printf("%f\n", r);
    // printf("%f\n", g);
    // printf("%f\n", b);

    red = 255 * r;
    green = 255 * g;
    blue = 255 * b;

    return (red << 16 | green << 8 | blue);
}

unsigned int get_col(float d, unsigned int base_color)
{
    u_int8_t red;
    u_int8_t green;
    u_int8_t blue;

    red = ((base_color >> 16) & 255) * d;
    green = ((base_color >> 8) & 255) * d;
    blue = ((base_color) & 255) * d;

    return ((red << 16) | (green << 8) | (blue));
}

t_dot *rgb_v(unsigned int base_color)
{
    u_int8_t red;
    u_int8_t green;
    u_int8_t blue;

    red = ((base_color >> 16) & 255);
    green = ((base_color >> 8) & 255);
    blue = ((base_color) & 255);
    return (get_vec(red, green, blue));
}




#include "minirt.h"

void	plane(t_img *img)
{
	t_dot		*o;
	t_dot		*d;
	int x;
	int y;

    t_dot *light_d = normalizer(get_vec(1.0f, 1.0f, 1.0f));


	o = get_vec(0.0f, 0.0f, 0.0f);

	float A = 5.0f;
	float B = -5.0f;
	float C = 5.0f;
	float D = 1.0f;


	y = -1;

	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)

		{
			if (y < HEIGHT / 1.95)
				continue;
			d = get_vec((float) x / HEIGHT,  (float) y / WIDTH, -5.0f);
			float	point = ( D - A * o->x - B * o->y - C * o->z) / (A * d->x + B * d->y + C * d->z );

			if (point <= 0)
				continue;

			t_dot *hit_p = normalizer(v_v(o, '+', v_f(d, '*', point)));
            float angle = _dot(*hit_p, *light_d) * 0.5f + 0.5f;

	
            my_mlx_pp(img, x, y, get_col(angle, rgb_conv(1, 0, 0.0f)));
		}
	}
}

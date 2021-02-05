/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: appinha <appinha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 23:53:20 by apuchill          #+#    #+#             */
/*   Updated: 2021/02/05 15:18:36 by appinha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "errors.h"
#include "scene.h"
#include "tests.h"

static t_ray	gen_ray(t_elem *cam, float x, float y)
{
	t_ray	ray;

	ray.coord = cam->coord;
	ray.normal = v_add(v_scale(cam->cam.hor, x), v_scale(cam->cam.ver, y));
	ray.normal = v_add(ray.normal, cam->cam.llc);
	ray.normal = v_norm(v_sub(ray.normal, ray.coord));
	ray.hit = (t_hit) {0};
	return (ray);
}

static void		render_img(t_rt *rt)
{
	int		x;
	int		y;
	t_ray	ray;
	int		colour;

	if (!rt->scene.cam)
		return ;
	y = -1;
	while (y++ < (rt->size_y - 1))
	{
		x = -1;
		while (x++ < (rt->size_x - 1))
		{
			// printf("\ncoord: %i %i\n", x, y);
			ray = gen_ray(rt->scene.cam,
							(float)x / rt->size_x, (float)y / rt->size_y);
			colour = raytrace(rt, &ray);
			pixel_put(&rt->img, x, (rt->size_y - 1) - y, colour);
		}
	}
	if (rt->save == false)
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img.ptr, 0, 0);
}

int				main(int argc, char *argv[])
{
	t_rt	rt;

	if (argc < 2)
		error_msg_and_exit("001");
	if (argc > 3)
		error_msg_and_exit("002");
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7) != 0)
		error_msg_and_exit("003");
	rt.save = (argc == 3);
	init_scene(argv[1], &rt.scene);
	// print_triage_scene_info(&rt.scene);
	init_mlx(&rt);
	render_img(&rt);
	run_mlx(&rt);
	return (0);
}

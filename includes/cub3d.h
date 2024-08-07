/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:00:44 by okoca             #+#    #+#             */
/*   Updated: 2024/08/03 10:06:18 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/time.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>
# include <math.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>

# include "mlx.h"
# include "libft.h"
# include "render.h"
# include "parser.h"

# define SCREEN_WIDTH 1680
# define SCREEN_HEIGHT 720

# define FORCE 5.00f

# define PROG_NAME "cub3d"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef USE_CUSTOM_FONT
#  define USE_CUSTOM_FONT 0
# endif

typedef int	t_color;

# define CEILLING_COLOR 0x70129a
# define FLOOR_COLOR 0x0fa0b9

# define MINIMAP_WALL 0xfb990f
# define MINIMAP_FLOOR 0x0bf90f
# define MINIMAP_PLAYER 0xfa8a8a
# define MINIMAP_SIZE 5

# define TEXTURE_COUNT 4

typedef struct s_keys
{
	int			up;
	int			down;
	int			right;
	int			left;
	int			r_left;
	int			r_right;
	int			mouse;
	t_vecint	m_pos;
}	t_keys;

typedef struct s_ctx
{
	void		*mlx;
	void		*window;
	t_texture	*textures;
	t_map		map;
	t_img		img;
	t_renderer	renderer;
	t_raytracer	raytracer;
	t_fps		fps;
	t_keys		keys;
	t_map_data	*mapdata;
}	t_ctx;

t_map		init_map(t_ctx *ctx);

int			cb_loop(t_ctx *ctx) __attribute__((cold));

t_ctx		cb_init_ctx(t_map_data *mapdata) __attribute__((cold));

int			cb_init_mtx(t_ctx *ctx) __attribute__((cold));

int			cb_handle_key(t_ctx *ctx);

int			cb_free_all(t_ctx *ctx) __attribute__((cold));

int			cb_mini_draw(void *data) __attribute__((hot));

void		cb_put_pixel(t_img *img, t_vecint vec, t_color color, float shading)
			__attribute__((hot));

int			cb_darken_color(int color, float shade) __attribute__((hot));

int			cb_clamp(int color) __attribute__((hot));

int			init_textures(t_ctx *ctx) __attribute__((cold));

uint64_t	get_time(void);

void		cb_free_map(t_ctx *ctx) __attribute__((cold));

void		cb_free_tex(t_ctx *ctx) __attribute__((cold));

int			cb_exit(void *param) __attribute__((cold));

void		cb_wall_dist(t_ctx *ctx) __attribute__((hot));

void		cb_check_hit(t_ctx *ctx) __attribute__((hot));

void		cb_side_step(t_ctx *ctx) __attribute__((hot));

void		cb_rt_set(t_ctx *ctx);

void		cb_draw_fps(t_ctx *ctx) __attribute__((hot));

void		cb_draw_ceilling_floor(t_ctx *ctx, int flag) __attribute__((hot));

int			cb_max(int a, int b);

int			cb_min(int a, int b);

void		cb_draw_minimap(t_ctx *ctx);

int			cb_key_toggle(int keycode, void *data);

int			cb_mouse_move(int keycode, int x, int y, void *param);

void		cb_rot_left(t_player *p, float force);

void		cb_rot_right(t_player *p, float force);

#endif

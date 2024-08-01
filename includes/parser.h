/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:08:25 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/01 13:46:48 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# include "cub3d.h"

typedef struct s_texture
{
	t_direction	dir;
	char		*path;
}	t_texture;

typedef struct s_map_data
{
	int			fd;
	char		**input;
	char		**map;
	t_texture	**textures;
	char		*f_colour;
	char		*c_colour;
}	t_map_data;

/* General Utilities */
int		resize_arr(char ***arr, int *size);

/* Boolean helper functions*/
bool	is_empty_line(char *line);
bool	is_space(unsigned char c);
bool	is_valid_fname(char *fname);

/* Garbage collection */
void	free_arr(void **arr);
void	bin_textures(t_texture **texts);

#endif
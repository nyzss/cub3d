/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:05:49 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/03 10:21:27 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	read_cub(t_map_data *mapdata, char *fname)
{
	if (!valid_fname(fname))
	{
		ft_putendl_fd("Error\nInvalid filename", 2);
		return (1);
	}
	if (init_input(mapdata, fname))
		return (1);
	get_file_contents(mapdata);
	if (!mapdata->input)
	{
		ft_putendl_fd("Error\nCould not retrieve file contents", 2);
		bin_parse_data(mapdata);
		return (1);
	}
	mapdata->tex_paths = get_textures(mapdata);
	if (!mapdata->tex_paths)
	{
		ft_putendl_fd("Error\nCould not retrieve texture paths from file.", 2);
		bin_parse_data(mapdata);
		return (1);
	}
	return (0);
}

t_map_data	*parse(char **av)
{
	t_map_data	*new;
	t_map_data	mapdata;
	char		*fname;

	fname = av[1];
	if (read_cub(&mapdata, fname))
		return (NULL);
	if (get_hex_colour(&mapdata, 4) || get_hex_colour(&mapdata, 5))
	{
		bin_parse_data(&mapdata);
		return (ft_putendl_fd("Error\nInvalid RGB values.", 2), NULL);
	}
	get_map(&mapdata);
	if (read_map(&mapdata))
	{
		bin_parse_data(&mapdata);
		return (ft_putendl_fd("Error\nCould not read map.", 2), NULL);
	}
	if (!valid_map(&mapdata))
		return (bin_parse_data(&mapdata), NULL);
	fill_player_room(mapdata.map);
	new = ft_calloc(1, sizeof(t_map_data));
	ft_memmove(new, &mapdata, sizeof(t_map_data));
	return (new);
}

/*
int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	t_map_data *data = parse(av);
	if (data)
	{
		bin_parse_data(data);
		free(data);
	}
	return (0);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:05:49 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/01 16:18:55 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_map_data	mapdata;
	char		*fname;
	size_t		i;

	(void)ac;
	fname = av[1];
	if (!is_valid_fname(fname))
		return (printf("Error\nInvalid filename\n"));
	if (init_input(&mapdata, fname))
		return (1);
	get_file_contents(&mapdata);
	if (!mapdata.input)
		return (printf("Error\nCould not retrieve file contents\n"));
	mapdata.tex_paths = get_textures(&mapdata);
	if (!mapdata.tex_paths)
		return (printf("Error\nCould not retrieve "
				"texture paths from file.\n"));
	i = -1;
	while (++i < 4)
		printf("%s", mapdata.tex_paths[i]->path);
}
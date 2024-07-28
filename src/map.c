/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 08:44:50 by okoca             #+#    #+#             */
/*   Updated: 2024/07/28 09:09:44 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* 111111111111
* 100000000001
* 100000000001
* 10P000110001
* 100000110001
* 100000000001
* 100000000001
* 100000000001
* 100000000001
* 111111111111
*/
t_map	*init_map()
{
	t_map	*map;
	int		i;

	i = 0;
	map = malloc(sizeof(t_map));
	map->player.x = 2;
	map->player.y = 3;
	map->raw = malloc(sizeof(char *) * (11));
	while (i < 10)
	{
		if (i == 0 || i == 9)
			map->raw[i] = ft_strdup("111111111111");
		else if (i == 3 || i == 4)
			map->raw[i] = ft_strdup("100000110001");
		else
			map->raw[i] = ft_strdup("100000000001");
		i++;
	}
	map->raw[i] = NULL;
	return (map);
}
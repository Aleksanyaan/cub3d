/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:21:10 by pargev            #+#    #+#             */
/*   Updated: 2026/01/28 20:14:46 by pargev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_config config;
	
	config = parse("/home/pargev/Desktop/cub3d/config.cub");

	printf("%s\n", config.north_texture);
	printf("%s\n", config.south_texture);
	printf("%s\n", config.west_texture);
	printf("%s\n", config.east_texture);
	printf("%d,%d,%d\n", config.floor_color->red, config.floor_color->green, config.floor_color->blue);
	printf("%d,%d,%d\n", config.ceiling_color->red, config.ceiling_color->green, config.ceiling_color->blue);
	int i = 0;
	while (config.map && config.map[i])
	{
		printf("%s\n" ,config.map[i]);
		i++;
	}

	free_config(&config);
}

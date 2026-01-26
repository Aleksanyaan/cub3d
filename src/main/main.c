/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:21:10 by pargev            #+#    #+#             */
/*   Updated: 2026/01/26 22:31:42 by pargev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_config config;
	
	config = parse_config("/home/pargev/Desktop/cub3d/config.cub");

	printf("%s\n", config.north_texture);
	printf("%s\n", config.south_texture);
	printf("%s\n", config.west_texture);
	printf("%s\n", config.east_texture);
	printf("%d,%d,%d\n", config.floor_color->red, config.floor_color->green, config.floor_color->blue);
	printf("%d,%d,%d\n", config.ceiling_color->red, config.ceiling_color->green, config.ceiling_color->blue);
}

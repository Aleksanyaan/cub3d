/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:35:55 by zaleksan          #+#    #+#             */
/*   Updated: 2026/06/18 13:40:56 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**parse_map(char **config_text, int start)
{
	int		len;
	char	**map;

	len = start;
	while (config_text[len])
		len++;
	map = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!map)
		return (NULL);
	if (!parse_map_rows(config_text, map, start))
	{
		free_string_array(map);
		return (NULL);
	}
	return (map);
}

int	parse_textures(char *info, t_config *config)
{
	if (!config->north_texture && ft_strnstr(info, "NO", 2) == info)
		config->north_texture = ft_strtrim(info + 2, " \n");
	else if (!config->south_texture && ft_strnstr(info, "SO", 2) == info)
		config->south_texture = ft_strtrim(info + 2, " \n");
	else if (!config->west_texture && ft_strnstr(info, "WE", 2) == info)
		config->west_texture = ft_strtrim(info + 2, " \n");
	else if (!config->east_texture && ft_strnstr(info, "EA", 2) == info)
		config->east_texture = ft_strtrim(info + 2, " \n");
	else
		return (0);
	return (1);
}

static int	parse_config_line(char **config_text, t_config *config,
				char *info, int i)
{
	if (info[0] == '\n' || parse_textures(info, config))
		return (0);
	if (ft_strnstr(info, "F", 1) == info)
		config->floor_color = parse_color(ft_strtrim(info + 1, " \n"));
	else if (ft_strnstr(info, "C", 1) == info)
		config->ceiling_color = parse_color(ft_strtrim(info + 1, " \n"));
	else if (ft_str_only(info, " \n10NWES"))
	{
		config->map = parse_map(config_text, i);
		parse_position(config->map, &config->x_position, &config->y_position);
		return (2);
	}
	else
		return (1);
	return (0);
}

int	parse_config(char **config_text, t_config *config)
{
	int		i;
	char	*info;
	int		ret;

	i = 0;
	while (config_text[i])
	{
		info = config_text[i];
		while (*info == ' ')
			info++;
		ret = parse_config_line(config_text, config, info, i);
		if (ret == 1)
			return (1);
		if (ret == 2)
			break ;
		i++;
	}
	return (0);
}

t_config	parse(char *path)
{
	char		**config_text;
	t_config	config;

	ft_bzero(&config, sizeof(t_config));
	if (!check_file_extension(path, "cub"))
		exit_with_error(": configuration's extension must be .cub");
	config_text = read_config(path);
	if (parse_config(config_text, &config))
		free_and_exit(&config, config_text,
			": configuration contains an invalid identifier");
	free_string_array(config_text);
	cheack_config(&config);
	return (config);
}

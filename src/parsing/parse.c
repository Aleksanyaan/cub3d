/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:21:05 by pargev            #+#    #+#             */
/*   Updated: 2026/01/27 18:45:43 by pargev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_extension(char *path, char *extension)
{
	int	path_len;
	int	extension_len;

	path_len = ft_strlen(path);
	extension_len = ft_strlen(extension);
	if (path_len < extension_len + 2)
		return (0);
	if (!ft_strncmp(path + path_len - extension_len, extension, extension_len))
	{
		if (path[path_len - extension_len - 1] == '.'
			&& !ft_strrchr("\\/:*?\"<>|", path[path_len - extension_len - 2]))
			return (1);
	}
	return (0);
}

int	config_lines_count(char *path)
{
	int		fd;
	int		len;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_with_error(strerror(errno));
	len = 0;
	while (1)
	{
		line = get_next_line(fd);	
		if (!line)
			break ;
		if (line[0] != '\n')
			len++;
		free(line);
	}
	close(fd);
	return (len);
}

char	**read_config(char *path)
{
	int		fd;
	char	**config;
	char	*line;
	int		i;

	config = (char **)malloc(sizeof(char *) * (config_lines_count(path) + 1));
	if (!config)
		exit_with_error(strerror(errno));
		fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_with_error(strerror(errno));
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			config[i++] = line;
		else
			free(line);
	}
	config[i] = 0;
	close(fd);
	return (config);
}

int	parse_color2(char *color_text, int *color, int min, int max)
{
	int	i;

	i = 0;
	while (color_text[i])
	{
		if(!ft_isdigit(color_text[i]))
			return (0);
		i++;
	}
	*color = ft_atoi(color_text);
	if (*color < min || *color > max)
		return (0);
	return (1);
}

t_color	*parse_color(char *color_text)
{
	char	**color_matrix;
	int		len;
	t_color	*color;

	color_matrix = ft_split(color_text, ',');
	len = 0;
	while (color_matrix[len])
		len++;
	if (len != 3)
		return (NULL);
	color = (t_color *)malloc(sizeof(t_color));
	if (!parse_color2(color_matrix[0], &color->red, 0, 255) || !parse_color2(color_matrix[1], &color->green, 0, 255) || !parse_color2(color_matrix[2], &color->blue, 0, 255))
	{
		free(color);
		return (NULL);
	}
	return (color);
}

char*	parse_config2(char **config_text, t_config *config)
{
	int		i;
	char	*info;

	i = 0;
	while (config_text[i])
	{
		info = config_text[i];
		if (config_text[0] == 0);
		else if (ft_strnstr(info, "NO", 2) == info)
			config->north_texture = ft_strtrim(info + 2, " \n");
		else if (ft_strnstr(info, "SO", 2) == info)
			config->south_texture = ft_strtrim(info + 2, " \n");
		else if (ft_strnstr(info, "WE", 2) == info)
			config->west_texture = ft_strtrim(info + 2, " \n");
		else if (ft_strnstr(info, "EA", 2) == info)
			config->east_texture = ft_strtrim(info + 2, " \n");
		else if (ft_strnstr(info, "F", 1) == info)
		{
			config->floor_color = parse_color(ft_strtrim(info + 1, " \n"));
			if (config->floor_color == NULL)
			{
				free_string_array(config_text);
				exit_with_error(": configuration contains incorrect color definition");
			}
		}
		else if (ft_strnstr(info, "C", 1) == info)
		{
			config->ceiling_color = parse_color(ft_strtrim(info + 1, " \n"));
			if (config->ceiling_color == NULL)
			{
				free_string_array(config_text);
				exit_with_error(": configuration contains incorrect color definition");
			}
		}
		else if (ft_str_only(ft_strtrim(info, " \n"), "10NWES"))
			return (info);
		else
		{
			free_string_array(config_text);
			exit_with_error(": configuration contains an invalid identifier");
		}
		i++;
	}
}

t_config	parse_config(char *path)
{
	char		**config_text;
	t_config	config;

	if (!check_file_extension(path, "cub"))
		exit_with_error(": configuration's extension must be .cub");
	config_text = read_config(path);
	parse_config2(config_text, &config);
	free_string_array(config_text);
	return (config);
}

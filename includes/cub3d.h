/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pargev <pargev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:21:14 by pargev            #+#    #+#             */
/*   Updated: 2026/01/28 14:27:43 by pargev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_color	*floor_color;
	t_color	*ceiling_color;
	char	**map;
}	t_config;


// =========== Main ============

// ========== Parsing ==========

t_config	parse(char *config_path);

// ========= utils =========

void	exit_with_error(char *error_message);
void	free_config_and_exit(t_config *config, char **string, char *error_message);
void	free_string_array(char **string);
void	free_config(t_config *config);
int		ft_str_only(const char *s, const char *allowed);
char	*ft_strdup_free(char *s1);

#endif
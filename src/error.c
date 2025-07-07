/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:52:27 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/07 12:51:56 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_error(const char *message)
{
	int	i;

	i = 0;
	write(2, "Error\n", 7);
	while (message[i])
	{
		write(2, &message[i], 1);
		i++;
	}
	write(2, "\n", 1);
}

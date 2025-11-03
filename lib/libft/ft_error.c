/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:01:17 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/03 18:05:47 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_puterr(char *errstr)
{
	if (!errstr)
		return (-1);
	write(STDERR_FILENO, "Error\n", 6);
	while (*errstr)
		write(STDERR_FILENO, errstr++, 1);
	write(STDERR_FILENO, "\n", 1);
	return (-1);
}

int	ft_puterr_exit(char *errstr)
{
	ft_puterr(errstr);
	exit(1);
	return (1);
}

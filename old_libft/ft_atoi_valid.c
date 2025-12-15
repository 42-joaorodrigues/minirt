/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:47:19 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/03 16:49:42 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_valid_end(char c)
{
	return (c == '\0' || c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	ft_atoi_valid(char *str, int *value)
{
	long	result;
	int		sign;

	if (!str || !*str)
		return (0);
	sign = 1;
	result = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str < '0' || *str > '9')
		return (0);
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	if (!is_valid_end(*str))
		return (0);
	result *= sign;
	if (result > 2147483647 || result < -2147483648)
		return (0);
	*value = (int)result;
	return (1);
}

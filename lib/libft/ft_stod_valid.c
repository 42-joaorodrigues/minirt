/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stod_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:35:53 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/03 17:02:35 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_valid_end(char c)
{
	return (c == '\0' || c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static char	*parse_exponent(char *ptr, double *exp_val)
{
	int	exp_sign;
	int	exp;

	exp_sign = 1;
	exp = 0;
	*exp_val = 0;
	if (*ptr == 'e' || *ptr == 'E')
	{
		ptr++;
		if (*ptr == '-' || *ptr == '+')
		{
			if (*ptr == '-')
				exp_sign = -1;
			ptr++;
		}
		if (*ptr < '0' || *ptr > '9')
			return (0);
		while (*ptr >= '0' && *ptr <= '9')
			exp = exp * 10 + (*ptr++ - '0');
		*exp_val = exp * exp_sign;
	}
	return (ptr);
}

static double	apply_exponent(double value, double exp_val)
{
	int		i;
	double	multiplier;

	if (exp_val == 0)
		return (value);
	multiplier = 1.0;
	i = 0;
	if (exp_val > 0)
	{
		while (i++ < (int)exp_val)
			multiplier *= 10.0;
	}
	else
	{
		while (i++ < -(int)exp_val)
			multiplier /= 10.0;
	}
	return (value * multiplier);
}

static int	parse_decimal(char **ptr, double *result)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 10.0;
	while (**ptr >= '0' && **ptr <= '9')
	{
		fraction += (**ptr - '0') / divisor;
		divisor *= 10.0;
		(*ptr)++;
	}
	*result += fraction;
	return (1);
}

int	ft_stod_valid(char *str, double *value)
{
	double	result;
	int		sign;
	double	exp_val;

	if (!str || !*str)
		return (0);
	sign = 1;
	result = 0.0;
	exp_val = 0;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	if (*str < '0' || *str > '9')
		return (0);
	while (*str >= '0' && *str <= '9')
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		if (!parse_decimal(&str, &result))
			return (0);
	}
	str = parse_exponent(str, &exp_val);
	if (!str || !is_valid_end(*str))
		return (0);
	*value = apply_exponent(result * sign, exp_val);
	return (1);
}

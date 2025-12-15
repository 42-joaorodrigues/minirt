/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:38:45 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/03 18:04:06 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

# define BUFFER_SIZE 1069
# define FD_MAX 69

// gnl
char	*get_next_line(int fd);
// gnl_util
size_t	ft_strlen(const char *s);
void	*ft_memset(void *ptr, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(char *s1, char *s2);

// split
char	**ft_split(const char *s, char *set);
// ft_split_util
char	*ft_strchr(const char *str, int c);
void	free_split(char **split);
int		count_split(char **split);

// atoi_valid
int		ft_atoi_valid(char *str, int *value);

// stod_valid
int		ft_stod_valid(const char *str, double *value);

// int_util
void	ft_swap(int *a, int *b);
int		ft_abs(int n);

// str_util
void	ft_putstr(char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strtrim(char const *s1, char const *set);

// ft_error
int		ft_puterr(char *errstr);
int		ft_puterr_exit(char *errstr);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:49:27 by efreire-          #+#    #+#             */
/*   Updated: 2021/11/05 17:53:31 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# include <sys/types.h>
# include <sys/uio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int				ft_atoi(const char *str);

void			ft_bzero(void *str, size_t len);

void			*ft_calloc(size_t count, size_t size);

bool			ft_file_exists(char *filepath);

int				ft_isalnum(int c);

int				ft_isalpha(int c);

int				ft_isascii(int c);

int				ft_isdigit(int c);

int				ft_isprint(int c);

bool			ft_isspace(int c);

bool			ft_isstrspace(char *str);

char			*ft_itoa(int n);

void			*ft_memchr(const void *str, int c, size_t len);

int				ft_memcmp(const void *str1, const void *str2, size_t len);

void			*ft_memcpy(void *dst, const void *src, size_t len);

void			*ft_memmove(void *dst, const void *src, size_t len);

void			*ft_memset(void *str, int c, size_t len);

long			ft_pow(int base, int exp);

void			ft_putchar_fd(char c, int fd);

void			ft_putendl_fd(char *str, int fd);

void			ft_putnbr_fd(int n, int fd);

void			ft_putstr_fd(char *str, int fd);

void			ft_replace(char *str, char to_find, char to_replace);

char			**ft_split(char const *str, char c);

char			*ft_str_expand(char *str, int len, char c);

int				ft_str_find_last(const char *haystack, const char needle);

bool			ft_strstarts(char *string, char *substring);

char			*ft_strchr(const char *str, int c);

char			*ft_strdup(const char *src);

bool			ft_strends(char *string, char *substring);

void			ft_striteri(char *str, void (*f)(unsigned int, char*));

char			*ft_strjoin(char const *str1, char const *str2);

size_t			ft_strlcat(char *dst, const char *src, size_t max_size);

size_t			ft_strlcpy(char *dst, const char *src, size_t dst_size);

size_t			ft_strlen(const char *str);

char			*ft_strmapi(char const *str, char (*f)(unsigned int, char));

int				ft_strncmp(const char *str1, const char *str2, size_t len);

char			*ft_strnstr(const char *haystack, \
					const char *needle, size_t len);

char			*ft_strrchr(const char *str, int c);

char			*ft_strtrim(char const *str, char const *set);

char			*ft_substr(char const *str, unsigned int start, size_t len);

int				ft_tolower(int c);

int				ft_toupper(int c);

bool			ft_valid_rgb(char *str);

unsigned long	ft_value_rgb(char *str);

// Lists

t_list			*ft_lstnew(void *content);

void			ft_lstadd_front(t_list **lst, t_list *new);

int				ft_lstsize(t_list *lst);

t_list			*ft_lstlast(t_list *lst);

void			ft_lstadd_back(t_list **lst, t_list *new);

void			ft_lstdelone(t_list *lst, void (*del)(void*));

void			ft_lstclear(t_list **lst, void (*del)(void*));

void			ft_lstiter(t_list *lst, void (*f)(void *));

t_list			*ft_lstmap(t_list *lst, \
					void *(*f)(void *), void (*del)(void *));

// Get Next Line

char			*get_next_line(int fd);

#endif

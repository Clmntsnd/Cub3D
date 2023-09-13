#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strchr(const char *str, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *str1, char const *str2);
char	*ft_strdup(const char *str1);
char	*ft_substr(char const *str, unsigned int start, size_t len);
char	*get_line(char **passed_stuff, char **line);
ssize_t	read_file(int fd, char **buf, char **passed_stuff, char **line);
char	*get_next_line(int fd);

# endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:34:46 by anamieta          #+#    #+#             */
/*   Updated: 2024/04/24 15:32:46 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

/* Utils */
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	free_array(char **array);
void	*ft_calloc(size_t count, size_t size);

/* Error handling */
void	args_error(void);
void	pipe_check(int *fd_pipe);
void	fork_check(pid_t pid);
void	cmd_error(char *cmd, char **arg);
void	error_handling(char *file, int exit_code);

/* Path utils */
int		path_index(char **envp);
char	**splitting_paths(char **envp);
char	*find_path(char **envp, char *argv);

/* Bonus */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
int		open_file(char *argv, int filetype);
void	here_doc(char *limiter, int argc);

#endif
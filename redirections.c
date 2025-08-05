
#include"minishell.h"

int handle_heredoc(const char *delimiter)
{
    char *line;
    int fds[2];

    if (pipe(fds) == -1)
        return -1;

    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
            break;

        write(fds[1], line, ft_strlen(line));
        write(fds[1], "\n", 1);
        free(line);
    }
    free(line);
    close(fds[1]);
    return fds[0];
}


int handle_redir_in(const char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("open infile"), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2 infile"), close(fd), 1);
	close(fd);
	return (0);
}

int handle_redir_out(const char *file)
{
	int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open outfile"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2 outfile"), close(fd), 1);
	close(fd);
	return (0);
}

int handle_redir_append(const char *file)
{
	int fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (perror("open append"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2 append"), close(fd), 1);
	close(fd);
	return (0);
}

int handle_redir_heredoc(const char *file)
{
	int fd = handle_heredoc(file);
	if (fd < 0)
		return (1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2 heredoc"), close(fd), 1);
	close(fd);
	return (0);
}

int handle_redirections(t_redirection *redir_list)
{
	t_redirection *curr = redir_list;

	while (curr)
	{
		if (curr->type == REDIR_IN && handle_redir_in(curr->file_name))
			return (1);
		else if (curr->type == REDIR_OUT && handle_redir_out(curr->file_name))
			return (1);
		else if (curr->type == REDIR_APPEND && handle_redir_append(curr->file_name))
			return (1);
		else if (curr->type == REDIR_HEREDOC && handle_redir_heredoc(curr->file_name))
			return (1);
		curr = curr->next;
	}
	return (0);
}




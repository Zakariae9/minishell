/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:22:56 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/03 21:55:31 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

extern int sig_s;

int has_redirection(t_cmd *cmd)
{
    return (cmd->redirection != NULL);
}

static char *resolve_executable_path_or_exit(t_cmd *cmd, t_env *env)
{
    struct stat sb;
    char *path = NULL;

    if (ft_strchr(cmd->av[0], '/')) 
    {
        if (access(cmd->av[0], F_OK) != 0)
        {
            fprintf(stderr, "%s: No such file or directory\n", cmd->av[0]);
            exit(127);
        }
        path = ft_strdup(cmd->av[0]);
    }
    else
    {
        path = find_cmd_path(cmd->av[0], env);
        if (!path)
        {
            fprintf(stderr, "%s: command not found\n", cmd->av[0]);
            exit(127);
        }
    }

    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        fprintf(stderr, "%s: is a directory\n", path);
        free(path);
        exit(126);
    }

    if (access(path, X_OK) != 0)
    {
        perror(path);
        free(path);
        exit(126);
    }

    return path;
}


static void run_execve(t_cmd *cmd, t_env *env)
{
    char *path = resolve_executable_path_or_exit(cmd, env);
    char **envp = convert_env_to_array(env);
    execve(path, cmd->av, envp);

    // if execve fails
    perror("execve");
    free(path);
    exit(126);
}

static void	child_process(t_cmd *cmd, t_env *env, int prev_fd, int *pipefd)
{
    signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
    
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
    
    if (cmd->next)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }
    
    if (handle_redirections(cmd->redirection) != 0)
    {
        
        exit(1);
    }
        
	if (is_builtin(cmd->av[0]))
		exit( run_builtin(cmd, &env));

	
	run_execve(cmd, env);
}

void execute_command(t_cmd *cmd, t_env **env, int *exit_status)
{

	if (!cmd->next && is_builtin(cmd->av[0]) && is_parent_builtin(cmd->av[0]) && !has_redirection(cmd))
	{
		*exit_status = run_builtin(cmd, env);
		return;
	}
	
	int prev_fd = -1;
	int pipefd[2];
    int ac = 0;
    int i = -1;
	int *pid;
	int status;
    sig_s = 1;

    t_cmd *tmp = cmd;
    while (tmp)
    {
        ac++;
        tmp = tmp->next;
    }
    pid = malloc(ac * 4);
	while (cmd)
	{
        if (cmd->next && pipe(pipefd) == -1)
            return (perror("pipe"), *exit_status = 1, (void)0);
        
        pid[++i] = fork();

        if (pid[i] == -1)
			return (perror("fork"), *exit_status = 1, (void)0);
		if (pid[i] == 0)
			child_process(cmd, *env, prev_fd, pipefd);
		if (prev_fd != -1)
			close(prev_fd);           
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmd = cmd->next;
	}
    i = 0;
	while (i < ac)
    {
        waitpid(pid[i++] , &status, 0);
		*exit_status = WEXITSTATUS(status);
    }
    sig_s = 0;
    // printf("%d\n", *exit_status);
    // printf("\n");
}








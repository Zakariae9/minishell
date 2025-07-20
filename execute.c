#include"minishell.h"

static void	run_execve(t_cmd *cmd, t_env *env)
{
	char *path = find_cmd_path(cmd->av[0], env);

	if (!path)
	{
		printf("%s: command not found\n", cmd->av[0]);
		exit(127);
	}
    char **envp = convert_env_to_array(env);
	execve(path, cmd->av, envp);
	perror("execve");
	exit(126);
}

static void	child_process(t_cmd *cmd, t_env *env, int prev_fd, int *pipefd)
{
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
		exit(1);
   

	if (is_builtin(cmd->av[0]) && !is_parent_builtin(cmd->av[0]))
		exit(run_builtin(cmd, &env));

	run_execve(cmd, env);
}

void execute_command(t_cmd *cmd, t_env **env, int *exit_status)
{
 	if (!cmd->next && is_builtin(cmd->av[0]) && is_parent_builtin(cmd->av[0]))
	{
		*exit_status = run_builtin(cmd, env);
		return;
	}
	
	int prev_fd = -1;
	int pipefd[2];
	pid_t pid;
	int status;
    
	while (cmd)
	{
        if (cmd->next && pipe(pipefd) == -1)
            return (perror("pipe"), *exit_status = 1, (void)0);
        
        pid = fork();
        if (pid == -1)
			return (perror("fork"), *exit_status = 1, (void)0);
            
		if (pid == 0)
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

	while (wait(&status) > 0)
		*exit_status = WEXITSTATUS(status);
}








#include "minishell.h"

char	*free2d_ar(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
	return (NULL);
}

void	free_token(t_token	**head)
{
	free((*head)->value);
	free(*head);
	*head = NULL;
}

void	free_list_tokens(t_token **head)
{
	t_token	*current;
	t_token	**helper;

	helper = head;
	while (*head != NULL)
	{
		current = *head;
		head = &(*head)->next;
		free_token(&current);
	}
	*helper = NULL;
}

void	free_address(t_addresses *head)
{
	t_addresses	*helper;

	while (head != NULL)
	{
		helper = head;
		head = head->next;
		free(helper->value);
		free(helper);
	}
}
void	free_cmd_list(t_cmd *cmd)
{
	while (cmd)
	{
		t_cmd *next = cmd->next;
		free(cmd);
		cmd = next;
	}
}

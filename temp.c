#include "minishell.h"

void WriteType(t_type type)
{
	if (type == en_word) {
    // Handle a regular word
    printf("This is a word token.\n");
}
else if (type == en_double_qoute) {
    // Handle a double-quoted string
    printf("This is a double-quoted string.\n");
}
else if (type == en_single_qoute) {
    // Handle a single-quoted string
    printf("This is a single-quoted string.\n");
}
else if (type == en_pip) {
    // Handle a pipe '|'
    printf("This is a pipe token.\n");
}
else if (type == en_output) {
    // Handle output redirection '>'
    printf("This is an output redirection token.\n");
}
else if (type == en_input) {
    // Handle input redirection '<'
    printf("This is an input redirection token.\n");
}
else if (type == en_append) {
    // Handle output append redirection '>>'
    printf("This is an append redirection token.\n");
}
else if (type == en_heredoc) {
    // Handle here-document '<<'
    printf("This is a heredoc token.\n");
}
else if (type == en_anything_else) {
    // Handle any other token
    printf("This is an unrecognized but expected token.\n");
}
else {
    // Unknown or truly unexpected token
    printf("Error: Unknown token type.\n");
}

}

void	print_tokens(t_token *head)
{
	int	i = 1;
	ft_putstr_fd("\nTokens====================================\n\n", 1);
	while (head)
	{
		printf("Token (%d) = %s\n", i++, head->value);
		WriteType(head->type);
		head = head->next;
	}
	ft_putstr_fd("These are all tokens===============================\n\n", 1);
}

void	Print_linked_list(t_token *head)
{
	while (head != NULL)
	{
		write(1, head->value, ft_strlen(head->value));
        write(1, "\n", 1);
		head = head->next;
	}
}
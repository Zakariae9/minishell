# ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include<string.h>
#include<signal.h>
#include<sys/wait.h>
#include <fcntl.h>


// \\// Parser

typedef enum n_expand
{
	en_expand, en_dont_expand
}t_expand;

typedef enum n_type
{
	en_word = 0,
	en_double_qoute,
	en_single_qoute,
	en_pip,
	en_output,
	en_input,
	en_append,
	en_heredoc,
	en_anything_else
}t_type;

typedef	struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}t_env;


typedef struct s_addresses
{
	void	*value;
	void	*next;
}t_addresses;

typedef struct s_token
{
	t_expand		expanding;
	t_type			type;
	char			*value;
	bool			join;
	struct s_token	*next;
}t_token;

//\\ Parser

// \\// Executer Things

typedef enum e_redir_type
{
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    REDIR_HEREDOC
}t_redir_type;


typedef struct s_redirection
{
    t_redir_type			type;
    char					*file_name;
    struct s_redirection	*next;
}t_redirection;



typedef struct s_cmd 
{
    char			**av;   
    struct s_cmd	*next; 
    t_redirection	*redirection;
} t_cmd;

//\\ Executer

// libft prototypes
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		fill_str(char const *str1, char const *str2, char *buffer);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s);
int			is_there_here(const char *s, int c);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strstr(const char *haystack, const char *needle);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
char		*delete_part(char *old_str, char *deleted_str);
char		*add_str(char *old_str, char *added_str, int pos);
size_t		ft_strcpy(char *dst, const char *src);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);


// check_errores
bool	check_are_qoutes_open(char *command);
bool	is_firs_and_last_token_valid(t_token *head);
int		is_there_anything_else(t_token *head);
bool	is_there_only$_as_double_q(char *command, t_type type);

// Expanding
void	expanding_all_tokens(t_token *head, t_env *env);
char	*expanding(char *command, t_env *env);
char	*get_variable_for_expanding(char *command, int *start, int *end_pos);
void	deside_expanding(t_token *head);
void	delete_tokens(t_token	**head, char *data);
char	*ft_getenv(char *variable, t_env *head);

// Free
char	*free2d_ar(char **str);
void	free_token(t_token	**head);
void	free_list_tokens(t_token **head);
void	free_address(t_addresses *head);

// Helpers
char	*get_address_of_closed_quote(char *command, char original_quote);
int		convert_from_add_to_pos(char *str, char c);
int		pos_of_end_of_variable(char *command, int start);
char	*get_address_of_separator(char *command);
void	join_tokens(t_token *head);
char	first_quote(char *command);
t_type	witch_type1(char c1);
t_type	witch_type(char c1, char c2);
int		num_of_char(char *str, char c);
char	*delete_spaces(char *str);
void	keep_only_space(t_token *head);
void	fixing_tokens(t_token *head);



// Lexer
char    *skip_spaces(char *command);
void	lexer(char *command, t_token **head);
char	*token_with_q(char *command, char q_type, t_token **head);
char	*token_delemeter(char *command, t_token **head);
char	*token_without_q(char *command, t_token **head);

// Linked list
t_token		*new_node(char *str, t_type type);
t_token		*last_node(t_token *head);
void		add_back(t_token **head, t_token *new);
t_addresses	*node(void *value);
void		push_back(t_addresses **head, t_addresses *new);
int			len_list(t_token *head);
char		*ft_getenv(char *var, t_env *env);


// temps
void	WriteType(t_type type);
void	print_tokens(t_token *head);
void	Print_linked_list(t_token *head);
bool	are_bash_rules_correct(t_token *head);

// main
void	start_minishell(char **env);
void	read_commands(t_token	**head, t_env *env);


// Will deleleted
void		make_env_list(char **env, t_env	**head);
void		add_back_export(t_env **head, t_env *new);
t_env		*new_node_export(char *str);


// Merge
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
t_cmd 			*tokens_to_commands(t_token *tokens);
 void			free_cmd_list(t_cmd *cmd);
 int 			add_redirection(t_cmd *cmd, t_redir_type type, char *file_name);
 int 			count_args(t_token *token);
bool			is_redirection(t_type type);
void			merging(t_token *head, t_cmd **cmd);
void			fill_redirection_struct(t_token **head_token, t_cmd **cmd);
void			fill_av(int arg_num, char **av, t_token **head);
t_cmd			*new_node_cmd();
t_redirection	*new_node_redirection(t_token *head_token);
t_redir_type	redir_type(t_type type);
int				count_arg(t_token *head);


///////////////////////////////////





bool is_builtin(char *cmd);
int run_builtin(t_cmd *cmd, t_env **env);
void execute_command(t_cmd *cmd, t_env **env, int *exit_status);
char *find_cmd_path(char *cmd, t_env *env);
int handle_redirections(t_redirection *redir_list);
char **convert_env_to_array(t_env *env);
char *join_path(const char *dir , const char *cmd);
void execute(t_cmd *cmd, t_env **g_env, int *g_exit_status);




// build_in_cmd
int ft_cd(char **args, t_env **env);
int ft_echo(t_cmd *cmd);
int ft_pwd(void);
void ft_exit(char **args);
int ft_export(char **args, t_env **env);
int ft_env(t_env *env);
int ft_unset(t_env **env, char **args);
bool is_parent_builtin(char *cmd);
void add_or_update_env(t_env **env, const char *arg);





// utils
int ft_strcmp(const char *s1, const char *s2);
size_t ft_strlen(const char *s);
char *ft_strstr(const char *haystack, const char *needle);
char *ft_strdup(const char *s);
char *ft_strchr(const char *s, int c);
void ft_putchar(char c);
char *ft_strcat(char *dest, const char *src);
int ft_strncmp(const char *str1, const char *str2, size_t n);
void	ft_putstr(char *s);
char	**ft_split(const char *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
int ft_isalpha(int c);
int ft_isalnum(int c);
char *ft_strcpyy(char *dest, const char *src);
char *ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

// free
void free_array(char **arr);
void	free_cmd_list(t_cmd *cmd);
void	free_env(t_env *env);


#endif


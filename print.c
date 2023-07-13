// FILE HAS TO BE REMOVED
#include "../includes/minishell.h"
#include "../includes/lexer.h"

char	*token_type(t_token_type type)
{
	if (type == APPEND)
		return ("APPEND");
	else if (type == HRDOC)
		return ("HRDOC");
	else if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == IN)
		return ("REDIR_IN");
	else
		return ("REDIR_OUT");
}

void	print_tokens(t_token *tokens)
{
	printf("| %-30s | %-30s | %-30s |\n", "Value", "Type", "Expandable");
	printf("|--------------------------------|--------------------------------|--------------------------------|\n");
	while (tokens)
	{
		printf("| %-30s ", tokens->token);
		printf("| %-30s ", token_type(tokens->type));

		if(tokens->expand == TRUE)
			printf("| %-30s |", "TRUE");
		else
			printf("| %-30s |", "FALSE");
		printf("\n");
		tokens = tokens->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->cmd_args[++i])
		printf("%s ", cmd->cmd_args[i]);
}

void	print_redir(t_redir *redir)
{
	if (redir)
	{
		while (redir)
		{
			if (redir->type == IN)
				printf("\t< ");
			else if (redir->type == OUT)
				printf("\t> ");
			else if (redir->type == APPEND)
				printf("\t>> ");
			else
				printf("\t<< ");
			printf("\t\t\033[1;32m%s\x1b[0m", redir->file);
			redir = redir->next;
		}
		printf("\n");
	}
	else
		printf("\t\033[1;32mno redirections\x1b[0m\n");
}

void print_ast_helper(t_ast *ast, int level) {
    if (ast) {
        for (int i = 0; i < level; i++) {
            if (i == level - 1) {
                printf("---> ");
            } else {
                printf("     ");
            }
        }
        if (ast->node->type == NODE_PIPE) {
            printf("\033[1;31mPIPE\x1b[0m\n");
        } else if (ast->node->type == NODE_CMD) {
            print_cmd(ast->node->cmd);
            print_redir(ast->node->cmd->redir);
        }

        print_ast_helper(ast->left, level + 1);
        print_ast_helper(ast->right, level + 1);
    }
}

void print_ast(t_ast *ast) {
    printf("AST:\n");
    print_ast_helper(ast, 0);
}
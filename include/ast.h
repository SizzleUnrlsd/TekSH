/**
* {{ project }}
* Copyright (C) {{ year }}  {{ organization }}
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef AST_H_
    #define AST_H_

    typedef enum {
        NODE_SEMICOLON = 0,
        NODE_PIPE = 1,
        NODE_REDIRECT_IN = 2,
        NODE_REDIRECT_OUT = 3,
        NODE_REDIRECT_APPEND = 4,
        NODE_REDIRECT_HEREDOC = 5,
        NODE_ARGUMENT = 6,
        NODE_AND = 7,
        NODE_OR = 8,
    } nodetype;

    typedef struct node_s {
        char *value;
        struct node_s *left;
        struct node_s *right;
        nodetype type;
        char padded[4];
    }node_t;

    node_t *create_node(nodetype type, char *value, ...);
    node_t *parse_pipe(char **input, shell_t *shell);
    node_t *parse_redirect(char **input, shell_t *shell);
    node_t *parse_argument(char **input, shell_t *shell);
    node_t *parse_semicolon(char **input, shell_t *shell);
    node_t *parse_and_or(char **input, shell_t *shell);
    int32_t execute_pipeline(node_t *cmd1_node, node_t *cmd2_node,
    shell_t *shell);
    void redirection_append(node_t *node, shell_t *shell);
    void redirection_dup_in(node_t *node, shell_t *shell);
    char *node_to_string(node_t *node);
    void ast(node_t *node, shell_t *shell);
    int32_t ast_final(char *command, shell_t *shell);
    void save_descriptor(int32_t *save_0, int32_t *save_1);
    void descriptor_restoration(int32_t save_0, int32_t save_1);

#endif /* !AST_H_ */

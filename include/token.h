/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:29:14 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/15 12:56:47 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type {
	TOKEN_ERROR,

	TOKEN_WORD,
	TOKEN_ASSIGNMENT,

	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_REDIR_HEREDOC_QUOTED,
	TOKEN_REDIR_HERESTRING,
	TOKEN_REDIR_DUP_IN,
	TOKEN_REDIR_DUP_OUT,

	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SEQUENCE,
	TOKEN_BACKGROUND,
	TOKEN_NEWLINE,

	TOKEN_PAREN_OPEN,
	TOKEN_PAREN_CLOSE,
	TOKEN_BRACE_OPEN,
	TOKEN_BRACE_CLOSE,
	TOKEN_DOUBLE_BRACKET_OPEN,
	TOKEN_DOUBLE_BRACKET_CLOSE,

	TOKEN_DOUBLE_SEMI,
	TOKEN_AMP_SEMI,
	TOKEN_DOUBLE_AMP_SEMI,

	TOKEN_IF,
	TOKEN_THEN,
	TOKEN_ELSE,
	TOKEN_FI,
	TOKEN_WHILE,
	TOKEN_DO,
	TOKEN_DONE,
	TOKEN_FOR,
	TOKEN_IN,
	TOKEN_CASE,
	TOKEN_ESAC,
	TOKEN_SELECT,
	TOKEN_TIME,
	TOKEN_FUNCTION,
	TOKEN_COPROC,
	TOKEN_UNTIL,
	TOKEN_ELIF,

	TOKEN_COMMENT,
	TOKEN_EOF,

	TOKEN_COUNT,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	struct s_position {
		int	line;
		int	start;
		int	end;
		int	absStart;
		int	absEnd;
	}	pos;
}	t_token;

#endif

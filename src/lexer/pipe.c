/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:53:39 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 15:54:26 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_pipe(t_lexer *lexer)
{
	if (lexer_match(lexer, '|'))
		return (lexer_emit(lexer, TOK_OR));
	return (lexer_emit(lexer, TOK_PIPE));
}

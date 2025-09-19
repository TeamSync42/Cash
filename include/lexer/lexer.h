/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:25:32 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:03:03 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>

# include "token.h"
# include "collections/vectors/vector.h"

typedef struct s_lexer
{
	char	*input;
	int		iterator;
	int		character;
	int		line;
	int		start;
	int		abs_start;
	int		fd;
	char	current_char;
	char	next_char;
	bool	end;
	bool	posix;
}	t_lexer;

t_result	lexer_init(t_lexer *lexer, char *line);

void		print_token(t_token token);

#endif // LEXER_H

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:59:08 by lbirloue          #+#    #+#             */
/*   Updated: 2024/05/08 18:38:29 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int free_all(t_data *data, char *str, int esc)
{
    t_lexer *current;
    t_lexer *temp;

    if (str)
        printf("%s\n", str);
    current = data->first;
    if (data->first)
    {
        while (current->next)
        {
            free(current->token_str);
            temp = current;
            current = current->next;
            free(temp);
        }
        free(current->token_str);
        free(current);
    }
    if (esc)
        exit (esc);
    return (0);
}

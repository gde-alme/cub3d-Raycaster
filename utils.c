/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:39 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/15 11:33:40 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

float	FixAngle(float angle) {
	if (angle <= 0)
		return ((float)(angle + 2*PI));
	else if (angle >= (float)(2*PI))
		return ((float)(angle - 2*PI));
	return (angle);
}

char	*_povAtoi(float	pov) {
	char *string = (char *)malloc(sizeof(char) * 9);
	string[0] = (int)pov % 10 + 48;
	string[1] = '.';
	string[7] = '\n';
	string[8] = '\0';

	int	atom = (int)(pov * 100000.0F);
	for (int i = 2; i < 7;i++) {
		string[i] = atom % 10 + 48;
		atom = atom / 10;
	}
	return (string);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BrickWall.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigoncal <nigoncal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:59:17 by ncolomer          #+#    #+#             */
/*   Updated: 2022/04/06 13:38:04 by nigoncal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BrickWall.hpp"

BrickWall::BrickWall():
	ATarget("BrickWall Practice") {}

BrickWall::~BrickWall() {}

ATarget *BrickWall::clone(void) const 
{
	return (new BrickWall(*this));
}

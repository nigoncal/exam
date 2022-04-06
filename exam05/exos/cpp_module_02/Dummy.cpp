/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dummy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigoncal <nigoncal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 23:16:30 by ncolomer          #+#    #+#             */
/*   Updated: 2022/04/06 13:37:58 by nigoncal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Dummy.hpp"

Dummy::Dummy():
	ATarget("Dummy Practice") {}

Dummy::~Dummy() {}

ATarget *Dummy::clone(void) const 
{
	return (new Dummy(*this));
}

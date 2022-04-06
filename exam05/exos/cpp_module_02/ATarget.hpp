/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigoncal <nigoncal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 23:06:18 by ncolomer          #+#    #+#             */
/*   Updated: 2022/04/06 13:40:45 by nigoncal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATARGET_HPP
# define ATARGET_HPP

# include <iostream>
# include <string>
# include "ASpell.hpp"

class ASpell;

class ATarget
{
protected:
	std::string type;
public:
	ATarget();
	ATarget(std::string const &type);
	ATarget(ATarget const &other);
	virtual ~ATarget();

	ATarget &operator=(ATarget const &other);

	std::string const &getType(void) const;

	void getHitBySpell(ASpell const &spell) const;

	virtual ATarget *clone(void) const = 0;
};


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigoncal <nigoncal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 23:06:00 by ncolomer          #+#    #+#             */
/*   Updated: 2022/04/06 13:40:28 by nigoncal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASPELL_HPP
# define ASPELL_HPP

# include "ATarget.hpp"
# include <iostream>
# include <string>

class ATarget;

class ASpell
{
protected:
	std::string name;
	std::string effects;
public:
	ASpell();
	ASpell(std::string const &name, std::string const &effects);
	ASpell(ASpell const &other);
	virtual ~ASpell();

	ASpell &operator=(ASpell const &other);

	std::string const &getName(void) const;
	std::string const &getEffects(void) const;

	void launch(ATarget const &target);

	virtual ASpell *clone(void) const = 0;
};

#endif

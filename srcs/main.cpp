/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:43:19 by nassuto           #+#    #+#             */
/*   Updated: 2026/02/22 17:24:26 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"
#include "../includes/Server.hpp"

int	main(int ac, char **av){
	if (ac != 3){
		std::cerr << "Error: nbr of args" << std::endl;
		return (1);
	}
	int port = strtod(av[1], NULL);
	Server serv(port, av[2]);
	try {
		serv.create_server();

	}
	catch (const std::exception &e){
		std::cerr << "ERROR:" << e.what() << std::endl;
	}
}

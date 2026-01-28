/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:32:13 by nkalkoul          #+#    #+#             */
/*   Updated: 2026/01/24 12:18:41 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/irc.hpp>

Server::Server(const Server &s){
	*this = s;
}

Server &Server::operator=(const Server &s){
	if (this != &s){
		this->_socket = s._socket;
	}
	return (*this);
} 

int Server::getSocket(void){
	return (_socket);
}

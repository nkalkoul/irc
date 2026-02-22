/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:26:42 by nkalkoul          #+#    #+#             */
/*   Updated: 2026/02/18 12:47:01 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "irc.hpp"
#include "Client.hpp"

class Server {

private:
	int _lsocket;
	int _port;
	int _epfd;
	std::string _password;
	struct sockaddr_in _saddr;
	std::map<int, Client> _clients;
	
public:
	Server(void){};
	Server(int port, std::string password);
	Server(const Server &s);
	~Server(void);
	Server &operator=(const Server &s);
	int 	getSocket(void);
	void	create_server(void);
	void	run(void);
	void	takeclient(void);
	int		handleclient(Client &client);
	int		check_commande(Client &client);
}; 

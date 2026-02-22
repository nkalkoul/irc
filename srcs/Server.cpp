/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:32:13 by nkalkoul          #+#    #+#             */
/*   Updated: 2026/02/22 17:25:32 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"
#include "../includes/Server.hpp"
#include "../includes/Client.hpp"
 

Server::Server(const Server &s){
	*this = s;
}

Server &Server::operator=(const Server &s){
	if (this != &s){
		this->_lsocket = s._lsocket;
		_port = s._port;
		_password = s._password;
		_saddr = s._saddr;
	}
	return (*this);
} 

Server::Server(int port, std::string password): _port(port), _password(password){
	memset(&_saddr, 0, sizeof(_saddr));
}

int Server::getSocket(void){
	return (_lsocket);
}

Server::~Server(void){
	close(_lsocket);
	_clients.clear();
}

void	Server::takeclient(void){
	socklen_t addrlen = sizeof(_saddr);
	struct epoll_event ev;
	while(true){
		int nfd = accept(_lsocket, (struct sockaddr *)&_saddr, &addrlen);
		if (nfd == -1)
		{
			if (errno == EAGAIN ||errno == EWOULDBLOCK)
				break;
			else {
				std::cerr << "accept failed" << std::endl;
				continue;
			}
		}
		if (fcntl(nfd, F_SETFL, O_NONBLOCK) == -1)
		{
			std::cerr << "fcntl new client failed" << std::endl;
			close(nfd);
			continue;
		}
		ev.events = EPOLLIN;
		ev.data.fd = nfd;
		if (epoll_ctl(_epfd, EPOLL_CTL_ADD, nfd, &ev) == -1)
		{
			std::cerr << "epoll ctl new client failed" << std::endl;
			close(nfd);
			continue;
		}
		_clients[nfd] = Client(nfd);
		std::cout << "connexion server client etablished !" << std::endl;
		
	}
}

int	Server::check_commande(Client &client){
	return 0;
}

int	Server::handleclient(Client &client){
	char buff[512];

	ssize_t i = recv(client.getfd(), &buff, 512, 0);
	if (i == -1){
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (true);
		else {
			std::cerr << "recv client failed" << std::endl;
			return (true);
		}
	}
	else if(i == 0) {
		return (false);
	}
	else {
		client.setbuffer(buff, i);
		std::string s = client.getbuffer();
		if (s.size() >= 2 && s[s.size() - 2] == '\r' && s[s.size() - 1] == '\n')
			return (check_commande(client));
	}
	return (true);
}

void	Server::run(void){
	struct epoll_event ev[1024];
	while(true) {
		int fds = epoll_wait(_epfd, ev, 1024, -1);
		if (fds == -1)
			continue;
		for (int i = 0; i < fds; i++){
			int fd = ev[i].data.fd;
			if (fd == _lsocket){
				takeclient();
				continue;
			}
			else {
				if (handleclient(_clients[fd]) == false){
					_clients.erase(fd);
					close(fd);
					epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, NULL);
					continue;
				}
			}
		}
	}
}

void	Server::create_server(void){
	_lsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_lsocket == -1)
		throw std::runtime_error("Selem ou bien salut socket it sur ces mots");

	int on = 1;
	if (setsockopt(_lsocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
		throw std::runtime_error("fct setsockopt failed");
	_saddr.sin_family = AF_INET;
	_saddr.sin_port = htons(_port);
	_saddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(_lsocket, (struct sockaddr *)&_saddr, sizeof(_saddr)) == -1)
		throw std::runtime_error("fct bind failed");

	if (listen(_lsocket, SOMAXCONN) == -1)
		throw std::runtime_error("fct listen failed");
	
	if (fcntl(_lsocket, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("fct fcntl failed");
	_epfd = epoll_create1(0);
	if (_epfd == -1)
		throw std::runtime_error("failed creation of epoll");
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = _lsocket;
	if (epoll_ctl(_epfd, EPOLL_CTL_ADD, _lsocket, &ev) == -1)
		throw std::runtime_error("add _lsocket of epoll failed");
	run();
}

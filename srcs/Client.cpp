/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:35:37 by nkalkoul          #+#    #+#             */
/*   Updated: 2026/02/18 14:35:44 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"
#include "../includes/Client.hpp"

Client::Client(void): _fd(-1){
    
}

Client::Client(int fd): _fd(fd){
    
}

Client::~Client(void){
    if (_fd >= 0)
        close(_fd);
}

Client &Client::operator=(const Client &c){
    if (this != &c){
        _fd = c._fd;
        _pass = c._pass;
        _nick = c._nick;
        _user = c._user;
        _registered = c._registered;
        _buffer = c._buffer;
    }
    return (*this);
}

Client::Client(const Client &c){
    *this = c;
}

int Client::getfd(void){
    return(_fd);
}

std::string Client::getpass(void){
    return (_pass);
}

std::string Client::getbuffer(void){
    return (_buffer);
}

void Client::setbuffer(char *s, ssize_t i){
    _buffer.append(s, i);
}
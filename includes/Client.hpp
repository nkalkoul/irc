/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:28:00 by nkalkoul          #+#    #+#             */
/*   Updated: 2026/02/18 14:42:46 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "irc.hpp"

class Client {

private:
    int _fd;
    std::string _pass;
    std::string _nick;
    std::string _user;
    bool _registered;
    std::string _buffer;
    
    public:
    Client(void);
    Client(int fd);
    Client(const Client &c);
    ~Client(void);
    Client &operator=(const Client &c);
    int getfd(void);
    std::string getpass(void);
    std::string getnick(void);
    std::string getuser(void);
    bool asregistered(void);
    std::string getbuffer(void);
    void setbuffer(char *s, ssize_t i);
};
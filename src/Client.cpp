/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recarlie <recarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:00:22 by frrusso           #+#    #+#             */
/*   Updated: 2023/04/13 12:25:40 by recarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>

Client::Client() : _socket(0), _isok(0), _bvn(1) {}

Client::Client(int _fd) : _socket(_fd), _isok(0), _bvn(1) {}

Client::Client(const Client &src)
{
	*this = src;
}

Client::~Client() {}

Client&		Client::operator=(Client const &rhs)
{
	_nickname = rhs._nickname;
	_username = rhs._username;
	_hostname = rhs._hostname;
	_host = rhs._host;
	_realname = rhs._realname;
	return (*this);
}

int			Client::getSocket(void)
{
	return (_socket);
}

std::string	Client::getMessage(void)
{
	return (_messageentrant);
}

std::string Client::getUsername(void)
{
	return (_username);
}

int			Client::isReady(void)
{
	return (_isok);
}

int			Client::isWelcomed(void)
{
	return (_bvn);
}

int			Client::getId(void)
{
	return (_id);
}

std::string	Client::getHostname(void)
{
	return (_hostname);
}

std::string	Client::getRealName(void)
{
	return (_realname);
}

std::string	Client::getNickname(void)
{
	return (_nickname);
}

void		Client::setId(int id)
{
	_id = id;
}

void		Client::setSocket(int socket)
{
	_socket = socket;
}

void		Client::setMessage(std::string	messageentrant)
{
	_messageentrant = messageentrant;
}

void		Client::setNickname(std::string nickname)
{
	_nickname = nickname;
}

void		Client::setUsername(std::string name)
{
	_username = name;
}

void		Client::setHostname(std::string name)
{
	_hostname = name;
}

void		Client::setHost(std::string name)
{
	_host = name;
}

void		Client::setRealName(std::string name)
{
	_realname = name;
}

void		Client::setOk(int ok)
{
	_isok = ok;
}

void		Client::setWelcomed(int bvn)
{
	_bvn = bvn;
}

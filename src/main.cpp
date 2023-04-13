/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recarlie <recarlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:01:31 by frrusso           #+#    #+#             */
/*   Updated: 2023/04/13 11:43:29 by recarlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

bool	isport(char *av)
{
	if (strlen(av) > 5)
		return (false);
	for (size_t i = 0; i < strlen(av); i++)
	{
		if (isdigit(av[i]) == false)
			return (false);
	}
	if (atoi(av) > MAX_TCP_PORT)
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << RED << "Usage: ./serverserv <port> <password>" << ENDL;
		return (0);
	}
	if (isport(av[1]) == false)
	{
		std::cerr << RED << "Port \"" << av[1] << "\" is not good." << ENDL;
		return (0);
	}

	Server	server;
	fd_set readfds;
	fd_set writefds;

	try
	{
		server.run();
		std::cout << GREEN << "✅ Socket created successfully." << ENDL;
		server.bind(atoi(av[1]));
		std::cout << GREEN << "✅ Socket binded successfully." << ENDL;
		server.listen();
		std::cout << GREEN << "✅ Server listening on 127.0.0.1:" <<
		server.getPort() << "." << ENDL;

		int			valread;
		std::string	buffer, name;

		while (42)
		{
			FD_ZERO(&readfds);
			FD_ZERO(&writefds);
			FD_SET(server.getSocketFd(), &readfds);
			FD_SET(server.getSocketFd(), &writefds);

			if (select(server.getHighestFd(&readfds, &writefds) + 1, &readfds, &writefds, NULL, NULL) < 0 && errno != EINTR)
				std::cerr << "select error" << std::endl;

			if (FD_ISSET(server.getSocketFd(), &readfds))
			{
				struct sockaddr_in address;
				int addrlen = sizeof(address);
				
				int new_socket = accept(
					server.getSocketFd(),
					reinterpret_cast<sockaddr*>(&address),
					reinterpret_cast<socklen_t*>(&addrlen)
				);
				if (new_socket < 0)
					throw "Failed to accept connection.";

				std::cout << CYAN << "✅ Connection accepted on FD " << new_socket << "." << ENDL;
				try
				{
					server.getClient(new_socket);
				}
				catch (const char *e)
				{
					Client *newClient = new Client(new_socket);
					server.addClient(newClient);
				}
			}

			for (size_t i = 0; i < server.getClients().size(); i++)
			{
				if (FD_ISSET(server.getClients().at(i)->getSocket(), &writefds))
					if (server.getClients().at(i)->isReady()
						&& server.getClients().at(i)->isWelcomed())
						server.welcome(server.getClients().at(i));
				if (FD_ISSET(server.getClients().at(i)->getSocket(), &readfds))
				{
					valread = read(
						server.getClients().at(i)->getSocket(),
						server.getBuffer(), 1024
					);
					if (valread == 0)
					{
						std::cerr << RED << "Client " << server.getClients().at(i)->getSocket() << " disconnected." << ENDL;
						close(server.getClients().at(i)->getSocket());
						server.removeClient(server.getClients().at(i));
					}
					else
					{
						server.getBuffer()[valread] = '\0';
						server.commandHandler(
							server.getBuffer(),
							server.getClients().at(i)
						);
					}
				}
			}
		}
	}
	catch(const char *e)
	{
		std::cerr << RED << e << ENDL;
		return (1);
	}
	return (0);
}

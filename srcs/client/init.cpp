#include "../../includes/client.hpp"

int	client::_newSocket()
{
	if ((this->_socket = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
	{
		perror("socket() failed");
		return (ERROR);
	}
	memset(&this->_addr, 0, sizeof(this->_addr));
	this->_addr.sin6_family = AF_INET6;
	memcpy(&this->_addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	this->_addr.sin6_port = htons(PORT);

	return (SUCCESS);
}

int	client::_handle_connection()
{
	if (connect(this->_socket, (struct sockaddr *)&this->_addr, sizeof(this->_addr)) < 0)
	{
		perror("connect() failed");
		return (ERROR);
	}

	return (SUCCESS);
}

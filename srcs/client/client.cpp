#include "../../includes/client.hpp"

client::client(void) : _socket(0)
{
	memset(&this->_socket, 0, sizeof(int));
	memset(&this->_addr, 0, sizeof(struct sockaddr_in6));
	memset(this->_resp, 0, (strlen(this->_resp) + 1) * sizeof(char));
	memset(this->_req, 0, (strlen(this->_req) + 1) * sizeof(char));
	this->_getKey();

	return ;
}

client::client(client const &src)
{
	*this = src;

	return ;
}

client::client(int const socket)
{
	memset(&this->_addr, 0, sizeof(struct sockaddr_in6));
	memset(this->_resp, 0, sizeof(this->_resp));
	memset(this->_req, 0, sizeof(this->_req));
	this->_socket = socket;
	this->_getKey();

	return ;
}

client::~client(void)
{
	memset(&this->_socket, 0, sizeof(int));
	memset(&this->_addr, 0, sizeof(struct sockaddr_in6));
	memset(this->_resp, 0, sizeof(this->_resp));
	memset(this->_req, 0, sizeof(this->_req));

	return ;
}

client	&client::operator=(client const &src)
{
	memset(&this->_socket, 0, sizeof(int));
	memset(&this->_addr, 0, sizeof(struct sockaddr_in6));
	memset(this->_resp, 0, sizeof(this->_resp));
	memset(this->_req, 0, sizeof(this->_req));

	this->_socket = src._socket;
	this->_addr = src._addr;

	strcpy(this->_resp, src._resp);
	strcpy(this->_req, src._req);

	return *this;
}

int client::runClient()
{
   	unsigned long	len;
	std::cout << BOLD << ">>> CONNECTED ON PORT [" << PORT << "]" << EOC << std::endl;

	this->_newSocket();
	this->_handle_connection();

	while (g_run)
	{
		this->_analyzeReq(&len);
		len = recv(this->_socket, this->_resp, sizeof(this->_resp), 0);
		if (!strcmp(this->_req, "ok"))
		{
			this->_decrypt();
			break;
		}
		memset(&this->_req, 0, sizeof(this->_req));
		std::cout << "[C] " << this->_resp << std::endl;
		this->_analyzeResp(len);
	}
	close(this->_socket);

	return (SUCCESS);
}

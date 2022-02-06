#include "../../includes/client.hpp"

client::client(void) : _socket(0)
{
	std::ifstream	k(".key");
	std::string		line;
	memset(&this->_socket, 0, sizeof(int));
	memset(&this->_addr, 0, sizeof(struct sockaddr_in6));
	memset(&this->_req, 0, sizeof(char));
	memset(&this->_resp, 0, sizeof(char));
	memset(this->_resp, 0, strlen(this->_resp));
	memset(this->_req, 0, strlen(this->_req));
	this->_fileSize = 0;

	while (getline(k, line))
		this->_key = line;
	k.close();

	return ;
}

client::client(client const &src)
{
	*this = src;

	return ;
}

client::client(int socket)
{
	std::ifstream	k(".key");
	std::string		line;
	memset(&this->_addr, 0, sizeof(struct sockaddr_in6));
	memset(&this->_req, 0, sizeof(char));
	memset(&this->_resp, 0, sizeof(char));
	memset(this->_resp, 0, strlen(this->_resp));
	memset(this->_req, 0, strlen(this->_req));
	this->_fileSize = 0;
	this->_socket = socket;

	while (getline(k, line))
		this->_key = line;
	k.close();

	return ;
}

client::~client(void)
{
	memset(&this->_socket, 0, sizeof(int));
	memset(&this->_addr, 0, sizeof(struct sockaddr_in6));
	memset(&this->_req, 0, sizeof(char));
	memset(&this->_resp, 0, sizeof(char));

	return ;
}

client	&client::operator=(client const &src)
{
	memset(&this->_socket, 0, sizeof(int));
	memset(&this->_addr, 0, sizeof(struct sockaddr_in6));
	memset(&this->_req, 0, sizeof(char));
	memset(&this->_resp, 0, sizeof(char));

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
		len = recv(this->_socket, this->_resp, sizeof(this->_resp) + 1, 0);
		if (!this->_completed && !strcmp(this->_req, "ok"))
		{
			this->_writeFile(len);
			break;
		}
		memset(&this->_req, 0, (strlen(this->_req) + 1) * sizeof(char));
		std::cout << this->_resp << std::endl;
		this->_analyzeResp(len);
	}
	close(this->_socket);

	return (SUCCESS);
}

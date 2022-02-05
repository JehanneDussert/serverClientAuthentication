#include "../../includes/client.hpp"

client::client(void) : _socket(0)
{
	memset(&this->_socket, 0, sizeof(int));
	memset(&this->_addr, 0, sizeof(struct sockaddr_in6));
	memset(&this->_req, 0, sizeof(char));
	memset(&this->_resp, 0, sizeof(char));
	this->_fileSize = 0;

	return ;
}

client::client(client const &src)
{
	*this = src;

	return ;
}

client::client(int socket)
{
	this->_socket = socket;

	memset(&this->_addr, 0, sizeof(struct sockaddr_in6));
	memset(&this->_req, 0, sizeof(char));
	memset(&this->_resp, 0, sizeof(char));
	this->_fileSize = 0;

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

int client::runClient()
{
   unsigned long	len;
   int				toRecv = 0;

	std::cout << BOLD << ">>> CONNECTED ON PORT [" << PORT << "]" << EOC << std::endl;

	this->_newSocket();
	this->_handle_connection();
	while (g_run)
	{
		std::cout << "run\n";
		len = send(this->_socket, this->_req, strlen(this->_req) + 1, 0);
		if (len != strlen(this->_req) + 1)
		{
			perror("send");
			close(this->_socket);
			exit(-1);
		}
		if (!this->_fileSize)
			len = recv(this->_socket, this->_resp, sizeof(this->_resp) + 1, 0);
		std::cout << "recv :" << sizeof(this->_resp) << std::endl;
		if (!this->_fileSize && !this->_completed && !strcmp(this->_req, "ok"))
		{
			std::cout << "atoi\n";
			this->_fileSize = atoi(this->_resp);
			toRecv = this->_fileSize;
		}
		else if (this->_fileSize)
		{
			std::cout << "Going to write\n";
			this->_writeFile();
			this->_completed = TRUE;
			break;
		}
		// std::cout << "resp: " << this->_resp << std::endl;
		memset(&this->_req, 0, (strlen(this->_req) + 1) * sizeof(char));
		std::cout << this->_resp << std::endl;
		if (!strcmp(this->_resp, "Wait..."))
			sleep(2);
		else if (!strcmp(this->_resp, "🔑 Password: "))
			std::cin >> this->_req;
		else if (this->_fileSize || (!this->_completed && !strcmp(this->_resp, "🔓 Success: valid key")))
		{
			std::cout << "ok\n";
			strcpy(this->_req, "ok");
		}
		std::cout << "resp: " << this->_resp << std::endl;
		if (!this->_fileSize && len != strlen(this->_resp) + 1)
		{
			std::cout << "Len: " << this->_fileSize << " " << len << std::endl;
			perror("recv");
			close(this->_socket);
			exit(-1);
		}
		memset(&this->_resp, 0, (strlen(this->_resp) + 1) * sizeof(char));
	}
	close(this->_socket);
	return (SUCCESS);
}

#include "../../includes/client.hpp"

client::client(void) : _socket(0)
{
	memset(&this->_socket, 0, sizeof(int));
	memset(&this->_addr, 0, sizeof(struct sockaddr_in6));
	memset(&this->_req, 0, sizeof(char));
	memset(&this->_resp, 0, sizeof(char));
	this->_fileSize = 0;
	std::ifstream	k(".key");
	std::string		line;

	memset(this->_resp, 0, strlen(this->_resp));
	memset(this->_req, 0, strlen(this->_req));

	while (getline(k, line))
		this->_key = line;
	// k.close();

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
	std::ifstream	k(".key");
	std::string		line;

	memset(this->_resp, 0, strlen(this->_resp));
	memset(this->_req, 0, strlen(this->_req));

	while (getline(k, line))
		this->_key = line;
	// k.close();

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

	std::cout << BOLD << ">>> CONNECTED ON PORT [" << PORT << "]" << EOC << std::endl;

	this->_newSocket();
	this->_handle_connection();
	while (g_run)
	{
		len = send(this->_socket, this->_req, strlen(this->_req) + 1, 0);
		if (len != strlen(this->_req) + 1)
		{
			perror("send");
			close(this->_socket);
			exit(-1);
		}
		if (this->_completed)
			break;
		// std::cout << "recv: " << this->_resp << " | " << len << std::endl;
		len = recv(this->_socket, this->_resp, sizeof(this->_resp) + 1, 0);
		if (!this->_completed && !strcmp(this->_req, "ok"))
		{
			this->_fileSize = len;
			this->_writeFile();
			this->_completed = TRUE;
			std::cout << "Download completed" << std::endl;
			break;
		}
		memset(&this->_req, 0, (strlen(this->_req) + 1) * sizeof(char));
		std::cout << this->_resp << std::endl;
		if (!strcmp(this->_resp, "Wait..."))
		{
			sleep(1);
		}
		else if (!strcmp(this->_resp, "🔑 Password: "))
		{
			strcpy(this->_req, this->_key.c_str());
		}
		else if (this->_fileSize || (!this->_completed && !strcmp(this->_resp, "🔓 Success: valid key")))
		{
			strcpy(this->_req, "ok");
		}
		if (!this->_fileSize && len != strlen(this->_resp) + 1 && strcmp(this->_resp, "Wait..."))
		{
			perror("recv");
			close(this->_socket);
			exit(-1);
		}
		memset(&this->_resp, 0, (strlen(this->_resp) + 1) * sizeof(char));
	}
	close(this->_socket);
	return (SUCCESS);
}

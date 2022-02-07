#include "../../includes/client.hpp"

void	client::_analyzeResp(unsigned long const len)
{
	std::string k;
	if (!strcmp(this->_resp, "Wait..."))
	{
		sleep(1);
	}
	else if (!strcmp(this->_resp, "🔑 Password: "))
	{
		std::cin >> k;
		strcpy(this->_req, k.c_str());
		// strcpy(this->_req, (std::to_string(this->_key)).c_str());
	}
	else if (!strcmp(this->_resp, "🔓 Success: valid key"))
	{
		strcpy(this->_req, "ok");
	}
	if (len != strlen(this->_resp) + 1 && strcmp(this->_resp, "Wait..."))
	{
		perror("recv");
		close(this->_socket);
		exit(-1);
	}
	memset(&this->_resp, 0, sizeof(this->_resp));

	return ;
}

void	client::_analyzeReq(unsigned long *len)
{
	*len = send(this->_socket, this->_req, strlen(this->_req) + 1, 0);

	if (*len != strlen(this->_req) + 1)
	{
		perror("send");
		close(this->_socket);
		exit(-1);
	}

	return ;
}

#include "../../includes/server.hpp"

server::server(void)
{
	memset(this->_resp, 0, sizeof(this->_resp));
	memset(this->_req, 0, sizeof(this->_req));

	this->_opt = TRUE;
	this->_nbClients = 0;
	this->_minClients = 0;
	this->_completed = FALSE;
	this->_connected = 0;
	this->_recv = 0;

	return ;
}

server::server(server const &src)
{
   *this = src;

   return ;
}

server  &server::operator=(server const &src)
{
   if (this == &src)
      return *this;

	this->_cnct.clear();
	memset(this->_resp, 0, sizeof(this->_resp));
	memset(this->_req, 0, sizeof(this->_req));

	this->_cnct = src._cnct;
	this->_opt = src._opt;
	this->_nbClients = src._nbClients;
	this->_minClients = src._minClients;
    this->_listen_sd = src._listen_sd;
    this->_max_sd = src._max_sd;
	this->_new_sd = src._new_sd;
    this->_addr = src._addr;
    this->_master_set = src._master_set;
    this->_working_set = src._working_set;
    this->_closeConct = src._closeConct;
    this->_key = src._key;
	this->_recv = src._recv;

	strcpy(this->_resp, src._req);
	strcpy(this->_resp, src._resp);

   return *this;
}

server::server(const int n)
{
	memset(this->_resp, 0, sizeof(this->_resp));
	memset(this->_req, 0, sizeof(this->_req));
	this->_getKey();
	this->_opt = TRUE;
	this->_nbClients = 0;
	this->_minClients = n;
	this->_completed = FALSE;
	this->_connected = 0;
	this->_recv = 0;

	return ;
}

server::~server(void)
{
	this->_cnct.clear();
	memset(this->_resp, 0, sizeof(this->_resp));
	memset(this->_req, 0, sizeof(this->_req));
	return ;
}

int	server::runServer()
{
	int					desc_ready;
	struct timeval		timeout;

	this->_initSocket();
	timeout.tv_sec  = 30;
	timeout.tv_usec = 0;
   	while (g_run)
   	{
    	memcpy(&this->_working_set, &this->_master_set, sizeof(this->_master_set));
      	std::cout << BOLD << ">>> SERVER IS LISTENING ON PORT [" << PORT << "]" << EOC << std::endl;
		if ((desc_ready = this->_checkSelect(&timeout)) <= 0)
			break;
		for (int i = 0; i <= this->_max_sd && desc_ready > 0; ++i)
		{
			if (FD_ISSET(i, &this->_working_set))
			{
				desc_ready -= 1;
				if (i == this->_listen_sd)
				{
					if (!this->_newClient())
						break ;
				}
				else
				{
					this->_closeConct = FALSE;
					this->_getRequest(i);
					this->_sendResponse(i);
					if (this->_closeConct)
					{
						this->_closeConnection(i);
					}
				}
			}
		}
   	}
   	this->_closeSockets();

	return (SUCCESS);
}

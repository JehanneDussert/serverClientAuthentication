#include "../../includes/server.hpp"

int	server::_checkSelect(struct timeval *time)
{
	int ret = select(this->_max_sd + 1, &this->_working_set, NULL, NULL, time);
	
	if (ret < 0)
		perror("error: select.");
	else if (ret == 0)
		perror("select timed out.");

	return ret;
}

bool	server::_newClient()
{
   do
   {
      this->_new_sd = accept(this->_listen_sd, NULL, NULL);
      this->_cnct.push_back(FALSE);
      if (this->_new_sd < 0)
      {
         if (errno != EWOULDBLOCK)
         {
            perror("accept() failed");
            g_run = FALSE;
         }
         return (FALSE);
      }
      std::cout << "[+] New connection" << std::endl;
      this->_nbClients++;
      FD_SET(this->_new_sd, &this->_master_set);
      if (this->_new_sd > this->_max_sd)
         this->_max_sd = this->_new_sd;
      std::cout << "[+] Number of clients: " << this->_nbClients << std::endl;
   } while (this->_new_sd != -1);

	return (SUCCESS);
}

int	server::_initSocket()
{
	int rc;
   this->_listen_sd = socket(AF_INET6, SOCK_STREAM, 0);

   if (this->_listen_sd < 0)
   {
      perror("socket() failed");
      exit(-1);
   }
   rc = setsockopt(this->_listen_sd, SOL_SOCKET,  SO_REUSEADDR, (char *)&this->_opt, sizeof(this->_opt));
   if (rc < 0)
   {
      perror("setsockopt() failed");
      close(this->_listen_sd);
      exit(-1);
   }
   rc = ioctl(this->_listen_sd, FIONBIO, (char *)&this->_opt);
   if (rc < 0)
   {
      perror("ioctl() failed");
      close(this->_listen_sd);
      exit(-1);
   }
   memset(&this->_addr, 0, sizeof(this->_addr));
   this->_addr.sin6_family = AF_INET6;
   memcpy(&this->_addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
   this->_addr.sin6_port = htons(PORT);
   rc = bind(this->_listen_sd, (struct sockaddr *)&this->_addr, sizeof(this->_addr));
   if (rc < 0)
   {
      perror("bind() failed");
      close(this->_listen_sd);
      exit(-1);
   }
   rc = listen(this->_listen_sd, 32);
   if (rc < 0)
   {
      perror("listen() failed");
      close(this->_listen_sd);
      exit(-1);
   }
   FD_ZERO(&this->_master_set);
   this->_max_sd = this->_listen_sd;
   FD_SET(this->_listen_sd, &this->_master_set);

	return (SUCCESS);
}

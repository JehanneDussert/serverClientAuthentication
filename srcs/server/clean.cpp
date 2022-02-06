#include "../../includes/server.hpp"

void	server::_rmClient(int i)
{
   if (!this->_cnct[i])
   {
      this->_nbClients--;
   }
}

void  server::_closeConnection(int i)
{
   close(i);
   FD_CLR(i, &this->_master_set);
   if (i == this->_max_sd)
   {
      while (FD_ISSET(this->_max_sd, &this->_master_set) == FALSE)
         this->_max_sd -= 1;
   }
}

void    server::_closeSockets()
{
   for (int i = 0; i <= this->_max_sd; ++i)
   {
      if (FD_ISSET(i, &this->_master_set))
         close(i);
   }
}

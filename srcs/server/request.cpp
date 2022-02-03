#include "../../includes/server.hpp"

bool  server::getRequest(int i)
{
   int rc, len;

   rc = recv(i, this->_req, sizeof(this->_req), 0);
   std::cout << "Server recv: " << this->_req << std::endl;
   if (rc < 0)
   {
      if (errno != EWOULDBLOCK)
      {
         perror("recv() failed");
         this->_closeConct = TRUE;
      }
      return (FALSE);
   }
   if (rc == 0)
   {
      rmClient();
      this->_closeConct = TRUE;
      return (FALSE);
   }
   if (!strcmp(this->_req, this->_key.c_str()))
   {
      strcpy(this->_resp, "🔓 Success: valid key\n");
      this->_cnct[i] = 1;
      this->_connectedClients++;
      }
   else if (strlen(this->_req) && strcmp(this->_req, this->_key.c_str()))
   {
      strcpy(this->_resp, "🔐 Error: invalid key\n");
   }
   // if (this->_connectedClients >= this->_minClients && this->_cnct[i] == 1)
   // {
   //    strcpy(this->_resp, "🔓 Ready to send file\n");        
   //    this->_cnct[i] = 2;
   //    memset(&this->_req, 0, strlen(this->_resp) * sizeof(char));
   //    // exit(0);
   //    // send
   // }
   memset(&this->_req, 0, strlen(this->_req) * sizeof(char));
   len = rc;
   std::cout << "Number of bytes received: " << len << std::endl;

   return (TRUE);
}

bool  server::sendResponse(int i)
{
   std::cout << ">> SEND RESPONSE <<" << std::endl;
   int rc = send(i, this->_resp, strlen(this->_resp) + 1, 0);

   if (rc < 0)
   {
      perror("  send() failed");
      this->_closeConct = TRUE;
      return (FALSE);
   }
   memset(&this->_resp, 0, strlen(this->_resp) * sizeof(char));
   if (this->_cnct[i])
      std::cout << "File will be sent\n";
   return (TRUE);
}
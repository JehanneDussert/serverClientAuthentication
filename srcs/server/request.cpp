#include "../../includes/server.hpp"

bool  server::_getRequest(int i)
{
   int rc, len;

   rc = recv(i, this->_req, sizeof(this->_req), 0);
   if (strlen(this->_req))
      std::cout << "[+] Request: " << this->_req << std::endl;
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
      this->_rmClient(i);
      this->_closeConct = TRUE;
      return (FALSE);
   }
   if (!strcmp(this->_req, "ok"))
   {
      this->_sendFile();
      // std::cout << "file: " << this->_resp << std::endl;
      this->_completed = TRUE;
   }
   else if (!this->_completed && !this->_cnct[i] && !strcmp(this->_req, this->_key.c_str()))
   {
      std::cout << "len: " << strlen(this->_req) << std::endl;
      strcpy(this->_resp, "🔓 Success: valid key");
      this->_cnct[i] = TRUE;
      this->_connectedClients++;
   }
   else if (!strlen(this->_req) && this->_nbClients >= this->_minClients)
   {
      strcpy(this->_resp, "\n🔑 Password: ");
   }
   else if (strlen(this->_req) && strcmp(this->_req, this->_key.c_str()))
   {
      std::cout << "len: " << strlen(this->_req) << std::endl;
      strcpy(this->_resp, "🔐 Error: invalid key\n");
   }
   else if (this->_nbClients < this->_minClients)
   {
      strcpy(this->_resp, "Wait...");
   }
   memset(&this->_req, 0, (strlen(this->_req) + 1) * sizeof(char));
   len = rc;
   // std::cout << "Number of bytes received: " << len << std::endl;

   return (TRUE);
}

bool  server::_sendResponse(int i)
{
   if (this->_completed)
   {
      this->_nbClients--;
      this->_connectedClients--;
      this->_cnct[i] = FALSE;
      std::cout<<"[+] File transfer completed" << std::endl;
   }
   std::cout << ">> SEND RESPONSE <<" << std::endl;
   int rc = 0;
   rc = send(i, this->_resp, strlen(this->_resp) + 1, 0);

   if (rc < 0)
   {
      perror("  send() failed");
      this->_closeConct = TRUE;
      return (FALSE);
   }
   memset(&this->_resp, 0, (strlen(this->_resp) + 1) * sizeof(char));
   if (this->_cnct[i])
   {
      std::cout << "[+] Client " << i << " is now connected" << std::endl;
   }
   return (TRUE);
}

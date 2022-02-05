#include "../../includes/server.hpp"

bool  server::_getRequest(int i)
{
   int rc, len;

   rc = recv(i, this->_req, sizeof(this->_req), 0);
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
   std::cout << "req: " << this->_req << std::endl;
   std::cout << "[+] Request received | " << strlen(this->_req) << " bytes" << std::endl;
   if (!strcmp(this->_req, "ok") && !this->_fileSize)
   {
      this->_getFileSize();
      // std::cout << "file: " << this->_resp << std::endl;
   }
   else if (!strcmp(this->_req, "ok") && this->_fileSize)
   {
      std::cout << "Going to send\n";
      this->_sendFile();
      this->_completed = TRUE;
   }
   else if (!this->_completed && !this->_cnct[i] && !strcmp(this->_req, this->_key.c_str()))
   {
      strcpy(this->_resp, "🔓 Success: valid key");
      this->_cnct[i] = TRUE;
      this->_connectedClients++;
   }
   else if (!strlen(this->_req) && this->_nbClients >= this->_minClients)
   {
      strcpy(this->_resp, "🔑 Password: ");
   }
   else if (strlen(this->_req) && strcmp(this->_req, this->_key.c_str()))
   {
      strcpy(this->_resp, "🔐 Error: invalid key");
   }
   else if (this->_nbClients < this->_minClients)
   {
      strcpy(this->_resp, "Wait...");
   }
   memset(&this->_req, 0, (strlen(this->_req) + 1) * sizeof(char));
   len = rc;

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
   int rc = 0;
   int len = 0;
   this->_fileSize ? len = this->_fileSize : len = strlen(this->_resp);
   rc = send(i, this->_resp, len + 1, 0);
   std::cout << "[+] Response sent" << std::endl;
   // if (this->_fileSize)
   //    exit(0);
   // this->_fileSize = 0;

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

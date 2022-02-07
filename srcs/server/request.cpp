#include "../../includes/server.hpp"

void  server::_analyzeReq(int const i)
{
   if (this->_cnct[i])
   {
      this->_encrypt(i);
   }
   else if (!this->_completed && !strcmp(this->_req, (std::to_string(this->_key)).c_str()))
   {
      strcpy(this->_resp, "🔓 Success: valid key");
      this->_cnct[i] = TRUE;
   }
   else if (!strlen(this->_req) && this->_nbClients >= this->_minClients)
   {
      strcpy(this->_resp, "🔑 Password: ");
   }
   else if (strlen(this->_req) && strcmp(this->_req, (std::to_string(this->_key)).c_str()))
   {
      strcpy(this->_resp, "🔐 Error: invalid key");
   }
   else if (this->_nbClients < this->_minClients)
   {
      strcpy(this->_resp, "Wait...");
      sleep(1);
   }

   return ;
}

bool  server::_getRequest(int i)
{
   int   rc;
   int   len;

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
      this->_closeConct = TRUE;
      return (FALSE);
   }
   std::cout << "[S] Request received | " << strlen(this->_req) << " bytes" << std::endl;
   this->_analyzeReq(i);
   memset(&this->_req, 0, sizeof(this->_req));
   len = rc;

   return (TRUE);
}

bool  server::_sendResponse(int i)
{
   int rc = 0;
   int len = 0;
   
   if (this->_completed)
   {
      std::cout<<"[S] File transfer completed" << std::endl;
   }
   len = strlen(this->_resp);
   rc = send(i, this->_resp, len + 1, 0);
   std::cout << "[S] Response sent" << std::endl;
   if (rc < 0)
   {
      perror("  send() failed");
      this->_closeConct = TRUE;
      return (FALSE);
   }
   memset(&this->_resp, 0, sizeof(this->_resp));
   if (this->_cnct[i])
   {
      std::cout << "[S] Client " << i << " is connected" << std::endl;
   }
   return (TRUE);
}

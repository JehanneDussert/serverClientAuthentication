#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "common.hpp"

class   client
{
    private:
        int					_socket;
        bool                _connected;
        int                  _key;
        struct sockaddr_in6 _addr;
		char				_req[1024];
		char				_resp[1024];
        int                 _newSocket();
        int                 _handle_connection();
        void                _getSize(const std::string& address);
        void                _analyzeResp(unsigned long const len);
        void                _analyzeReq(unsigned long *len);
        void                _getKey();
        void                _decrypt();
    public:
        client();
        client(int const socket);
        client(client const &src);
        ~client();
        client      &operator=(client const &src);
        int         runClient();
};

#endif

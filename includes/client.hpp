#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "common.hpp"

class   client
{
    private:
        int					_socket;
        std::string         _key;
        struct sockaddr_in6 _addr;
		char				_req[1024];
		char				_resp[1024];
        bool                _completed;
        int                 _fileSize;
        int                 _newSocket();
        int                 _handle_connection();
        int                 _writeFile(int const len);
        void                _getSize(const std::string& address);
        void                _analyzeResp(unsigned long const len);
        void                _analyzeReq(unsigned long *len);
    public:
        client();
        client(int socket);
        client(client const &src);
        ~client();
        client      &operator=(client const &src);
        int         runClient();
};

#endif
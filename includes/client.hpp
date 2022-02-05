#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "common.hpp"

class   client
{
    private:
        int					_socket;
        struct sockaddr_in6 _addr;
		char				_req[1024];
		char				_resp[1024];
        bool                _completed;
        int                 _newSocket();
        int                 _handle_connection();
        int                 _writeFile();
        int                 _fileSize;
        void                _getSize(const std::string& address);
    public:
        client();
        client(int socket);
        client(client const &src);
        ~client();
        client      &operator=(client const &src);

        int         runClient();
};

# define FALSE 0
# define TRUE 1

#endif
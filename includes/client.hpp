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
    public:
        client();
        client(int socket);
        client(client const &src);
        ~client();
        client      &operator=(client const &src);

        int         runClient();
        int         newSocket();
        int         handle_connection();
        int         writeFile();
};

# define FALSE 0
# define TRUE 1

#endif
#ifndef SERVER_HPP
# define SERVER_HPP

# define SERVER_BACKLOG 100

# include "common.hpp"

class   server
{
    private:
        std::vector<bool>           _cnct;
        int                         _opt;
        unsigned long               _nbClients;
        unsigned long              	_minClients;
		unsigned long				_connectedClients;
        int                         _listen_sd;
        int                         _max_sd;
        int                         _new_sd;
        struct sockaddr_in6          _addr;			// look diff with in
        struct fd_set               _master_set;
        struct fd_set               _working_set;
        char                        _req[255];
        char                        _resp[255];
        bool                        _closeConct;
        std::string                 _key;

    public:
        server();
        server(const int n);
        server(server const &src);
        ~server();
        server  &operator=(server const &src);
		
        int     runServer();
        int	    initSocket();
        int	    checkSelect(struct timeval *time);
        void    rmClient();
        void    closeConnection(int i);
        void    closeSockets(void);
        bool    newClient();
        bool    getRequest(int i);
        bool    sendResponse(int i);
};

#endif
#ifndef SERVER_HPP
# define SERVER_HPP

# include "common.hpp"

class   server
{
    private:
        std::vector<bool>           _cnct;
        int                         _opt;
        unsigned long               _nbClients;
        unsigned long              	_minClients;
        int                         _listen_sd;
        int                         _max_sd;
        int                         _new_sd;
        struct sockaddr_in6         _addr;
        fd_set                      _master_set;
        fd_set						_working_set;
        char                        _req[1024];
        char                        _resp[1024];
        int                         _fileSize;
        bool                        _closeConct;
        int                          _key;
        bool                        _completed;
        int	                        _initSocket();
        int	                        _checkSelect(struct timeval *time);
        void    					_closeConnection(int i);
        void    					_closeSockets(void);
        bool    					_newClient();
        bool    					_getRequest(int i);
        void                        _analyzeReq(int const i);
        bool    					_sendResponse(int i);
        void                        _encrypt(int i);
        int                         _getKey();

    public:
        server();
        server(const int n);
        server(server const &src);
        ~server();
        server  &operator=(server const &src);
        int     runServer();
};

#endif

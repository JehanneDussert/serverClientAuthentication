#ifndef SERVER_HPP
# define SERVER_HPP

# include "common.hpp"

class   server
{
    private:
        std::vector<bool>           _cnct;
        int                         _opt;
        size_t                      _nbClients;
        size_t                    	_minClients;
        int                         _listen_sd;
		size_t						_connected;
        int                         _max_sd;
        int                         _new_sd;
        struct sockaddr_in6         _addr;
        fd_set                      _master_set;
        fd_set						_working_set;
        char                        _req[1024];
        char                        _resp[1024];
        bool                        _closeConct;
        int                         _key;
        bool                        _completed;
		size_t						_recv;
        int	                        _initSocket();
        int	                        _checkSelect(struct timeval *time);
        void    					_closeConnection(int i);
        void    					_closeSockets(void);
        bool    					_newClient();
        bool    					_getRequest(int i);
        void                        _analyzeReq(int const i);
        bool    					_sendResponse(int i);
        void                        _encrypt(int i);
        void                        _getKey();

    public:
        server();
        server(const int n);
        server(server const &src);
        ~server();
        server  &operator=(server const &src);
        int     runServer();
};

#endif

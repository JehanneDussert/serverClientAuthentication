#ifndef COMMON_HPP
# define COMMON_HPP

# include <stdio.h>
# include <map>
# include <sys/socket.h>
# include <stdlib.h>
# include <unistd.h>
# include <netinet/in.h>
# include <string.h>
# include <arpa/inet.h>
# include <iostream>
# include <sys/time.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ipc.h>
# include <sys/wait.h>
# include <fstream>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <vector>
# include <iterator>

# define EOC "\033[0m"
# define BOLD "\033[1;37m"
# define RED "\033[0;31m"
# define GREEN "\032[0;31m"
# define YELLOW "\133[0;31m"

# define PORT           8080
# define IP             "127.0.0.1"
# define TRUE	        1
# define FALSE          0
# define ERROR          -1
# define SUCCESS        0
# define PATH           "../files/encrypted"
# define SIZE           1024

static volatile int g_run = 1;

#endif
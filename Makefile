CLIENT_NAME = client
SERVER_NAME = server

CLIENT_PATH	= srcs/client/
SERVER_PATH = srcs/server/

CLIENT_FILES = main.cpp client.cpp recvFile.cpp init.cpp response.cpp
SERVER_FILES = main.cpp server.cpp clean.cpp request.cpp init.cpp \
				sendFile.cpp

CLIENT_SRCS = ${addprefix ${CLIENT_PATH}, ${CLIENT_FILES}}
SERVER_SRCS = ${addprefix ${SERVER_PATH}, ${SERVER_FILES}}

CLIENT_OBJECTS = $(CLIENT_SRCS:.cpp=.o)
SERVER_OBJECTS = $(SERVER_SRCS:.cpp=.o)

CXX = @clang++
CXXFLAGS += -Wall -Wextra -Werror -std=c++98

all : $(SERVER_NAME) $(CLIENT_NAME)
	@echo "\033[0;32mCompilation done\t✅\033[0m"

$(CLIENT_NAME) : $(CLIENT_OBJECTS)
	@echo "\033[0;32mBuidling client\t\t✅\033[0m"
	@${CXX} ${CXXFLAGS} -o ${CLIENT_NAME} $(CLIENT_OBJECTS)

$(SERVER_NAME) : $(SERVER_OBJECTS)
	@echo "\033[0;32mBuidling server\t\t✅\033[0m"
	@${CXX} ${CXXFLAGS} -o ${SERVER_NAME} $(SERVER_OBJECTS)

clean : 
	@/bin/rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS)

fclean : clean
	@/bin/rm -f $(SERVER_NAME) ${CLIENT_NAME}

re : fclean all
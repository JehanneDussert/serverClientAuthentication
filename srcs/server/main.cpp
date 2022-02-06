#include "../../includes/server.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "error: arguments. Please enter a minimum of clients." << std::endl;
		return (ERROR);
	}
	server	server(atoi(av[1]));
	server.runServer();

	return 0;
}

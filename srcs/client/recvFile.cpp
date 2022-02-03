#include "../../includes/client.hpp"

int     client::writeFile()
{
	int n;
	FILE *fp;
	const char *filename = "recv";
	char buffer[SIZE];
	std::string	buf;
	// std::cout << "buffer here: " << buf << std::endl;

	fp = fopen(filename, "w");
	while (1)
	{
		n = recv(this->_socket, buffer, SIZE, 0);
		buf += buffer;
		if (n <= 0)
		{
			break;
		}
		// decrypt here buffer
		fprintf(fp, "%s", buffer);
		memset(&buffer, 0, SIZE * sizeof(char));
	}
	std::cout << "buffer: " << buffer << std::endl;
	std::cout << "buf: " << buf << std::endl;

    return (SUCCESS);
}
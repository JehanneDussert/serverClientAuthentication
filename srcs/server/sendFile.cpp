#include "../../includes/server.hpp"

int server::getFile(FILE *f)
{
	char data[SIZE] = {0};
   std::string buf;

	while (fgets(data, SIZE, f) != NULL)
	{
      buf += data;
		bzero(data, SIZE);
	}

   strcpy(this->_resp, buf.c_str());
   buf.clear();

	return (SUCCESS);
}

int		server::sendFile()
{
	std::string		buf;
	FILE *f;

	// encrypt here
	const char *filename = "files/encrypted";
	f = fopen(filename, "r");
	if (f == NULL)
	{
		perror("file is null");
		return (ERROR);
	}
	if (getFile(f) == SUCCESS)
	{
			std::cout << "File sent to client" << std::endl;
   }
	return (SUCCESS);
}

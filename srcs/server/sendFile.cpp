#include "../../includes/server.hpp"
#include <iterator>
int		server::sendFile()
{
	std::string buf;
	std::ifstream input( "files/encrypted", std::ios::binary );
    // copies all data into buffer
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), (std::istreambuf_iterator<char>()));

	for (std::vector<unsigned char>::const_iterator it = buffer.begin(); it != buffer.end(); it++)
	{
		buf += *it;
	}
	// std::cout << "buf: " << buf << std::endl;
	strcpy(this->_resp, buf.c_str());
	std::cout << "resp: " << this->_resp << std::endl;
	buf.clear();
	std::cout<<"[SENDING FILE] File size: "<< strlen(this->_resp) <<" bytes." << std::endl;
	this->_completed = TRUE;
	this->_file = true;

	return (SUCCESS);
}

#include "../../includes/server.hpp"

int		server::_getFileSize()
{
	system("openssl enc -e -aes-256-cbc -in files/toEncrypt.txt -out files/encrypted -pass pass:.key");
	std::cout<<"[+] File has been encrypted" << std::endl;
	std::ifstream input("files/encrypted", std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), (std::istreambuf_iterator<char>()));

	this->_fileSize = buffer.size();
	strcpy(this->_resp, std::to_string(this->_fileSize).c_str());
	return (SUCCESS);
}

int		server::_sendFile()
{
	std::string buf;
	
    // copies all data into buffer
	std::ifstream input("files/encrypted", std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), (std::istreambuf_iterator<char>()));
	int i = 0;
	for (std::vector<unsigned char>::const_iterator it = buffer.begin(); it != buffer.end(); it++)
	{
		i++;
		buf += *it;
	}
	strcpy(this->_resp, buf.c_str());
	std::cout << "buf: " << buf << std::endl;
	std::cout << "this->_resp: " << this->_resp << std::endl;
	// std::cout << "resp: " << this->_resp << std::endl;
	buf.clear();
	std::cout<<"[+] File size: "<< i <<" bytes." << std::endl;
	this->_completed = TRUE;

	return (i);
}

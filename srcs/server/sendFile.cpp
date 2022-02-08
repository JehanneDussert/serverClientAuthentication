#include "../../includes/server.hpp"

void	server::_encrypt(int i)
{
 	std::ifstream	fin;
	std::ofstream	fout;
	std::string		buf;
	char			c;
	size_t			len = 0;
	
	fin.open("files/toEncrypt.txt", std::ifstream::in);
    fout.open("encrypted.bin", std::ofstream::out);

    while (fin >> std::noskipws >> c)
	{
        int tmp = (c + this->_key);
        fout << (char)tmp;
		buf += (char)tmp;
		len++;
		if (len > sizeof(this->_resp))
		{
			std::cerr << "[S] Error: file is too large. Maximum file size is 1024 bytes" << std::endl;
			fin.close();
			fout.close();
			this->_closeSockets();
			this->_closeConnection(i);
			exit(-1);
		}
    }
	strcpy(this->_resp, buf.c_str());
	std::cout << "[S] File encrypted" << std::endl;
    fin.close();
    fout.close();
	this->_cnct[i] = FALSE;
	this->_recv++;

	return ;
}

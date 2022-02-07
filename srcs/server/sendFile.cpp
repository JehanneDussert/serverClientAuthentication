#include "../../includes/server.hpp"

void	server::_encrypt(int i)
{
 	std::ifstream fin;
	std::ofstream fout;
	std::string buf;
	char c;
	(void)i;
	
	fin.open("files/toEncrypt.txt", std::ifstream::in);
    fout.open("encrypted.bin", std::ofstream::out);
    while (fin >> std::noskipws >> c)
	{
        int temp = (c + this->_key);
        fout << (char)temp;
		buf += (char)temp;
    }
	strcpy(this->_resp, buf.c_str());
	std::cout << "[S] File encrypted" << std::endl;
    fin.close();
    fout.close();
	this->_cnct[i] = FALSE;

	return ;
}

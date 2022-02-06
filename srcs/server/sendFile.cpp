#include "../../includes/server.hpp"

void	server::_encrypt()
{
 	std::fstream fin, fout;
	fin.open("files/toEncrypt.txt", std::fstream::in);
    fout.open("encrypt.bin", std::fstream::out);
	char c;
    while (fin >> std::noskipws >> c)
	{
        int temp = (c + this->_key);
        fout << (char)temp;
    }
    fin.close();
    fout.close();
}

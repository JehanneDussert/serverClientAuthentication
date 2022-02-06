#include "../../includes/server.hpp"

void	server::_encrypt(int i)
{
 	std::ifstream fin;
	 std::ofstream fout;
	fin.open("files/toEncrypt.txt", std::ifstream::in);
    fout.open("encrypted.bin", std::ofstream::out);
	char c;
	(void)i;
    while (fin >> std::noskipws >> c)
	{
        int temp = (c + this->_key);
        fout << (char)temp;
    }
	std::cout << "[S] File encrypted" << std::endl;
    fin.close();
    fout.close();
	this->_cnct[i] = FALSE;

	return ;
}

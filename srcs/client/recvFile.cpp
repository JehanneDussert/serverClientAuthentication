#include "../../includes/client.hpp"

void	client::_decrypt()
{
    std::fstream fin;
    std::fstream fout;
	char c;
    fin.open("encrypt.txt", std::fstream::in);
    fout.open("decrypt.txt", std::fstream::out);
 
    while (fin >> std::noskipws >> c)
	{
        int temp = (c - this->_key);
        fout << (char)temp;
    }
    fin.close();
    fout.close();
	std::cout << "📁 Download completed" << std::endl;
	this->_completed = TRUE;
	system("rm encrypt.bin");

	return ;
}

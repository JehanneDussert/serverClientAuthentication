#include "../../includes/client.hpp"

void	client::_decrypt()
{
	char			c;
    std::ifstream	recv;
    std::ofstream	decrypt;

    recv.open("encrypted.bin");
    decrypt.open("decrypt.txt");
    while (recv >> std::noskipws >> c)
	{
        int temp = (c - this->_key);
        decrypt << (char)temp;
    }
    recv.close();
    decrypt.close();
	std::cout << "[C] " << "✅ File decrypted" << std::endl;
	this->_completed = TRUE;
	// system("rm encrypted.bin");
	std::cout << "[C] " << "📁 Download completed" << std::endl;

	return ;
}

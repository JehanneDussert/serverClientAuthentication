#include "../../includes/client.hpp"

void	client::_decrypt()
{
    std::ofstream	decrypt;

    decrypt.open("decrypt.txt");

    if (!strlen(this->_resp))
    {
        return ;
    }
    for (size_t i = 0; i < strlen(this->_resp); i++)
	{
        int tmp = (this->_resp[i] - this->_key);
        decrypt << (char)tmp;
    }
    decrypt.close();
	std::cout << "[C] " << "✅ File decrypted" << std::endl;
	std::cout << "[C] " << "📁 Download completed" << std::endl;
}

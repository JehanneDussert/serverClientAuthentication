#include "../../includes/client.hpp"

void	client::_decrypt()
{
    std::ofstream	decrypt;

    decrypt.open("decrypt.txt");
    for (size_t i = 0; i < strlen(this->_resp); i++)
	{
        int temp = (this->_resp[i] - this->_key);
        decrypt << (char)temp;
    }
    decrypt.close();
	std::cout << "[C] " << "✅ File decrypted" << std::endl;
	this->_completed = TRUE;
	std::cout << "[C] " << "📁 Download completed" << std::endl;

	return ;
}

#include "../../includes/client.hpp"

int     client::_writeFile(int const len)
{
    std::string const file = "recv";
    std::ofstream f(file.c_str(), std::ios::binary);
    this->_fileSize = len;

    for (int i = 0; i < this->_fileSize; i++)
    {
        f.write(&(this->_resp)[i],sizeof((this->_resp)[i]));
    }
    f.close();

    system("openssl enc -d -aes-256-cbc -in recv -out decrypted.txt -pass pass:.key");
    system("rm recv");
	this->_completed = TRUE;
	std::cout << "📁 Download completed" << std::endl;

    return (SUCCESS);
}

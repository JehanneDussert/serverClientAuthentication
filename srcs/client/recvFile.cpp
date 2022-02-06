#include "../../includes/client.hpp"

int     client::_writeFile(int const len)
{
    std::string const file = "download/recv";
    std::ofstream f(file.c_str(), std::ios::binary);
    this->_fileSize = len;

    for (int i = 0; i < this->_fileSize; i++)
    {
        f.write(&(this->_resp)[i],sizeof((this->_resp)[i]));
    }
    f.close();

    system("openssl enc -d -aes-256-cbc -in download/recv -out download/decrypted.txt -pass pass:.key");
    system("rm download/recv");
	this->_completed = TRUE;
	std::cout << "Download completed" << std::endl;

    return (SUCCESS);
}

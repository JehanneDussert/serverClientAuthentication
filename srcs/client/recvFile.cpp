#include "../../includes/client.hpp"

int     client::_writeFile()
{
    std::string const file = "download/recv";// + std::to_string(this->_socket);
    //("files/recv");
    std::ofstream f(file.c_str(), std::ios::binary);
    
    for (int i = 0; i < this->_fileSize; i++)
    {
        f.write(&(this->_resp)[i],sizeof((this->_resp)[i]));
    }
    f.close();

    system("openssl enc -d -aes-256-cbc -in download/recv -out download/decrypted.txt -pass pass:.key");
    system("rm download/recv");

    return (SUCCESS);
}
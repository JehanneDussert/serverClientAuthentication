#include "../../includes/client.hpp"

int     client::_writeFile()
{
    // char    buf[this->_fileSize];
    // recv(this->_socket, buf, bytes_received, 0);
    std::string const file("files/recv");
    std::ofstream f(file.c_str(), std::ios::binary);
    
    for (int i = 0; i < this->_fileSize; i++)
    {
        f.write(&(this->_resp)[i],sizeof((this->_resp)[i]));
    }
    f.close();

    system("openssl enc -d -aes-256-cbc -in files/recv -out files/decrypted.txt -pass pass:.key");
    
    return (SUCCESS);
}
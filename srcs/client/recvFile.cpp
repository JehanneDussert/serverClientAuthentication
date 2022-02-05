#include "../../includes/client.hpp"

int     client::_writeFile()
{
	std::string const file("files/recv");
    std::ofstream f(file.c_str());

    if(f)    
    {
        f << this->_resp << std::endl;
		// std::cout << "resp: " << this->_resp << std::endl;
    }
    else
    {
        std::cout << "Error: file open." << std::endl;
    }
    return (SUCCESS);
}
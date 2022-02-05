#include "../../includes/client.hpp"

// void client::_getSize(const std::string& address)
// {
//     std::fstream input(address.c_str(), std::ios::binary | std::ios::in | std::ios::ate);
    
//     if (input)
//     {
//         std::fstream::pos_type size = input.tellg();
//         // this->_fileSize = size;
//     }
//     else
//     {
//         perror(address.c_str());
//     }

// }
#include <string>
#include <sstream>
int     client::_writeFile()
{
    int id = 1;
    std::stringstream ss2;
    int bytes_received;
    ss2 << id;
    std::ofstream img(ss2.str().c_str(), std::ios::binary);

// 1MB is a lot to put on the stack, use the heap instead
    std::vector<char> buff(1024*1024);
    do
    {
        bytes_received = recv(this->_socket, &buff[0], buff.size(), 0);
        if (bytes_received < 0)
            break; // ERROR!

        if (bytes_received == 0)
            break; // DISCONNECT!

        for (int i = 0; i < bytes_received; ++i)
            std::cout << buff[i];
        std::cout << std::endl;

        img.write(&buff[0], bytes_received);
        std::cout << "la\n";
        std::cout << "bytes: " << bytes_received << std::endl;
        if (bytes_received == this->_fileSize + 1)
            break;
        // TODO: if reached the end of the image, stop here
    } while (true);
    std::cout << "[+] File size: "<< this->_fileSize <<" bytes." << std::endl;
	std::string const file("files/recv");
    std::ofstream f(file.c_str(), std::ios::binary);
    std::string buf;
    int i = 0;
    if (f)    
    {
        for(std::vector<char>::iterator it = buff.begin(); it != buff.end(); it++)
            {
                buf += *it;
                i++;
                // std::cout << *it << std::endl;
            } 
            // std::cout << "resp: " << this->_resp << std::endl;
        }
        else
        {
            std::cout << "[-] Error: file open." << std::endl;
        }
	std::cout << "buf: " << buf << std::endl;
    f << buf;
	
    // std::ifstream bin(this->_resp, std::ios::binary);
    // std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(bin), (std::istreambuf_iterator<char>()));
    // std::string buf;

    // int i = 0;
	// for (std::vector<unsigned char>::const_iterator it = buffer.begin(); it != buffer.end(); it++)
	// {
	// 	i++;
	// 	buf += *it;
	// }
    // std::cout << "buf: " << buf << std::endl;
    // // this->_getSize(this->_resp);
    // // std::string buf;
	// // std::ifstream input(this->_resp, std::ios::binary|std::ios::in|std::ios::ate);
    // // // copies all data into buffer
    // // std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), (std::istreambuf_iterator<char>()));
	// // int i = 0;
	// // for (std::vector<unsigned char>::const_iterator it = buffer.begin(); it != buffer.end(); it++)
	// // {
    // //     std::cout << "i: " << i << std::endl;
	// // 	i++;
	// // 	buf += *it;
	// // }
    // // //std::cout << this->_resp << std::endl;
    // // std::string const file("files/recv");
    // // std::ofstream f(file.c_str());
    // // f << buf;
	// // std::cout << "buf: " << buf << std::endl;
	// // strcpy(this->_resp, buf.c_str());
	// // std::cout << "resp: " << this->_resp << std::endl;
	// // buf.clear();
	system("openssl enc -d -aes-256-cbc -in files/recv -out files/decrypted.txt -pass pass:.key");
    std::cout << "after openssl\n";
    exit (0);
    return (SUCCESS);
}
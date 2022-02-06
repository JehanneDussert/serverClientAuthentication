# Client-server authentication

The objective of this project is to create a server that requires clients to authenticate themselves through a shared key. Once a certain number of clients are connected, the server allows the download of an encrypted file.

<p align="center">
	<img src="./test/demo.gif" >
</p>

## ✅ Completed
- Server-client part
- Secret key generation with openSSL
- Checking client key once enough clients are connected
- Encrypted file: send + receive
- Tests: several clients, large files etc
- Script bash: test, clean, update

## 🔎 Server-client

IO Multiplexing: chose to work with select().
[Advantage] : Portable solution, adapted to MacOS and Linux unlike poll() and epoll().
[Disadvantage] : Less optimized than poll() and epoll().

I referred to the IBM documentation to build my server and client and to Jacob Sorber's Youtube channel.

At each loop turn, only one call to select() is made. Only one send() and recv() is performed by the server and the client.

All data and functions members of the server class and client class are in private except for the launch functions.

## 🔎 Client authentication

Key generator command: /dev/urandom.
[Advantage] : Easy to use.

The key is created when the run.sh script is launched and written in a .key file.

When the minimum number of connected clients is reached, the server asks the secret key to each of them and compares it with the key it holds in private variable.

If successful, the server proceeds to download the encrypted file.
In case of failure, the server will send an error message and ask for the secret key again.

## 🔎 Download encrypted file

Once encrypted, the file (files/encrypted) is sent by the server through a socket, the client receives it and writes it into a file.

Sending an encrypted file can be complex. To get around this problem, each encrypted character is inserted into a buffer which is a char vector.

I found most of the answers to my questions about sending and receiving encrypted files on Stackoverflow and Youtube.

Once written, the file is downloaded in files/ and named 'recv'.

## 💡 Usage

```
bash run.sh
./server [minClientsNeeded]
```

In an other terminal, run a client

```
./client
```

To clean:
```
bash run.sh clean
```

To test:
```
bash run.sh test
```

Update:
```
bash run.sh up
```

## 🖇 Reference
- [Sécurisez vos données avec la cryptographie](https://openclassrooms.com/fr/courses/1757741-securisez-vos-donnees-avec-la-cryptographie/6031691-decouvrez-la-cryptographie-moderne)
- [Linux – IO Multiplexing – Select vs Poll vs Epoll](https://devarea.com/linux-io-multiplexing-select-vs-poll-vs-epoll/#.Yf5wxGDjJKM)
- [Example: Nonblocking I/O and select()](https://www.ibm.com/docs/en/i/7.1?topic=designs-example-nonblocking-io-select)
- [Program your own web server in C. (sockets)](https://www.youtube.com/watch?v=esXw4bdaZkc&ab_channel=JacobSorber)
- [How to build a web client? (sockets)](https://www.youtube.com/watch?v=bdIiTxtMaKA&ab_channel=JacobSorber)
- [10 ways to generate a random password from the command line](https://www.howtogeek.com/howto/30184/10-ways-to-generate-a-random-password-from-the-command-line)
- [File Transfer using TCP Socket in C | Socket Programming](https://www.youtube.com/watch?v=7d7_G81uews&ab_channel=IdiotDeveloper)
- [How to read a binary file into a vector](https://stackoverflow.com/questions/15138353/how-to-read-a-binary-file-into-a-vector-of-unsigned-chars)
- [Reading and writing binary file](https://stackoverflow.com/questions/5420317/reading-and-writing-binary-file)
- [Determine the size of a binary file](https://stackoverflow.com/questions/13648066/determine-the-size-of-a-binary-file)

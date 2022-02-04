# Client-server authentication

The objective of this project is to create a server that requires clients to authenticate themselves through a shared key. Once a certain number of clients are connected, the server allows the download of an encrypted file.

## ✅ Completed ⤵️
- Server-client part
- Secret key generation with openSSL
- Checking client key when nc is called
- Encrypted file: send + receive

## 📈 To be completed ⤵️
- Decrypted file
- Improve script bash
- Tests: several clients, large files etc

<!-- ## 🔎 Server-client ⤵️ -->
<!-- ## 🔎 Client authentication ⤵️ -->
<!-- ## 🔎 Download encrypted file ⤵️ -->

## 💡 Usage

```
bash run.sh
./server [minClientsNeeded]
```

In an other terminal, run a client

```
./client
```


## 🖇 Reference
- [Sécurisez vos données avec la cryptographie](https://openclassrooms.com/fr/courses/1757741-securisez-vos-donnees-avec-la-cryptographie/6031691-decouvrez-la-cryptographie-moderne)
- [Example: Nonblocking I/O and select()](https://www.ibm.com/docs/en/i/7.1?topic=designs-example-nonblocking-io-select)
- [10 ways to generate a random password from the command line](https://www.howtogeek.com/howto/30184/10-ways-to-generate-a-random-password-from-the-command-line)
- [File Transfer using TCP Socket in C | Socket Programming](https://www.youtube.com/watch?v=7d7_G81uews&ab_channel=IdiotDeveloper)
- [How to read a binary file into a vector](https://stackoverflow.com/questions/34304570/how-to-resolve-the-evp-decryptfinal-ex-bad-decrypt-during-file-decryption/43847627)

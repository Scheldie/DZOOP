#include "file.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>  // Для вывода в HEX (удобно для отладки)
#include <iostream>
#include <cstdio>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iomanip>

using namespace std;
using namespace CryptoPP;

std::string encryptAES(const std::string& plaintext, const std::string& key, const std::string& iv) {
    std::string ciphertext;
    

    try {

        // Настройка шифрования
        CBC_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(
            reinterpret_cast<const CryptoPP::byte*>(key.data()),
            key.size(),
            reinterpret_cast<const CryptoPP::byte*>(iv.data())
        );

        // Шифрование
        StringSource ss(
            plaintext,
            true,
            new StreamTransformationFilter(
                encryptor,
                new StringSink(ciphertext)
            )
        );
    } 
    catch (const CryptoPP::Exception& e) {
       
    }

    return ciphertext;
}

std::string decryptAES(const std::string& ciphertext, const std::string& key, const std::string& iv) {
    std::string decryptedtext;

    try {
        CBC_Mode<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(
            reinterpret_cast<const CryptoPP::byte*>(key.data()),
            key.size(),
            reinterpret_cast<const CryptoPP::byte*>(iv.data())
        );

        StringSource ss(
            ciphertext,
            true,
            new StreamTransformationFilter(
                decryptor,
                new StringSink(decryptedtext))
        );
    } catch (const CryptoPP::Exception& e) {
        
        return "";
    }

    return decryptedtext;
}
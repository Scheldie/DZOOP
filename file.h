#pragma once
#include <string>

// Шифрует строку с помощью AES-256-CBC
std::string encryptAES(const std::string& plaintext, const std::string& key, const std::string& iv);

// Дешифрует строку из AES-256-CBC
std::string decryptAES(const std::string& ciphertext, const std::string& key, const std::string& iv);
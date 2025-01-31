#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/secblock.h>

namespace fs = std::filesystem;

void decryptFile(const std::string& encryptedFile, const std::string& outputFile, const std::string& keyString) {
    // Abrir o arquivo criptografado
    std::ifstream file(encryptedFile, std::ios::binary);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo criptografado: " << encryptedFile << std::endl;
        return;
    }

    std::vector<CryptoPP::byte> encryptedData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Preparar chave de descriptografia
    CryptoPP::SecByteBlock key(reinterpret_cast<const CryptoPP::byte*>(keyString.data()), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE] = {0};  // IV inicializado com zeros

    // Configurar o modo CTR
    CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption decryption;
    decryption.SetKeyWithIV(key, key.size(), iv);

    std::vector<CryptoPP::byte> decryptedData(encryptedData.size());
    CryptoPP::ArraySink sink(decryptedData.data(), decryptedData.size());

    CryptoPP::ArraySource(encryptedData.data(), encryptedData.size(), true,
        new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::Redirector(sink)));

    // Gravar o conteúdo descriptografado
    std::ofstream outputFileStream(outputFile, std::ios::binary);
    outputFileStream.write(reinterpret_cast<char*>(decryptedData.data()), decryptedData.size());
    outputFileStream.close();

    // Remover o arquivo criptografado
    fs::remove(encryptedFile);

    std::cout << "Arquivo descriptografado com sucesso: " << outputFile << std::endl;
}

int main() {
    std::string encryptedFile = "teste.txt.ransomwaretroll";
    std::string outputFile = "teste.txt";
    std::string key = "testeransomwares";

    decryptFile(encryptedFile, outputFile, key);

    return 0;
}


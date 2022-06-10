//
// Created by dongbo on 2022/4/12.
//

#include "x25519.h"
#include <cstring>
#include <experimental/filesystem>

using namespace CryptoPP;

namespace crypto_key {
    static std::string _SHA256(const std::string &message) {
        std::string digest;
        CryptoPP::SHA256 hash;

        CryptoPP::StringSource hasher(message,
                                      true,
                                      new CryptoPP::HashFilter(hash,
                                                               new CryptoPP::StringSink(digest),
                                                               false));

        return digest;
    }

    x25519::x25519(const std::string &path_) : _path(path_) {
    }


    int x25519::create_key(){
        CryptoPP::byte privateKey1[PUBLIC_KEYLENGTH];
        std::experimental::filesystem::create_directories(_path);

        CryptoPP::x25519 x1;

        x1.GeneratePrivateKey(prng, privateKey1);
        Integer intPrvK1(privateKey1, sizeof(privateKey1));
        std::cout << "Private key created " << intPrvK1 << std::endl;

        std::string file_name = _path+"/private.key.bin";
        std::fstream file(file_name,
                          std::ios_base::in | std::ios_base::out | std::ios_base::app | std::ios_base::binary);
        if (file.is_open()) {
            file << intPrvK1;
            std::cout << "Private key created: " << file_name << std::endl;
        }
        file.close();

        return 0;
    }


    int x25519::init_load_key_file() {
        std::string file_name = _path + "/private.key.bin";
        std::fstream file(file_name,
                          std::ios_base::in | std::ios_base::out | std::ios_base::app | std::ios_base::binary);

        std::string private_key;
        if (file.is_open()) {
            file >> private_key;
        }

        Integer int_private_key(private_key.c_str());
        int_private_key.Encode(_private_x25591_key, sizeof(_private_x25591_key));

        std::cout << "Private key load " << int_private_key << std::endl;

        file.close();
        return 0;
    }

    std::tuple<CryptoPP::byte(&)[32], bool> x25519::crypto_string(const std::string &message) {
        std::memset(message_input,0, sizeof(message_input));
        std::memcpy(message_input, message.c_str(),
                    message.length() < sizeof(message_input)? message.length() : sizeof (message_input));
        if (curve25519_mult(x25591_crypto, _private_x25591_key, message_input) == 0) {
            return std::make_tuple(std::ref(x25591_crypto), true);
        }

        return std::make_tuple(std::ref(x25591_crypto), false);
    }


    std::tuple<CryptoPP::byte(&)[32], bool> x25519::crypto_bytes(const CryptoPP::byte (&message)[32]) {
        std::memcpy(message_input, message, sizeof(message_input));

        if (curve25519_mult(x25591_crypto, _private_x25591_key, message_input) == 0) {
            return std::make_tuple(std::ref(x25591_crypto), true);
        }
        return std::make_tuple(std::ref(x25591_crypto), false);
    }


    std::string x25519::hash_right_shift(const std::string &message) {
        auto hash_string = _SHA256(message);

        return hash_string;
    }
}

//
// Created by dongbo on 2022/4/19.
//

#ifndef HTTPD__CRYPTO_H
#define HTTPD__CRYPTO_H

#include <iostream>
#include <tuple>
#include <cryptopp/cryptlib.h>


namespace crypto_key {
    class _crypto {
    public:

        virtual int init_load_key_file() = 0;

        virtual int create_key() = 0;

        virtual std::tuple<CryptoPP::byte(&)[32], bool> crypto_string(const std::string &message) = 0;

        virtual std::tuple<CryptoPP::byte(&)[32], bool> crypto_bytes(const CryptoPP::byte (&message)[32]) = 0;

        virtual std::string hash_right_shift(const std::string &message) = 0;

    private :

    };
}

#endif //HTTPD__CRYPTO_H

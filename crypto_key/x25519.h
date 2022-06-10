//
// Created by dongbo on 2022/4/12.
//

#ifndef HTTPD_X25519_H
#define HTTPD_X25519_H

#include <cryptopp/xed25519.h>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>

#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/hmac.h>
#include <cryptopp/donna.h>

#include "_crypto.h"

using CryptoPP::x25519;
using CryptoPP::Donna::curve25519_mult;
using CryptoPP::Donna::ed25519_sign;
using CryptoPP::Donna::ed25519_sign_open;
using CryptoPP::Donna::ed25519_publickey;


static const int PUBLIC_KEYLENGTH = 32;

namespace crypto_key {
    class x25519 : public _crypto {
    public:
        x25519(const std::string &path_);

        int init_load_key_file();

        int create_key();

        std::tuple<CryptoPP::byte(&)[32], bool> crypto_string(const std::string &message);

        std::tuple<CryptoPP::byte(&)[32], bool> crypto_bytes(const CryptoPP::byte (&message)[32]);

        std::string hash_right_shift(const std::string &message);

        std::string& path(){
            return _path;
        }

        const size_t x25591_crypto_size(){
            return  PUBLIC_KEYLENGTH;
        }

    private :
        std::string _path;
        CryptoPP::byte _private_x25591_key[PUBLIC_KEYLENGTH];
        CryptoPP::AutoSeededRandomPool prng;

    private:
        CryptoPP::byte message_input[PUBLIC_KEYLENGTH];
        CryptoPP::byte x25591_crypto[PUBLIC_KEYLENGTH];
    };

}


#endif //HTTPD_X25519_H

//
// Created by dongbo on 2022/6/9.
//

#ifndef DBREDIS_CC_X25519_H
#define DBREDIS_CC_X25519_H


#ifdef __cplusplus
extern "C"{
#endif
#include "cc_x25519.h"
#ifdef __cplusplus
}
#endif

#include "x25519.h"

static crypto_key::x25519 _x25519("/home/");

static int init_x25519(){
    static int init_ = 0;
    if(!init_){
//        _x25519.create_key();
        _x25519.init_load_key_file();
        init_=1;
    }

    return 0;
}


extern "C" int crypto_mul_x25519(const char * s, int len, char** crypto_result, int *crypto_len){
    init_x25519();
    auto hash_string =  _x25519.hash_right_shift(std::string(s,len));
    auto r = _x25519.crypto_string(std::string(s,len));

    *crypto_result = (char*)std::get<0>(r);
    *crypto_len = sizeof( std::get<0>(r));
    return 0;
}


extern "C" int re_crypto_mul_x25519(const char * s, int len, char** crypto_result, int *crypto_len){
    auto r = _x25519.crypto_string(std::string(s,len));

    *crypto_result = (char*)std::get<0>(r);
    *crypto_len = sizeof( std::get<0>(r));
    return 0;
}



#endif //DBREDIS_CC_X25519_H

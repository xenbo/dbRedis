//
// Created by dongbo on 2022/6/9.
//

#ifndef DBREDIS_CC_X25519_H
#define DBREDIS_CC_X25519_H

int crypto_mul_x25519(const char * s, int len, char** crypto_result, int *crypto_len);

int re_crypto_mul_x25519(const char * s, int len, char** crypto_result, int *crypto_len);

#endif //DBREDIS_CC_X25519_H

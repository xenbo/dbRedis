#include <iostream>
#include <chrono>
#include <vector>
#include <hiredis/hiredis.h>
#include <thread>
#include <atomic>

int main() {

    static std::atomic<std::chrono::system_clock::time_point*> start[100];
    static std::atomic<std::chrono::system_clock::time_point*> end[100];

    for(int t=1;t<=40;t++) {
        new std::thread([t](){
            struct timeval timeout = {2, 0};
            redisContext *redis_context = reinterpret_cast<redisContext *>(redisConnectWithTimeout("127.0.0.1", 6600+t, timeout));
            if (redis_context == nullptr) {
                std::cout << "no connection established." << std::endl;
                return 1;
            } else if (redis_context->err) {
                std::cout << "connection encounts errors: " << redis_context->errstr << std::endl;
                return 1;
            }

            int n_keys = 25000;
            int n_n =100;
            std::vector<std::vector<std::string>> vec_data;
            vec_data.resize(n_n);

            start[t] =  new std::chrono::system_clock::time_point (std::chrono::system_clock::now());

            {
                for (int n = 0; n < n_n; n++) {
                    {
                        for (int i = 0; i < n_keys; i++)
                            redisAppendCommand(redis_context, "crypto_mul key_%d %s", i + n * n_keys, "");
                    }

                    {
                        redisReply *redis_reply = nullptr;
                        for (int i = 0; i < n_keys; i++) {
                            redisGetReply(redis_context, reinterpret_cast<void **>(&redis_reply));
//                    std::cout << redis_reply->len << "," << redis_reply->str << std::endl;

                            vec_data[n].emplace_back(redis_reply->str, redis_reply->len);
                            redisAppendCommand(redis_context, "re_crypto_mul %b %s",  redis_reply->str,redis_reply->len, "");
                            freeReplyObject(redis_reply);
                        }
                    }

                    {
                        redisReply *redis_reply = nullptr;
                        for (int i = 0; i < n_keys; i++) {
                            redisGetReply(redis_context, reinterpret_cast<void **>(&redis_reply));
//                    std::cout << redis_reply->len << "," << redis_reply->str << std::endl;
                            freeReplyObject(redis_reply);
                        }

                    }
                }
            }
            end[t] =  new std::chrono::system_clock::time_point (std::chrono::system_clock::now());

            std::cout << "insert ok :" << std::chrono::duration_cast<std::chrono::seconds>(*end[t] - *start[t]).count() << std::endl;


//            {
//                static std::atomic<std::chrono::system_clock::time_point*> start1(  new std::chrono::system_clock::time_point (std::chrono::system_clock::now()));
//                for(int n=0;n< n_n ;n++) {
//                    {
//                        for (int i = 0; i < n_keys; i++) {
//                            redisAppendCommand(redis_context, "re_crypto_mul %b %s",vec_data[n][i].c_str(), vec_data[n][i].length(), "");
//                        }
//                    }
//
//                    {
//
//                        redisReply *redis_reply = nullptr;
//                        for (int i = 0; i < n_keys; i++) {
//                            redisGetReply(redis_context, reinterpret_cast<void **>(&redis_reply));
////                    std::cout << redis_reply->str <<std::endl;
//                            freeReplyObject(redis_reply);
//                        }
//                    }
//                }
//
//                static std::atomic<std::chrono::system_clock::time_point*> end1(  new std::chrono::system_clock::time_point (std::chrono::system_clock::now()));
//
//                std::cout << "find ok :" << std::chrono::duration_cast<std::chrono::seconds>(*end1 - *start1).count()
//                          << std::endl;
//
//            }

            redisFree(redis_context);
            return 0;
        });


    }

    std::this_thread::sleep_for(std::chrono::seconds(400000));

    return 0;
}

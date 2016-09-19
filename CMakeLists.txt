cmake_minimum_required (VERSION 2.6)
project (sftp)

include_directories(include)

add_executable(unit_test_encrypt src/security/unit_test/encrypt.cpp)

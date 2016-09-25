cmake_minimum_required (VERSION 2.6)
project (sftp)

include_directories(include)

#add_library(shared src/shared/Logger.cpp)
#target_link_libraries(shared somelib1 somelib2)




#add_library(include src/security/encrypt.cpp)

add_executable(unit_test_encrypt src/unit_test/security/encrypt.cpp)
add_executable(unit_test_diffiehellman src/unit_test/security/diffiehellman.cpp)



#add_executable(unit_test_encrypt src/security/unit_test/encrypt.cpp src/security/unit_test/hello.cpp)
#target_link_libraries(unit_test_encrypt shared)

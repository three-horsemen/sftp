cmake_minimum_required (VERSION 2.6)
project (sftp)
include_directories(include)

###Samples:
#add_library(shared src/shared/Logger.cpp)
#target_link_libraries(shared somelib1 somelib2)
#add_executable(unit_test_encrypt src/security/unit_test/encrypt.cpp src/security/unit_test/hello.cpp)
#target_link_libraries(unit_test_encrypt shared)
#add_library(include src/security/encrypt.cpp)


###Security module.
add_library(securityLibraryCollection
				src/security/cryptmath.cpp
				src/security/encrypt.cpp
				src/security/diffiehellman.cpp
				src/security/rsa.cpp
			)

add_executable(unit_test_encrypt src/unit_test/security/encrypt.cpp)
target_link_libraries(unit_test_encrypt securityLibraryCollection)

add_executable(unit_test_diffiehellman src/unit_test/security/diffiehellman.cpp)
target_link_libraries(unit_test_diffiehellman securityLibraryCollection)

add_executable(unit_test_rsa src/unit_test/security/rsa.cpp)
target_link_libraries(unit_test_rsa securityLibraryCollection)

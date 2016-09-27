cmake_minimum_required (VERSION 2.6)
project (sftp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package( Boost COMPONENTS log log_setup thread system REQUIRED )

include_directories(include ${Boost_INCLUDE_DIRS})

###Shared module
add_library(shared
	src/shared/logger.cpp
	)
target_link_libraries(shared ${Boost_LIBRARIES} pthread)

add_executable(unit_test_logger src/unit_test/shared/logger.cpp)
target_link_libraries(unit_test_logger shared)

###Security module
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

cmake_minimum_required (VERSION 2.6)
project (sftp)

###Samples:
#add_library(shared src/shared/Logger.cpp)
#target_link_libraries(shared somelib1 somelib2)
#add_executable(unit_test_encrypt src/security/unit_test/encrypt.cpp src/security/unit_test/hello.cpp)
#target_link_libraries(unit_test_encrypt shared)
#add_library(include src/security/encrypt.cpp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

add_compile_options(-std=c++11)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package( Boost 1.54 COMPONENTS log log_setup thread system REQUIRED )

include_directories(include ${Boost_INCLUDE_DIRS})

###Shared module
add_library(shared
	src/shared/logger.cpp
	src/shared/SignalHandler.cpp
	src/shared/InvalidSocketException.cpp
	src/shared/SocketIOException.cpp
	src/shared/SocketBufferEmptyException.cpp
	src/shared/SocketException.cpp
	)
target_link_libraries(shared ${Boost_LIBRARIES} pthread)

add_executable(unit_test_logger src/unit_test/shared/logger.cpp)
target_link_libraries(unit_test_logger shared)

###Security module
add_library(security
	src/security/encrypt.cpp
	src/security/diffiehellman.cpp
	src/security/SecureSocketManager.cpp
	)
target_link_libraries(security shared)


add_executable(unit_test_encrypt src/unit_test/security/encrypt.cpp)
target_link_libraries(unit_test_encrypt security)

add_executable(unit_test_diffiehellman src/unit_test/security/diffiehellman.cpp)
target_link_libraries(unit_test_diffiehellman security)

###Timeline module
add_executable(timeline_server
	src/sync/timeline/TimelineServer.cpp
	)
target_link_libraries(timeline_server shared security)

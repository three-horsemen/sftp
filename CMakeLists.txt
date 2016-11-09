cmake_minimum_required (VERSION 2.6)
project (sftp)

add_compile_options(-std=c++11)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

find_package(Boost 1.54 COMPONENTS log log_setup thread system date_time REQUIRED)

find_path(SQLITE3_INCLUDE_DIR NAMES sqlite3.h)
find_library(SQLITE3_LIBRARY NAMES sqlite3)

include_directories(include ${Boost_INCLUDE_DIRS})

###Shared module
add_library(shared
	src/shared/logger.cpp
	src/shared/SignalHandler.cpp
	)
target_link_libraries(shared ${Boost_LIBRARIES} pthread)

add_executable(unit_test_logger src/unit_test/shared/logger.cpp)
target_link_libraries(unit_test_logger shared)

###Security module
add_library(security
	src/security/cryptmath.cpp
	src/security/cryptstr.cpp
	src/security/encrypt.cpp
	src/security/rsa.cpp
		src/security/DHContainer.cpp
	src/security/securesocket.cpp
	src/security/socketexceptions.cpp
	)
target_link_libraries(security shared)

add_executable(unit_test_encrypt src/unit_test/security/encrypt.cpp)
target_link_libraries(unit_test_encrypt security)

add_executable(unit_test_rsa src/unit_test/security/rsa.cpp)
target_link_libraries(unit_test_rsa security)

add_executable(unit_test_SecureTCP_client src/unit_test/security/SecureTCP_Comms/client.cpp)
target_link_libraries(unit_test_SecureTCP_client security)
add_executable(unit_test_SecureTCP_server src/unit_test/security/SecureTCP_Comms/server.cpp)
target_link_libraries(unit_test_SecureTCP_server security)

###DB module
add_library(db
	src/database/SQLiteException.cpp
	src/database/DbHandler.cpp
	src/database/DbManager.cpp
	src/database/UserManager.cpp
	src/database/PermissionManager.cpp
	src/database/TimelineManager.cpp
	src/database/Notification.cpp
	)
target_link_libraries(db shared security ${SQLITE3_LIBRARY})

add_executable(unit_test_user_manager
	src/unit_test/database/UserManagerUnitTest.cpp
	)
target_link_libraries(unit_test_user_manager db)

add_executable(unit_test_permission_manager
	src/unit_test/database/PermissionManagerUnitTest.cpp
	)
target_link_libraries(unit_test_permission_manager db)

###Sync Module
add_executable(timeline_server src/sync/TimelineServer.cpp)
target_link_libraries(timeline_server security db)

add_executable(timeline_client src/sync/TimelineClientReceiver.cpp)
target_link_libraries(timeline_client security db)

add_executable(unit_test_timeline_client_sender src/unit_test/sync/TImelineClientSenderUnitTest.cpp)
target_link_libraries(unit_test_timeline_client_sender db)

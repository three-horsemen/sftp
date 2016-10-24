cmake_minimum_required (VERSION 2.6)
project (sftp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

add_compile_options(-std=c++11)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_path(SQLITE3_INCLUDE_DIR NAMES sqlite3.h)
find_library(SQLITE3_LIBRARY NAMES sqlite)
#find_package( SQLite3 COMPONENTS REQUIRED )
find_package( Boost 1.54 COMPONENTS log log_setup thread system REQUIRED )

include_directories(include ${Boost_INCLUDE_DIRS})

###Shared module
add_library(shared
	src/shared/logger.cpp
	src/shared/SignalHandler.cpp
	)
target_link_libraries(shared ${Boost_LIBRARIES} pthread)

add_executable(unit_test_logger src/unit_test/shared/logger.cpp)
target_link_libraries(unit_test_logger shared)



###UI module
add_library(ui
	src/ui/Command.cpp
	src/ui/CommandInterpreter.cpp
	src/ui/CommandPathUtil.cpp
	src/ui/UserSessionDetail.cpp
	)
target_link_libraries(ui shared)

add_executable(unit_test_UserSessionDetail src/unit_test/ui/UserSessionDetail.cpp)
target_link_libraries(unit_test_UserSessionDetail ui)
#target_compile_options(unit_test_UserSessionDetail
#	PRIVATE -lboost_filesystem
#	PRIVATE -lboost_system)

add_executable(unit_test_Command src/unit_test/ui/Command.cpp)
target_link_libraries(unit_test_Command ui)



###Security module
add_library(security
	src/security/cryptmath.cpp
	src/security/cryptstr.cpp
	src/security/encrypt.cpp
	src/security/rsa.cpp
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
# add_library(db
# 	src/database/DbManager.cpp
# 	src/database/UserManager.cpp
# 	src/database/PermissionManager.cpp
# 	)
# target_link_libraries(db shared security ${SQLITE_LIBRARIES})

###Sync Module
add_executable(timeline_server src/sync/timeline/TimelineServer.cpp)
target_link_libraries(timeline_server security ${SQLITE3_LIBRARIES})

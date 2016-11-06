/*
SecureSocketException

01: Standard socket error. <STD_SOCK_EXC>
02: Data socket error. <DATA_SOCK_EXC>
03: Listen socket error. <LISTEN_SOCK_EXC>
04: Data Socket IO Exception <DATA_SOCK_IO_EXC>
05: Data socket connect exception <DATA_SOCK_CONN_EXC>
06: Data socket Diffie-Hellman exception <DATA_SOCK_DH_EXC>
07: Listen socket bind exception <LISTEN_SOCK_BIND_EXC>
08: Listen socket listen exception <LISTEN_SOCK_LISTEN_EXC>
09: Listen socket accept connection <LISTEN_SOCK_ACCEPT_EXC>
10: DH Key Container exception. <DH_CONT_EXC>
11: Socket creation exception. <SOCK_CREATE_EXC>
12: Socket reuse exception. <SOCK_REUSE_EXC>
13: Socket close exception. <SOCK_CLOSE_EXC>
14: Data socket incorrect host mode. <DATA_SOCK_BADHOST>
15: Data socket invalid. <DATA_SOCK_INVALID_EXC>
16: Data socket read zero bytes. <DATA_SOCK_READ_EMPTY_EXC>
17: Data socket write zero bytes. <DATA_SOCK_WRITE_EMPTY_EXC>
18: Data socket write buffer empty. <DATA_SOCK_WRITE_EMPTYBUFFER_EXC>

19: DH container invalid. <DH_CONT_INVALID_EXC>
20: Data socket DH encryption failed. <DATA_SOCK_ENCR_EXC>
21: Data socket DH decryption failed. <DATA_SOCK_DECR_EXC>
22: Data socket could not send secured data. <DATA_SOCK_ENCRSEND_EXC>
23: Data socket could not receive secured data. <DATA_SOCK_DECRRECV_EXC>
24: DH Exchange hello message send failed. <DH_HELLOSEND_EXC>
25: DH Exchange key reception failed. <DH_KEYRECV_EXC>
26: DH Exchange key transmission failed. <DH_KEYSEND_EXC>
27: DH Exchange procedure failed. <DH_PROC_EXC>
28: 24: DH Exchange hello message receive failed. <DH_HELLORECV_EXC>

29: Listen socket invalid. <LISTEN_SOCK_INVALID_EXC>
*/

#define STD_SOCK_EXC 1
#define DATA_SOCK_EXC 2
#define LISTEN_SOCK_EXC 3
#define DATA_SOCK_IO_EXC 4
#define DATA_SOCK_CONN_EXC 5
#define DATA_SOCK_DH_EXC 6
#define LISTEN_SOCK_BIND_EXC 7
#define LISTEN_SOCK_LISTEN_EXC 8
#define LISTEN_SOCK_ACCEPT_EXC 9
#define DH_CONT_EXC 10
#define SOCK_CREATE_EXC 11
#define SOCK_REUSE_EXC 12
#define SOCK_CLOSE_EXC 13
#define DATA_SOCK_BADHOST 14
#define DATA_SOCK_INVALID_EXC 15
#define DATA_SOCK_READ_EMPTY_EXC 16
#define DATA_SOCK_WRITE_EMPTY_EXC 17
#define DATA_SOCK_WRITE_EMPTYBUFFER_EXC 18
#define DH_CONT_INVALID_EXC 19
#define DATA_SOCK_ENCR_EXC 20
#define DATA_SOCK_DECR_EXC 21
#define DATA_SOCK_ENCRSEND_EXC 22
#define DATA_SOCK_DECRRECV_EXC 23
#define DH_HELLOSEND_EXC 24
#define DH_KEYRECV_EXC 25
#define DH_KEYSEND_EXC 26
#define DH_PROC_EXC 27
#define DH_HELLORECV_EXC 28
#define LISTEN_SOCK_INVALID_EXC 29
#define DATA_SOCK_READ_TIMEOUT 30
#define DATA_SOCK_CONNECT_TIMEOUT 31

#include "security/cryptstr.hpp"

class SecureSocketException : public std::exception
{
private:
	int errorCode;
	std::string message;
public:
	SecureSocketException(int newErrorCode);
	SecureSocketException(int newErrorCode, std::string newMessage);
	virtual const char* what() const throw()
	{
		return string_to_charArray("Exception: SecureSocketException. " + message + " || Error code: " + std::to_string(errorCode) + "\n");
	}
};

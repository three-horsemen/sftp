/*
 * SQLiteException.hpp
 *
 *  Created on: 05-Nov-2016
 *      Author: reubenjohn
 */

#ifndef SRC_DATABASE_SQLITEEXCEPTION_HPP_
#define SRC_DATABASE_SQLITEEXCEPTION_HPP_

#include <string>
#include <exception>

#include <sqlite3.h>

namespace sftp {

namespace db {

using namespace std;

class SQLiteException: public exception {
private:
	const int rc;
	const string errorMessageStr;
public:
	SQLiteException(int, string);
	virtual ~SQLiteException();

	string getErrorMessage();
	const char* what() const throw ();

};

} /* namespace db */

} /* namespace sftp */

#endif /* SRC_DATABASE_SQLITEEXCEPTION_HPP_ */

/*
 * SQLiteException.cpp
 *
 *  Created on: 05-Nov-2016
 *      Author: reubenjohn
 */

#include "database/SQLiteException.hpp"

namespace sftp {

	namespace db {

		SQLiteException::SQLiteException(int rc, string errorMessage) :
				rc(rc), errorMessageStr(errorMessage) {
		}

		SQLiteException::~SQLiteException() {
		}

		int SQLiteException::getErrorCode() {
			return rc;
		}

		string SQLiteException::getErrorMessage() {
			return errorMessageStr;
		}

		const char *SQLiteException::what() const throw() {
			return errorMessageStr.c_str();
		}

	} /* namespace db */

} /* namespace sftp */

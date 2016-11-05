/*
 * UserManagerUnitTest.cpp
 *
 *  Created on: 11-Oct-2016
 *      Author: reubenjohn
 */

#include <database/DbManager.hpp>
#include <shared/logger.hpp>
#include <limits>	//cin.ignore(numeric_limits<streamsize>::max(), '\n');

using namespace sftp::db;

int getInt() {
	int i;
	while (!(cin >> i)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.  Try again: ";
	}
	return i;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		LOG_ERROR<<"Must specify database name as argument";
		exit(1);
	}
	DbManager::initializeStaticDbManager(argv[1]);
	int ch=0;
	do {
		cout<<"Options:\n"
		<<"0. Exit\n"
		<<"1. Set owners\n"
		<<"2. Check resource accessibility\n"
		<<"3. Move resource\n";
		cout<<"Choice: ";

		//getline(cin,ch);
		ch = getInt();
		cout<<ch<<endl;
		if(ch==0) {
			cout<<"Exiting...\n";
		} else if(ch==1) {
			string path;
			cout<<"Enter path: ";
			cin>>path;
			cout<<path<<endl;
			cin.ignore();
			unsigned int ownerCount=0;
			cout<<"Enter the number of owners: ";
			ownerCount = getInt();
			cout<<ownerCount<<endl;
			string newOwners[ownerCount];
			cout<<"Enter the owners:\n";
			for(unsigned int i=0;i<ownerCount;i++) {
				cin>>newOwners[i];
				cout<<newOwners[i]<<' ';
			}
			cout<<endl;
			cin.ignore();
			try {
				bool success = DbManager::getDb()->getPermissionManager().setOwners(path,newOwners,ownerCount);
				if(success) {
					cout<<"Owners were set successfully\n";
				} else {
					cout<<"Owners were set unsuccessfully\n";
				}
			} catch(SQLiteException &e) {
				cout<<"Failed to set the permission: "<<e.what()<<endl;
			}
		} else if(ch==2) {
			string absolutePath;
			cout<<"Enter path: ";
			cin>>absolutePath;
			cout<<absolutePath<<endl;
			cout<<"Enter owner: ";
			string owner;
			cin>>owner;
			cout<<owner<<endl;
			bool isAccessible = DbManager::getDb()->getPermissionManager().isResourceAccessible(absolutePath,owner);
			if(isAccessible) {
				cout<<"Permission to resource granted\n";
			} else {
				cout<<"Permission to resource denied\n";
			}
		} else if(ch==3) {
			string sourcePath,destinationPath;
			cout<<"Source path: ";
			cin>>sourcePath;cout<<sourcePath<<endl;
			cout<<"Destination path: ";
			cin>>destinationPath;cout<<destinationPath<<endl;
			try {
				int count = DbManager::getDb()->getPermissionManager().moveResource(sourcePath,destinationPath);
				if(count>=0) {
					cout<<"Successfully moved resource\n";
				} else {
					cout<<"Failed to moved resource\n";
				}
			} catch(SQLiteException &e) {
				cout<<"Failed to move resource: "<<e.what()<<endl;
			}
		} else {
			cout<<"Unknown choice\n";
		}
	}while(ch);
	return 0;
}

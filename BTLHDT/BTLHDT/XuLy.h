#include "stdafx.h"
#include <string>
#include <vector>
#include "ThiSinh.h"
#include "Constant.h"
#include "sqlite3.h"
#include <iostream>
#include <fstream>

using namespace std;
class XuLy
{
public:
	string dbname;
	sqlite3 *dbfile;
	string query;
	bool isOpenDB = false;
	XuLy();
	~XuLy();
	vector<string> GetLine();
	ThiSinh OneLineToThiSinh();
	bool ConnectDB();
	void DisonnectDB();
	void InsertDB();

private:
	vector<string> key;
	ifstream dangkynv;
	ifstream csdl;
};


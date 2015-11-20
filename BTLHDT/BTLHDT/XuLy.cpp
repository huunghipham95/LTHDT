#include "stdafx.h"
#include "XuLy.h"
#include "ComonFunction.h"




XuLy::XuLy()
{
	dangkynv = ifstream("dangkynv-bk.csv");
	csdl = ifstream("csdl-bk.csv");
	key = GetLine();
	dbname = "27.db";
	query = R"(
		DROP TABLE nvxt;
		CREATE TABLE nvxt(sbd varchar(9), nvso int, manv varchar(4), diemxt double precision);)";
}


XuLy::~XuLy()
{
}

vector<string> XuLy::GetLine()
{
	char temp[500];
	csdl.getline(temp, 500);
	vector<string> vcsdl = ComonFunction::string_split_csv(temp);
	dangkynv.getline(temp, 500);
	vector<string> vdangkynv = ComonFunction::string_split_csv(temp);
	vector<string> v = vcsdl;
	for (int i = 1; i < vdangkynv.size(); i++) {
		v.push_back(vdangkynv.at(i));
	}
	return v;
}

ThiSinh XuLy::OneLineToThiSinh()
{
	vector<string> line = GetLine();
	map<string, string> m;
	vector<vector<string>> vNguyenVong;
	for (int i = 0; i < line.size(); i++)
	{
		m[key[i]] = line[i];
	}
	map<string, float> mDiem;
	vector<string> mon = MON;
	for each (string var in mon)
	{
		if (m[var] == "NA")
		{
			mDiem[var] = 0;
			continue;
		}
		mDiem[var] = stof(m[var]);
	}
	/*vNguyenVong[0][0] = m["NV1.N"];
	vNguyenVong[0][1] = m["NV1.TH"];
	vNguyenVong[1][0] = m["NV2.N"];
	vNguyenVong[1][1] = m["NV2.TH"];
	vNguyenVong[2][0] = m["NV3.N"];
	vNguyenVong[2][1] = m["NV3.TH"];
	vNguyenVong[3][0] = m["NV4.N"];
	vNguyenVong[3][1] = m["NV4.TH"];*/
	for (int i = 0; i < 4; i++)
	{
		vector<string> temp;
		string temp2;
		temp2 = "NV" + to_string(i + 1) + ".N";
		temp.push_back(m[temp2]);
		temp2 = "NV" + to_string(i + 1) + ".TH";
		temp.push_back(m[temp2]);
		vNguyenVong.push_back(temp);
	}
		
	
	return ThiSinh(m["HoTen"], m["SBD"], mDiem, vNguyenVong, m["NgaySinh"], m["KV"], m["DT"], m["UT"]);
}

bool XuLy::ConnectDB()
{
	if (sqlite3_open(dbname.c_str(), &dbfile) == SQLITE_OK)
	{
		isOpenDB = true;
		return true;
	}
	return false;
}

void XuLy::DisonnectDB()
{
	if (isOpenDB == true)
	{
		sqlite3_close(dbfile);
	}
}

void XuLy::InsertDB()
{
	if (ConnectDB())
	{
		for (int i = 1; i < START_STUDENT; i++)
		{
			char temp[499];
			csdl.getline(temp,498);
			dangkynv.getline(temp,498);
		}
		for (int i = 0; i < 100; i++)
		{
			ThiSinh temp = OneLineToThiSinh();
			for (int k = 0; k < 4; k++)
			{
				if (temp.GetNguyenVong()[k][0] != "NA")
				{
					string s = "INSERT INTO nvxt VALUES ('";
					s += temp.GetSBD() + "',";
					s += to_string(k + 1);
					s += ",'" + temp.GetNguyenVong()[k][0] + "',";
					float diemXT = roundf(temp.TinhDiem(k) * 100) / 100;
					s += to_string(diemXT);
					s += ");";
					query += s;
				}
				cout << to_string(i + 1) + "  " + temp.GetSBD() + "  " + temp.GetNguyenVong()[k][0] << endl;
				
			}
		}
		sqlite3_exec(dbfile, query.c_str(),NULL,NULL,NULL);
		DisonnectDB();
	}
	else
		cout << "Can not open db\n";
}

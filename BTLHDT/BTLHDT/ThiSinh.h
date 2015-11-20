#pragma once
#include <string>	
#include <map>
#include <vector>


using namespace std;

class ThiSinh
{
public:
	ThiSinh(string ten,
	string sbd,
	map<string, float> diem,
	vector<vector<string>> nguyenVong,
	string ngaySinh,
	string khuVuc,
	string doiTuong,
	string uuTien);
	string GetSBD();
	vector<vector<string>> GetNguyenVong();
	~ThiSinh();
	float TinhDiem(int nguyenVong);
private:
	vector<vector<string>> nguyenVong;
	string ten;
	string sbd;
	map<string, float> diem;
	string ngaySinh;
	string khuVuc;
	string doiTuong;
	string uuTien;
};


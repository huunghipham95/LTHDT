#include "stdafx.h"
#include "ThiSinh.h"
#include "ComonFunction.h"




ThiSinh::ThiSinh(string ten, string sbd, map<string, float> diem, vector<vector<string>> nguyenVong, string ngaySinh, string khuVuc, string doiTuong,
	string uuTien)
{
	this->ten = ten;
	this->sbd = sbd;
	this->diem = diem;
	this->nguyenVong = nguyenVong;
	this->ngaySinh = ngaySinh;
	this->khuVuc = khuVuc;
	this->doiTuong = doiTuong;
	this->uuTien = uuTien;
}

string ThiSinh::GetSBD()
{
	return sbd;
}

vector<vector<string>> ThiSinh::GetNguyenVong()
{
	return nguyenVong;
}

ThiSinh::~ThiSinh()
{
}

float ThiSinh::TinhDiem(int nguyenVong)
{
	float d,kv,ut,dt;
	vector<string> s;
	d = 0;
	s = ComonFunction::string_split_csv(this->nguyenVong[nguyenVong][1]);
	for (int i = 0; i < 3; i++)
	{
		d += this->diem[s[i]];
	}
	d += this->diem[s[0]] * stof(s[3]);
	khuVuc == "KV1" ? kv = 1.5 : khuVuc == "KV2-NT" ? kv = 1 : khuVuc == "KV2" ? kv = 0.5 : kv = 0;
	doiTuong == "NDT1" ? dt = 2 : doiTuong == "NDT2" ? dt = 1 : dt = 0;
	uuTien == "UT" ? ut = 1 : ut = 0;
	return d / (3 + stof(s[3])) + (kv + ut + dt)/3;
}


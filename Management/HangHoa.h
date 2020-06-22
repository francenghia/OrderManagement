#include <iostream>
#include <regex>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;
#pragma once
class HangHoa
{
	string tenMatHang;
	float donGia;

public:
	HangHoa();
	HangHoa(string, float);
	HangHoa EnterHangHoa();
	string getTenMatHang();
	float getDonGia();
	~HangHoa();
};


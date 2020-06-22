#include <iostream> 
#include <fstream> 
#include <string> 
#include "HangHoa.h"

using namespace std;

#pragma once
class HoaDon
{
	HangHoa hangHoa;
	int soLuong;
	float thanhTien;
public:
	HoaDon();
	HoaDon(HangHoa, int, float);
	HoaDon EnterHoaDon();
	HangHoa getHangHoa();
	int getSoLuong();
	float getThanhTien();
	~HoaDon();
};


#include "HoaDon.h"

HoaDon::HoaDon(){

}
HoaDon::HoaDon(HangHoa hangHoa, int soLuong, float thanhTien){
	this->hangHoa = hangHoa;
	this->soLuong = soLuong;
	this->thanhTien = thanhTien;
}

HoaDon HoaDon::EnterHoaDon(){
	return *this;
}

HangHoa HoaDon::getHangHoa(){
	return this->hangHoa;
}
int HoaDon::getSoLuong(){
	return this->soLuong;
}

float HoaDon::getThanhTien(){
	return this->thanhTien;
}

HoaDon::~HoaDon(){}
#include "HangHoa.h"

HangHoa::HangHoa() {

}

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool isFloat(string myString) {
	std::istringstream iss(myString);
	float f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
	// Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

HangHoa::HangHoa(string tenMatHang, float donGia) {
	this->tenMatHang = tenMatHang;
	this->donGia = donGia;
}

HangHoa HangHoa::EnterHangHoa() {
	string tenMatHang;
	do {
		cout << endl << "\n - Nhap ten mat hang : ";
		getline(cin, tenMatHang);
		if (is_number(tenMatHang)) {
			cout << "*** Ban nhap so, Moi nhap lai: ***";
		}
	} while (is_number(tenMatHang));
	this->tenMatHang = tenMatHang;

	string donGia = "0";
	do {
		cout << "\n - Nhap don gia: ";
		cin >> donGia;
		if (!isFloat(donGia)) {
			cout << "\n *** Nhap sai don gia. Moi nhap lai ***";
		}
	} while (!isFloat(donGia));
	this->donGia = stof(donGia);
	return *this;
}

string HangHoa::getTenMatHang() {
	return this->tenMatHang;
}

float HangHoa::getDonGia() {
	return this->donGia;
}

HangHoa::~HangHoa() {

}
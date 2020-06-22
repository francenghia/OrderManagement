#define _CRT_SECURE_NO_WARNINGS
#include "ArrayList.h"
#include "HangHoa.h"
#include "HoaDon.h"
#include "TextTable.h"
#include <fstream> 
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <Windows.h> 
#include <string>
#include <vector>
#include <filesystem>
#include <ctime> 
#include <map>
using namespace std;
#pragma once
class Shop
{
private:
	ArrayList<HangHoa> listHangHoa;
	ArrayList<HoaDon> listHoaDon;
public:
	//contructor
	Shop();
	Shop(ArrayList<HangHoa> listHangHoa, ArrayList<HoaDon> listHoaDon);
	//======
	//HangHoa
	//======
	void readFileFromText(string path);
	void writeFileToText(string path);
	void showAllHangHoa();
	void insertHangHoa();
	void updateHangHoa();
	void removeHangHoa();
	//======
	//HoaDon
	//======
	void readFileHoaDonFromText(string path);
	void createHoaDon(string path);
	void updateHoaDon(string path);
	void deleteHoaDon(string path);
	void statisticalHoaDon(string path);
	~Shop();
};


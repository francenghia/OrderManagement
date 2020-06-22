// Management.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> 
#include <string> 
#include <iomanip> 
#include <stdio.h> 
#include <conio.h> 
#include <sstream> 
#include <Windows.h> 
#include <string>
#include <vector>
#include "TextTable.h"
#include "ArrayList.h"
#include "HangHoa.h"
#include "Shop.h"
using namespace std;

#define HANGHOA_DB "Database\\hanghoa\\hanghoa.txt"
#define LIST_HOADON_DB "Database\\hoadon\\*.txt"
#define GLOBAL_HOADON_DB "Database\\hoadon\\"

bool isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}


bool checkChooseNew(string value, int begin, int end) {
	if (!isNumber(value)) {
		return false;
	}

	if (stoi(value) < begin || stoi(value) > end) {
		return false;
	}
	return true;
}

int ChooseContinue() {
	cout << endl << "- Ban muon quay lai menu : " << endl;
	cout << "1. Yes ." << endl;
	cout << "2. No ." << endl;
	bool checkChooseContinue = false;
	string chooseContinueTemp;
	wcout << "Nhap lua chon cua ban : ";
	wcin.ignore(-1);
	do {
		getline(cin, chooseContinueTemp);
		checkChooseContinue = checkChooseNew(chooseContinueTemp, 1, 2);
		if (!checkChooseContinue) {
			cout << "\n Lua chon khong chinh xac. Nhap lai : ";
		}
	} while (!checkChooseContinue);
	return stoi(chooseContinueTemp);
}

void option() {
	Shop shop;
	shop.readFileFromText(HANGHOA_DB);
	string chooseMainTemp;
	bool checkChooseMain = false;
labelMain:
	system("cls");
	cout << endl << "--------------------- QUAN LY HOA DON ---------------------" << endl << endl;
	cout << "====== CHUC NANG HANG HOA ======" << endl;
	cout << "1. Hien thi hang hoa: " << endl;
	cout << "2. Them hang hoa: " << endl;
	cout << "3. Cap nhat hang hoa: " << endl;
	cout << "4. Xoa hang hoa: " << endl;
	cout << "5. Luu file hang hoa: " << endl;
	cout << "====== CHUC NANG HOA DON ======" << endl;
	cout << "6. Lap hoa don: " << endl;
	cout << "7. Chinh sua hoa don: " << endl;
	cout << "8. Xoa hoa don: " << endl;
	cout << "9. Doanh so cua tung mat hang: " << endl;

	cout << "\n -> Nhap Lua chon: ";
	do {
		getline(cin, chooseMainTemp);
		checkChooseMain = checkChooseNew(chooseMainTemp, 1, 10);
		if (!checkChooseMain) {
			cout << "\n Lua chon khong chinh xac. Nhap lai : ";
		}
	} while (!checkChooseMain);
	int chooseMain = stoi(chooseMainTemp);
	switch (chooseMain)
	{
	case 1:
	{
		cout << "1. Hien thi hang hoa: " << endl;
		shop.showAllHangHoa();
		int chooseContinue = ChooseContinue();
		if (chooseContinue == 1) {
			goto labelMain;
		}
		else
			wcout << L"Cảm ơn bạn. hẹn gặp lại sau !" << endl;
		break;
	}
	case 2:
	{
		cout << "2. Cap nhat hang hoa: " << endl;
		shop.insertHangHoa();
		shop.showAllHangHoa();
		int chooseContinue = ChooseContinue();
		if (chooseContinue == 1) {
			goto labelMain;
		}
		else
			wcout << L"Cảm ơn bạn. hẹn gặp lại sau !" << endl;
		break;
	}
	case 3:
	{
		cout << "3. Cap nhat hang hoa: " << endl;
		shop.updateHangHoa();
		int chooseContinue = ChooseContinue();
		if (chooseContinue == 1) {
			goto labelMain;
		}
		else
			wcout << L"Cảm ơn bạn. hẹn gặp lại sau !" << endl;
		break;
	}
	case 4:
	{
		cout << "4. Xoa hang hoa: " << endl;
		shop.removeHangHoa();
		int chooseContinue = ChooseContinue();
		if (chooseContinue == 1) {
			goto labelMain;
		}
		else
			wcout << L"Cảm ơn bạn. hẹn gặp lại sau !" << endl;
		break;
	}
	case 5:
	{
		cout << "5. Luu file hang hoa: " << endl;
		shop.writeFileToText(HANGHOA_DB);
		wcout << "Qua trinh luu file hoan tat!" << endl;
		int chooseContinue = ChooseContinue();
		if (chooseContinue == 1) {
			goto labelMain;
		}
		else
			cout << "Cam on da su dung. Hen lai ban lan sau nhe !" << endl;
		break;
	}
	case 6:
	{
		cout << "6. Lap hoa don: " << endl;
		shop.createHoaDon(LIST_HOADON_DB);
		int chooseContinue = ChooseContinue();
		if (chooseContinue == 1) {
			goto labelMain;
		}
		else
			cout << "Cam on da su dung. Hen lai ban lan sau nhe !" << endl;
		break;
	}
	case 7:
	{
		cout << "7. Chinh sua hoa don: " << endl;
		system("cls");
		shop.updateHoaDon(LIST_HOADON_DB);
		int chooseContinue = ChooseContinue();
		if (chooseContinue == 1) {
			goto labelMain;
		}
		else
			cout << "Cam on da su dung. Hen lai ban lan sau nhe !" << endl;
		break;
	}
	case 8:
	{
		cout << "8. Xoa hoa don: " << endl;
		shop.deleteHoaDon(LIST_HOADON_DB);
		int chooseContinue = ChooseContinue();
		if (chooseContinue == 1) {
			goto labelMain;
		}
		else
			cout << "Cam on da su dung. Hen lai ban lan sau nhe !" << endl;
		break;
	}
	case 9:
	{
		cout << "9. Doanh so cua tung mat hang: " << endl;
		shop.statisticalHoaDon(LIST_HOADON_DB);
		int chooseContinue = ChooseContinue();
		if (chooseContinue == 1) {
			goto labelMain;
		}
		else
			cout << "Cam on da su dung. Hen lai ban lan sau nhe !" << endl;
		break;
	}
	default:
		cout << endl << "Cam on da su dung. Hen lai ban lan sau nhe!" << endl;
		break;
	}

}

int main()
{
	option();


	//int sizeList = listFiles.size();
	//createFormHoaDon(sizeList);

	return 0;
}

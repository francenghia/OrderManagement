#include "Shop.h"

//contructor
Shop::Shop() {
}

Shop::Shop(ArrayList<HangHoa> listHangHoa, ArrayList<HoaDon> listHoaDon) {
	this->listHangHoa = listHangHoa;
}

bool isNumber(std::string x) {
	std::regex e("^-?\\d+");
	if (std::regex_match(x, e)) return true;
	else return false;
}

bool checkChoose(string value, int begin, int end) {
	if (!isNumber(value)) {
		return false;
	}

	if (stoi(value) < begin || stoi(value) > end) {
		return false;
	}
	return true;
}

void getAllHangHoa(ArrayList<HangHoa> listHangHoa) {
	TextTable t('-', '|', '+');
	// create Title
	t.add("STT");
	t.add("Ten mat hang");
	t.add("Don gia");
	t.endOfRow();
	for (int i = 0; i < listHangHoa.getSize(); i++) {
		string stt = to_string(i + 1);
		string tenMH = listHangHoa.getArray()[i].getTenMatHang();
		string donGia = to_string(listHangHoa.getArray()[i].getDonGia());
		t.add(stt);
		t.add(tenMH);
		t.add(donGia);
		t.endOfRow();
	}
	t.setAlignment(listHangHoa.getSize(), TextTable::Alignment::RIGHT);
	cout << t;

}
string wchar_t2string(const wchar_t *wchar)
{
	string str = "";
	int index = 0;
	while (wchar[index] != 0)
	{
		str += (char)wchar[index];
		++index;
	}
	return str;
}

wchar_t *string2wchar_t(const string &str)
{
	wchar_t wchar[260];
	int index = 0;
	while (index < str.size())
	{
		wchar[index] = (wchar_t)str[index];
		++index;
	}
	wchar[index] = 0;
	return wchar;
}

vector<string> listFilesInDirectory(string directoryName)
{
	WIN32_FIND_DATA FindFileData;
	wchar_t * FileName = string2wchar_t(directoryName);
	HANDLE hFind = FindFirstFile(FileName, &FindFileData);

	vector<string> listFileNames;
	listFileNames.push_back(wchar_t2string(FindFileData.cFileName));

	while (FindNextFile(hFind, &FindFileData))
		listFileNames.push_back(wchar_t2string(FindFileData.cFileName));

	return listFileNames;
}

static bool isFloat(const std::string& string) {
	std::string::const_iterator it = string.begin();
	bool decimalPoint = false;
	int minSize = 0;
	if (string.size() > 0 && (string[0] == '-' || string[0] == '+')) {
		it++;
		minSize++;
	}
	while (it != string.end()) {
		if (*it == '.') {
			if (!decimalPoint) decimalPoint = true;
			else break;
		}
		else if (!isdigit(*it) && ((*it != 'f') || it + 1 != string.end() || !decimalPoint)) {
			break;
		}
		++it;
	}
	return string.size() > minSize && it == string.end();
}

string trim(const string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}


vector<string> split(const string& str, const string& delimeter) {
	string token;
	vector<string> splitted;
	size_t ini{ 0 }, end{ 0 };
	while ((end = str.find(delimeter, ini)) <= str.size()) {
		token = str.substr(ini, end - ini);
		ini = end + delimeter.size();
		splitted.push_back(token);
	}
	if (ini < str.size()) {
		token = str.substr(ini);
		splitted.push_back(token);
	}
	return splitted;
}

HoaDon readLineFileHoaDon(string line, int point, int flagThanhTien)
{
	HoaDon hoaDonReturn;
	string delimiter = "|";
	size_t pos = 0;
	string token;
	int flag = 0;
	string tenMatHang;
	string donGia;
	string soLuong;
	string thanhTien;

	//create Data HangHoa and HoaDon
	if (point != flagThanhTien) {

		while ((pos = line.find(delimiter)) != std::string::npos) {

			token = trim(line.substr(0, pos));
			switch (flag)
			{
			case 1: {
				break;
			}
			case 2: {
				tenMatHang = token;
				break;
			}
			case 3: {
				soLuong = token;
				break;
			}
			case 4: {
				donGia = token;
				break;
			}
			case 5: {
				thanhTien = token;
				break;
			}
			default:
				break;
			}

			line.erase(0, pos + delimiter.length());
			flag++;
		}
	}
	else {
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = trim(line.substr(0, pos));
			switch (flag)
			{
			case 5: {
				/*cout << "Tong tien:" << token << endl;*/
				break;
			}
			default:
				break;
			}
			line.erase(0, pos + delimiter.length());
			flag++;
		}
	}

	if (soLuong != "" && thanhTien != "" && tenMatHang != "" && donGia != "")
	{
		HangHoa hangHoa(tenMatHang, stof(donGia));
		HoaDon hoaDon(hangHoa, stoi(soLuong), stof(thanhTien));
		hoaDonReturn = hoaDon;

	}

	return hoaDonReturn;
}

void Shop::readFileFromText(string path) {
	string line;
	ifstream myfile(path);
	if (myfile.is_open())
	{
		while (myfile.good())
		{
			getline(myfile, line);
			string tenMatHang = split(line, ",")[0];
			float donGia = stof(split(line, ",")[1]);
			HangHoa hh(tenMatHang, donGia);
			listHangHoa.add(hh);
		}
		myfile.close();
	}
}

void Shop::writeFileToText(string path) {
	ofstream myfile(path);
	if (myfile.is_open())
	{
		for (int i = 0; i < listHangHoa.getSize(); i++) {
			if (i + 1 == listHangHoa.getSize())
				myfile << listHangHoa.getArray()[i].getTenMatHang() << "," << listHangHoa.getArray()[i].getDonGia();
			else {
				myfile << listHangHoa.getArray()[i].getTenMatHang() << "," << listHangHoa.getArray()[i].getDonGia();
				myfile << endl;
			}

		}
		myfile.close();
	}
	else cout << "Unable to open file";
}
//======
//HangHoa
//======
void Shop::showAllHangHoa() {
	getAllHangHoa(listHangHoa);
}

void Shop::insertHangHoa() {
	HangHoa hh;
	cout << "Nhap hang hoa:";
	hh.EnterHangHoa();
	listHangHoa.add(hh);
}

int choseNameOrPrice() {
	string update;
	int start = 1;
	int end = 2;
	cout << "\n + 1. Ten mat hang";
	cout << "\n + 2. Don gia";
	cout << "\n -> Lua chon cua ban:";
	bool checkChooseValidate = false;
	do {
		getline(cin, update);
		checkChooseValidate = checkChoose(update, start, end);
		if (!checkChooseValidate) {
			wcout << "\nBan nhap khong chinh xac. Nhap lai: ";
		}
	} while (!checkChooseValidate);
	int choosed = stoi(update);
	return choosed;
}

int choseYesOrNo() {
	string isYes;
	int start = 1;
	int end = 2;
	cout << "\n + 1. Yes";
	cout << "\n + 2. No";
	cout << "\n -> Lua chon cua ban:";
	bool checkChooseValidate = false;
	do {
		getline(cin, isYes);
		checkChooseValidate = checkChoose(isYes, start, end);
		if (!checkChooseValidate) {
			wcout << "\nBan nhap khong chinh xac. Nhap lai: ";
		}
	} while (!checkChooseValidate);
	int choosed = stoi(isYes);
	return choosed;
}

void Shop::updateHangHoa() {
	showAllHangHoa();
	cout << "\n + Nhap vi tri hang hoa ban muon thay doi gia:" << endl;
	string choose;
	int start = 1;
	int end = listHangHoa.getSize();

	bool checkChooseValidate = false;
	do {
		getline(cin, choose);
		checkChooseValidate = checkChoose(choose, start, end);
		if (!checkChooseValidate) {
			wcout << "\nBan nhap khong chinh xac. Nhap lai!";
		}
	} while (!checkChooseValidate);
	int choosed = stoi(choose);
	cout << "\n San pham ban chon : " << listHangHoa.getArray()[choosed - 1].getTenMatHang() << " - don gia :" << listHangHoa.getArray()[choosed - 1].getDonGia() << endl;
	cout << "\n Ban muon cap nhat theo.";
	int update = choseNameOrPrice();
	if (update == 1) {
		string tenMatHangNew;
		do {
			cout << "- Nhap ten mat hang moi can chinh sua: ";
			getline(cin, tenMatHangNew);
			if (isNumber(tenMatHangNew)) {
				cout << "\nBan nhap khong chinh xac. Nhap lai!";
			}
		} while (isNumber(tenMatHangNew));
		HangHoa hhNew(tenMatHangNew, listHangHoa.getArray()[choosed - 1].getDonGia());

		listHangHoa.remove(choosed - 1);
		listHangHoa.add(hhNew, choosed - 1);
		system("CLS");
		cout << "\n Danh sach duoc cap nhat moi :";
		showAllHangHoa();
	}
	else if (update == 2) {
		cout << "\n Nhap don gia moi can cap nhat: ";
		string donGiaNew = "0";
		do {
			cout << "\n - Nhap don gia: ";
			cin >> donGiaNew;
			if (!isFloat(donGiaNew)) {
				cout << "\n *** Nhap sai don gia. Moi nhap lai ***";
			}
		} while (!isFloat(donGiaNew));
		HangHoa hhNew(listHangHoa.getArray()[choosed - 1].getTenMatHang(), stof(donGiaNew));

		listHangHoa.remove(choosed - 1);
		listHangHoa.add(hhNew, choosed - 1);
		system("CLS");
		cout << "\n Danh sach duoc cap nhat moi :";
		showAllHangHoa();
	}
	else {
		cout << "\n Loi xay ra";
	}
}

void Shop::removeHangHoa() {
	showAllHangHoa();
	cout << "\n + Nhap vi tri hang hoa ban muon xoa:" << endl;
	string choose;
	int start = 1;
	int end = listHangHoa.getSize();

	bool checkChooseValidate = false;
	do {
		getline(cin, choose);
		checkChooseValidate = checkChoose(choose, start, end);
		if (!checkChooseValidate) {
			wcout << "\nBan nhap khong chinh xac. Nhap lai!";
		}
	} while (!checkChooseValidate);
	int choosed = stoi(choose);
	cout << "\n San pham ban chon : " << listHangHoa.getArray()[choosed - 1].getTenMatHang() << " - don gia :" << listHangHoa.getArray()[choosed - 1].getDonGia() << endl;
	cout << "\n Ban co chac chan muon xoa khong?";
	int removeValue = choseYesOrNo();
	if (removeValue == 1) {
		listHangHoa.remove(choosed - 1);
		system("CLS");
		cout << "\n Danh sach duoc xoa moi :" << endl;
		showAllHangHoa();
	}
	else if (removeValue == 2) {
		return;
	}
	else {
		cout << "\n Loi xay ra";
	}
}

int getNumberLines(string path) {
	int number_of_lines = 0;
	string line;
	ifstream myfile(path);
	while (getline(myfile, line))
		++number_of_lines;
	myfile.close();
	return number_of_lines;
}

string Shop::readFileHoaDonFromText(string staticPath) {
	vector<string> listFiles;
	int checkChooseMain;
	listFiles = listFilesInDirectory(staticPath);
	cout << "-- Danh sach cac hoa don --" << endl;
	int flag = 0;
	for (string str : listFiles) {
		flag++;
		cout << flag << "." << str << endl;
	}
	string chooseCase7;
	cout << "\n -> Nhap Lua chon: ";
	do {
		getline(cin, chooseCase7);
		checkChooseMain = checkChoose(chooseCase7, 1, listFiles.size());
		if (!checkChooseMain) {
			cout << "\n Lua chon khong chinh xac. Nhap lai : ";
		}
	} while (!checkChooseMain);
	int choosedCase7 = stoi(chooseCase7);

	string path = "Database\\hoadon\\";
	path.append(listFiles[choosedCase7 - 1]);
	return path;
}

void Shop::createHoaDon(string paths) {
	ArrayList<HoaDon> listHoaDonNew;
	auto time = std::time(nullptr);
	auto tm = *std::localtime(&time);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
	auto str = oss.str();
	vector<string> listFiles;
	listFiles = listFilesInDirectory(paths);
	int sizeList = listFiles.size();
	TextTable t('-', '|', '+');
	t.add("STT");
	t.add("Ten mat hang");
	t.add("So luong");
	t.add("Don gia");
	t.add("Thanh tien");
	t.endOfRow();

mainAdd:
	system("cls");
	cout << endl << "- Them san pham vao hoa don khong : " << endl;
	cout << "1. Yes ." << endl;
	cout << "2. No ." << endl;
	bool checkChooseContinue = false;
	string chooseContinueTemp;
	cout << "Nhap lua chon cua ban : ";
	do {
		getline(cin, chooseContinueTemp);
		checkChooseContinue = checkChoose(chooseContinueTemp, 1, 2);
		if (!checkChooseContinue) {
			cout << "\n Lua chon khong chinh xac. Nhap lai : ";
		}
	} while (!checkChooseContinue);
	switch (stoi(chooseContinueTemp))
	{
	case 1: {
		getAllHangHoa(listHangHoa);
		string positionHangHoa;
		cout << "\n Nhap lua chon cua ban : ";
		do {
			getline(cin, positionHangHoa);
			if (!checkChoose(positionHangHoa, 1, listHangHoa.getSize())) {
				cout << "\n Lua chon khong chinh xac. Nhap lai : ";
			}
		} while (!checkChoose(positionHangHoa, 1, listHangHoa.getSize()));

		string tenHangHoa = listHangHoa.getArray()[stoi(positionHangHoa) - 1].getTenMatHang();
		float donGia = listHangHoa.getArray()[stoi(positionHangHoa) - 1].getDonGia();

		string soLuong;
		do {
			cout << endl << "\n - Nhap so luong: ";
			getline(cin, soLuong);
			if (!isNumber(soLuong)) {
				cout << "Ban nhap text, Moi nhap lai: ";
			}
		} while (!isNumber(soLuong));

		float thanhTien = donGia * stoi(soLuong);

		bool flagAsSame = false;
		if (listHoaDonNew.getSize() > 0) {
			for (int i = 0;i < listHoaDonNew.getSize();i++) {
				if (listHangHoa.getArray()[stoi(positionHangHoa) - 1].getTenMatHang() == listHoaDonNew.getArray()[i].getHangHoa().getTenMatHang()) {
					int slTemp = listHoaDonNew.getArray()[i].getSoLuong();
					listHoaDonNew.remove(i);
					HoaDon hoaDonTemp(listHangHoa.getArray()[stoi(positionHangHoa) - 1], stoi(soLuong) + slTemp,
						(stoi(soLuong) + slTemp) * (listHangHoa.getArray()[stoi(positionHangHoa) - 1].getDonGia()));
					listHoaDonNew.add(hoaDonTemp);
					flagAsSame = true;
				}
				else
					flagAsSame = false;
			}

			if (!flagAsSame) {
				HoaDon hoaDonTemp(listHangHoa.getArray()[stoi(positionHangHoa) - 1], stoi(soLuong), thanhTien);
				listHoaDonNew.add(hoaDonTemp);
			}
		}
		else {
			HoaDon hoaDonTemp(listHangHoa.getArray()[stoi(positionHangHoa) - 1], stoi(soLuong), thanhTien);
			listHoaDonNew.add(hoaDonTemp);
		}


		goto mainAdd;
	}
	case 2: {
		cout << "\n San pham xac nhan. ";
		break;
	}
	default:
		break;
	}

	float total = 0;
	for (int i = 0; i < listHoaDonNew.getSize();i++) {
		string stt = to_string(i + 1);
		t.add(stt);
		t.add(listHoaDonNew.getArray()[i].getHangHoa().getTenMatHang());
		t.add(to_string(listHoaDonNew.getArray()[i].getSoLuong()));
		t.add(to_string(listHoaDonNew.getArray()[i].getHangHoa().getDonGia()));
		t.add(to_string(listHoaDonNew.getArray()[i].getThanhTien()));
		total = total + listHoaDonNew.getArray()[i].getThanhTien();
		t.endOfRow();
	}

	t.add("Cong");
	t.add("");
	t.add("");
	t.add("");
	t.add(to_string(total));
	t.endOfRow();
	t.setAlignment(5, TextTable::Alignment::RIGHT);

	string path = "Database\\hoadon\\hoadon-";
	int sizeAsSoHD = sizeList + 1;
	path.append(to_string(sizeAsSoHD));
	path.append(".txt");

	string tenKH;
	do {
		cout << endl << "\n - Nhap ten khach hang: ";
		getline(cin, tenKH);
		if (isNumber(tenKH)) {
			cout << "Ban nhap so, Moi nhap lai: ";
		}
	} while (isNumber(tenKH));

	string biller;
	do {
		cout << endl << "\n - Nhap ten nguoi lap hoa don: ";
		getline(cin, biller);
		if (isNumber(biller)) {
			cout << "Ban nhap so, Moi nhap lai: ";
		}
	} while (isNumber(biller));

	ofstream myfile(path);
	if (myfile.is_open())
	{
		myfile << "So HD:" << sizeAsSoHD << endl;
		myfile << "Ngay:" << str << endl;
		myfile << "Ten khach hang:" << tenKH << endl;
		myfile << t;
		myfile << "Nguoi lap hoa don:" << biller;
		myfile.close();
	}
	else cout << "Unable to open file";
}

void updateHoaDonNew(string path, string sizeAsSoHD, string date, string tenKH, ArrayList<HoaDon> tempList, string biller) {
	TextTable t('-', '|', '+');
	t.add("STT");
	t.add("Ten mat hang");
	t.add("So luong");
	t.add("Don gia");
	t.add("Thanh tien");
	t.endOfRow();

	float total = 0;
	for (int i = 0; i < tempList.getSize();i++) {
		string stt = to_string(i + 1);
		t.add(stt);
		t.add(tempList.getArray()[i].getHangHoa().getTenMatHang());
		t.add(to_string(tempList.getArray()[i].getSoLuong()));
		t.add(to_string(tempList.getArray()[i].getHangHoa().getDonGia()));
		t.add(to_string(tempList.getArray()[i].getThanhTien()));
		total = total + tempList.getArray()[i].getThanhTien();

		t.endOfRow();
	}

	t.add("Cong");
	t.add("");
	t.add("");
	t.add("");
	t.add(to_string(total));
	t.endOfRow();
	t.setAlignment(5, TextTable::Alignment::RIGHT);
	const int result = remove(path.c_str());
	if (result == 0) {
		ofstream myfile(path);
		if (myfile.is_open())
		{
			myfile << "So HD:" << sizeAsSoHD << endl;
			myfile << "Ngay:" << date << endl;
			myfile << "Ten khach hang:" << tenKH << endl;
			myfile << t;
			myfile << "Nguoi lap hoa don:" << biller;
			myfile.close();
		}
		else cout << "Unable to open file";
	}
	else {
		cout << "\n No such file or directory :" << strerror(errno); // No such file or directory
	}

}

void Shop::updateHoaDon(string path) {
	ArrayList<HoaDon> listHoaDonNew;
	string pathFileUpdate = readFileHoaDonFromText(path);
	ArrayList<HoaDon> tempList;
	string line;
	string soHD;
	string date;
	string tenKH;
	string biller;
	ifstream myfile(pathFileUpdate);
	
	if (myfile.is_open())
	{
		int flag = 0;
		int maxSize = getNumberLines(pathFileUpdate);
		while (myfile.good())
		{
			getline(myfile, line);
			flag++;
			if (flag <= 3 || flag >= maxSize) {
				if (flag == 1) {
					soHD = split(line, ":")[1];
				}
				else if (flag == 2) {
					date = split(line, ":")[1];
				}
				else if (flag == 3) {
					tenKH = split(line, ":")[1];
				}
				else {
					biller = split(line, ":")[1];
				}
			}
			else if (flag > 5 && flag < maxSize) {
				HoaDon hd = readLineFileHoaDon(line, flag, maxSize - 2);
				if (hd.getHangHoa().getTenMatHang() != "") {
					tempList.add(hd);
				}
			}
			else {
				continue;
			}
		}

		
		myfile.close();
	mainUpdate:
		string chooseUpdate;
		bool checkUpdateContinue = false;
		cout << "Ban muon sua:" << endl;
		cout << "1. Ten khach hang." << endl;
		cout << "2. San pham : " << endl;
		cout << "3. Nguoi lap hoa don : " << endl;
		cout << "4. Thoat : " << endl;
		cout << "Nhap lua chon cua ban : ";
		do {
			getline(cin, chooseUpdate);
			checkUpdateContinue = checkChoose(chooseUpdate, 1, 4);
			if (!checkUpdateContinue) {
				cout << "\n Lua chon khong chinh xac. Nhap lai : ";
			}
		} while (!checkUpdateContinue);
		switch (stoi(chooseUpdate))
		{
		case 1: {
			string tenKHUpdate;
			do {
				cout << "Nhap ten khach hang can chinh sua :" << endl;
				getline(cin, tenKHUpdate);
				if (isNumber(tenKHUpdate)) {
					cout << "Ban nhap so, Moi nhap lai: ";
				}
			} while (isNumber(tenKHUpdate));
			tenKH = tenKHUpdate;
			updateHoaDonNew(pathFileUpdate, soHD, date, tenKH, tempList, biller);
			/*goto mainUpdate;*/
			break;
		}
		case 2: {
		mainAdd:
			system("cls");
			cout << endl << "- Them san pham vao hoa don khong : " << endl;
			cout << "1. Yes ." << endl;
			cout << "2. No ." << endl;
			bool checkChooseContinue = false;
			string chooseContinueTemp;
			cout << "Nhap lua chon cua ban : ";
			do {
				getline(cin, chooseContinueTemp);
				checkChooseContinue = checkChoose(chooseContinueTemp, 1, 2);
				if (!checkChooseContinue) {
					cout << "\n Lua chon khong chinh xac. Nhap lai : ";
				}
			} while (!checkChooseContinue);
			switch (stoi(chooseContinueTemp))
			{
			case 1: {
				getAllHangHoa(listHangHoa);
				string positionHangHoa;
				cout << "\n Nhap lua chon cua ban : ";
				do {
					getline(cin, positionHangHoa);
					if (!checkChoose(positionHangHoa, 1, listHangHoa.getSize())) {
						cout << "\n Lua chon khong chinh xac. Nhap lai : ";
					}
				} while (!checkChoose(positionHangHoa, 1, listHangHoa.getSize()));

				string tenHangHoa = listHangHoa.getArray()[stoi(positionHangHoa) - 1].getTenMatHang();
				float donGia = listHangHoa.getArray()[stoi(positionHangHoa) - 1].getDonGia();

				string soLuong;
				do {
					cout << endl << "\n - Nhap so luong: ";
					getline(cin, soLuong);
					if (!isNumber(soLuong)) {
						cout << "Ban nhap text, Moi nhap lai: ";
					}
				} while (!isNumber(soLuong));

				float thanhTien = donGia * stoi(soLuong);

				bool flagAsSame = false;
				if (listHoaDonNew.getSize() > 0) {
					for (int i = 0;i < listHoaDonNew.getSize();i++) {
						if (listHangHoa.getArray()[stoi(positionHangHoa) - 1].getTenMatHang() == listHoaDonNew.getArray()[i].getHangHoa().getTenMatHang()) {
							int slTemp = listHoaDonNew.getArray()[i].getSoLuong();
							listHoaDonNew.remove(i);
							HoaDon hoaDonTemp(listHangHoa.getArray()[stoi(positionHangHoa) - 1], stoi(soLuong) + slTemp,
								(stoi(soLuong) + slTemp) * (listHangHoa.getArray()[stoi(positionHangHoa) - 1].getDonGia()));
							listHoaDonNew.add(hoaDonTemp);
							flagAsSame = true;
						}
						else
							flagAsSame = false;
					}

					if (!flagAsSame) {
						HoaDon hoaDonTemp(listHangHoa.getArray()[stoi(positionHangHoa) - 1], stoi(soLuong), thanhTien);
						listHoaDonNew.add(hoaDonTemp);
					}
				}
				else {
					HoaDon hoaDonTemp(listHangHoa.getArray()[stoi(positionHangHoa) - 1], stoi(soLuong), thanhTien);
					listHoaDonNew.add(hoaDonTemp);
				}

				updateHoaDonNew(pathFileUpdate, soHD, date, tenKH, listHoaDonNew, biller);
				goto mainAdd;
			}
			case 2: {
				cout << "\n San pham xac nhan. ";
				break;
			}
			default:
				break;
			}
			goto mainUpdate;
			break;
		}
		case 3: {
			string billerUpdate;
			do {
				cout << "Nhap ten nguoi lap hoa don can chinh sua :" << endl;
				getline(cin, billerUpdate);
				if (isNumber(billerUpdate)) {
					cout << "Ban nhap so, Moi nhap lai: ";
				}
			} while (isNumber(billerUpdate));
			biller = billerUpdate;
			updateHoaDonNew(pathFileUpdate, soHD, date, tenKH, tempList, biller);
			goto mainUpdate;
			break;
		}
		case 4: {
			break;
		}
		default:
			break;
		}
	}
}

void Shop::deleteHoaDon(string staticPath) {
	vector<string> listFiles;
	int checkChooseMain;
	listFiles = listFilesInDirectory(staticPath);
	cout << "-- Danh sach cac hoa don --" << endl;
	int flag = 0;
	for (string str : listFiles) {
		flag++;
		cout << flag << "." << str << endl;
	}
	string chooseCase7;
	cout << "\n -> Nhap Lua chon: ";
	do {
		getline(cin, chooseCase7);
		checkChooseMain = checkChoose(chooseCase7, 1, listFiles.size());
		if (!checkChooseMain) {
			cout << "\n Lua chon khong chinh xac. Nhap lai : ";
		}
	} while (!checkChooseMain);
	int choosedCase7 = stoi(chooseCase7);

	string path = "Database\\hoadon\\";
	path.append(listFiles[choosedCase7 - 1]);

	cout << endl << "- Ban co chac chan muon xoa no khong?: " << endl;
	cout << "1. Yes ." << endl;
	cout << "2. No ." << endl;
	bool checkChooseContinue = false;
	string chooseContinueTemp;
	cout << "Nhap lua chon cua ban : ";
	do {
		getline(cin, chooseContinueTemp);
		checkChooseContinue = checkChoose(chooseContinueTemp, 1, 2);
		if (!checkChooseContinue) {
			cout << "\n Lua chon khong chinh xac. Nhap lai : ";
		}
	} while (!checkChooseContinue);
	if (stoi(chooseContinueTemp) == 1) {
		const int result = remove(path.c_str());
		if (result == 0) {
			cout << "\n Xoa thanh cong";
		}
		else {
			cout << "\n No such file or directory :" << strerror(errno); // No such file or directory
		}
	}

}

void Shop::statisticalHoaDon(string staticPath) {
	vector<string> listFiles;
	int checkChooseMain;
	listFiles = listFilesInDirectory(staticPath);
	int flag = 0;
	map<string, ArrayList<HoaDon>> mapDateWHoaDon;

	for (string str : listFiles) {
		string path = "Database\\hoadon\\";
		path.append(listFiles[flag]);
		ArrayList<HoaDon> tempList;
		flag++;
		string line;
		string soHD;
		string date;
		string tenKH;
		string biller;
		ifstream myfile(path);
		if (myfile.is_open())
		{
			int flag = 0;
			int maxSize = getNumberLines(path);
			while (myfile.good())
			{
				getline(myfile, line);
				flag++;
				if (flag <= 3 || flag >= maxSize) {
					if (flag == 2) {
						date = split(line, ":")[1];
					}
				}
				else if (flag > 5 && flag < maxSize) {
					HoaDon hd = readLineFileHoaDon(line, flag, maxSize - 2);
					if (hd.getHangHoa().getTenMatHang() != "") {
						tempList.add(hd);
					}
				}
				else {
					continue;
				}
			}

			myfile.close();
		}

		mapDateWHoaDon.insert(pair<string, ArrayList<HoaDon>>(date, tempList));
	}
	ArrayList<string> dataByDate;
	map<string, ArrayList<HoaDon>>::iterator itr;
	for (itr = mapDateWHoaDon.begin(); itr != mapDateWHoaDon.end(); ++itr) {
		vector<string> temp = split(itr->first, " ");
		for (int i = 0; i < itr->second.getSize(); i++) {
			string dataTemp = temp[0];
			dataTemp.append("-");
			dataTemp.append(itr->second.getArray()[i].getHangHoa().getTenMatHang());
			dataTemp.append("-");
			dataTemp.append(to_string(itr->second.getArray()[i].getSoLuong()));
			dataByDate.add(dataTemp);
		}
	}

	dataByDate.quickSort();

	int positionFlag = -1;
	int total = 0;
	ArrayList<string> dataFinally;
	for (int i = 0; i < dataByDate.getSize(); i++) {
		string name = split(dataByDate.getArray()[i], "-")[0] + "-" + split(dataByDate.getArray()[i], "-")[1] + "-" + split(dataByDate.getArray()[i], "-")[2] + ":" + split(dataByDate.getArray()[i], "-")[3];

		positionFlag = 0;
		for (int j = i + 1; j < dataByDate.getSize(); j++) {
			string data1 = split(dataByDate.getArray()[i], "-")[0] + split(dataByDate.getArray()[i], "-")[1] + split(dataByDate.getArray()[i], "-")[2] + split(dataByDate.getArray()[i], "-")[3];
			string data2 = split(dataByDate.getArray()[j], "-")[0] + split(dataByDate.getArray()[j], "-")[1] + split(dataByDate.getArray()[j], "-")[2] + split(dataByDate.getArray()[j], "-")[3];
			if (data1 == data2) {
				positionFlag++;
			}
		}

		if (positionFlag == 0) {
			total += stoi(split(dataByDate.getArray()[i], "-")[4]);
			dataFinally.add(name.append(":").append(to_string(total)));
			total = 0;
		}
		else {
			total += stoi(split(dataByDate.getArray()[i], "-")[4]);
		}

	}

	for (int i = 0; i < dataFinally.getSize(); i++) {
		cout << dataFinally.getArray()[i] << endl;
	}
}

Shop::~Shop() {

}

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct ROOM {
	short roomNumber;
	string roomClassify;
	short roomStatus;
	string tenant;
};

struct NODE {
	ROOM data;
	NODE* Next;
};
typedef NODE* List;

NODE* create_node(ROOM data) {
	NODE* P = new NODE;
	P->Next = NULL;
	P->data = data;
	return P;
}

void create_list(List &l) {
	l = NULL;
}

void add_tail(List& l, ROOM room) {
	NODE* p = create_node(room);
	if (l == NULL) l = p;
	else {
		NODE* Q = l;
		while (Q->Next != NULL) {
			Q = Q->Next;
		}
		Q->Next = p;
	}
}

void init(List& l) {
	for (int i = 1; i <= 100; i++) {
		ROOM room;
		if (i <= 10) room.roomClassify = "RR";
		else if (i <= 30) room.roomClassify = "DB";
		else room.roomClassify = "TC";
		room.roomNumber = i;
		room.roomStatus = 0; //con trong 
		room.tenant = "Empty";
		add_tail(l, room);
	}
}

void check_out(List l) {
	short num;
	cout << "Enter the n room number: ";
	cin >> num;
	NODE* Q = l;
	while (Q != NULL) {
		if (Q->data.roomNumber == num) {
			Q->data.roomStatus = 0;
			Q->data.tenant = "Empty";
			break;
		}
		Q = Q->Next;
	}
}

void out_put_one_room(ROOM room) {
	cout << room.roomNumber << " " << room.roomClassify << " " << room.roomStatus << " " << room.tenant << endl;
}
void output(List l) {
	NODE* Q = l;
	while (Q != NULL) {
		out_put_one_room(Q->data);
		Q = Q->Next;
	}
}
void standard(string& str) {
	for (short i = 0; i < str.length();i++) {
		if (str[i] == ' ') {
			str.erase(i, 1);
			i--;
		}
	}
	for (short i = 0;i < str.length();i++) {
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
	}
}

void rent_room(List l) {
	string type;
	cout << "Enter the room classification you want to rent (RR/DB/TC): ";
	cin >> type;

	NODE* Q = l;
	bool found = false;

	cout << "Danh sach cac phong loai: " << type << endl;

	while (Q != NULL) {
		if (Q->data.roomClassify == type) {
			out_put_one_room(Q->data);
			found = true;
		}
		Q = Q->Next;
	}

	if (!found) {
		cout << "No available rooms of the specified classification." << endl;
		return;
	}

	short roomNumber;
	cout << "Enter the room number you want to rent: ";
	cin >> roomNumber;

	Q = l;
	while (Q != NULL) {
		if (Q->data.roomNumber == roomNumber && Q->data.roomStatus == 0) {
			Q->data.roomStatus = 1; 
			cout << "Room " << roomNumber << " has been rented." << endl;

			cout << "Enter the tenant's name: ";
			cin >> Q->data.tenant;

			break;
		}
		Q = Q->Next;
	}
}

void menu(List& l) {
	short choice;

	do {
		cout << "1. Thue phong" << endl;
		cout << "2. tra phong" << endl;
		cout << "3. In danh sach phong" << endl;
		cout << "0. Thoat" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			rent_room(l);
			break;

		case 2:
			check_out(l);
			break;

		case 3:
			output(l);
			break;

		case 0:
			cout << "Thoat chuong trinh!" << endl;
			break;

		default:
			cout << "Lua chon khong hop le!" << endl;
		}

	} while (choice != 0);
}

int main() {
	List roomList;
	create_list(roomList);
	init(roomList);

	cout << "Welcome to the Hotel Room Management System!" << endl;

	menu(roomList);

	return 0;
}
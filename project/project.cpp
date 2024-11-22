#include <iostream>
#include <fstream>
#include<sstream>

using namespace std;
class Seat {
public:
	int seat;
	string name;
	string email;
	int phone;
	Seat* next;
	bool isbooked;
	Seat(int s, string n, string e, int num) {
		seat = s;
		name = n;
		email = e;
		phone = num;
		next = NULL;
		isbooked = false;
	}
};

class seat_list {
public:
	Seat* head;
	seat_list() {
		head = NULL;
	}

	void add_seat(int s, string n, string email, int p) {
		Seat* newnode = new Seat(s, n, email, p);
		if (head == NULL) {
			head = newnode;
		}
		else {
			Seat* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newnode;
			newnode->next = NULL;
		}
	}

	int checkseat(int s_num) {
		ifstream obj;
		obj.open("ticket list.txt", ios::in);
		string line;
		int num, line_number = 0;

		while (getline(obj, line)) {
			line_number++;
			stringstream ss(line);
			string seat_no, name;
			getline(ss, seat_no, ',');
			getline(ss, name, ',');
			num = stoi(seat_no);
			if (num == s_num) {
				obj.close();
				return line_number;
			}
		}

		obj.close();
		return NULL;
	}


	void bookSeat() {
		int seat_num;

		cout << "Enter a seat number which you want to book.\nEnter (1-50)  \n";
		cin >> seat_num;
		if (seat_num < 0 || seat_num >50) {
			cout << "Invalid Input" << endl;
			return;
		}
		Seat* temp = head;
		bool seatFound = false;

		ofstream obj;

		obj.open("ticket list.txt", ios::app);
		while (temp != NULL) {
			if (temp->seat == seat_num) {
				seatFound = true;
				if (checkseat(seat_num) != NULL) {
					cout << "seat is already book " << endl;
					return;
				}
				else {
					if (temp->isbooked == false) {

						cout << "Enter your name " << endl;
						cin >> temp->name;
						cout << "Enter your Email " << endl;
						cin >> temp->email;
						cout << "Enter your Phone " << endl;
						cin >> temp->phone;

						temp->isbooked = true;
						obj << temp->seat << "," << temp->name << "," << temp->email << "," << temp->phone << endl;
						payment();

						cout << "your seat is booked" << endl;
						return;
					}
				}
			}
			temp = temp->next;
		}
		if (seatFound == false) {
			cout << "seat is not available" << endl;
		}
		obj.close();

	}


	void cancel_seat() {
		cout << "Enter seat number you want to cancel: ";
		int seat_num;
		cin >> seat_num;

		if (seat_num < 1 || seat_num > 5) {
			cout << "Invalid Seat Number!" << endl;
			return;
		}

		ifstream readfile("ticket list.txt");
		Seat* tempHead = NULL;
		Seat* tempTail = NULL;
		string line;
		while (getline(readfile, line)) {
			stringstream ss(line);
			string seat_no, name, email, phone;
			int num;
			getline(ss, seat_no, ',');
			getline(ss, name, ',');
			getline(ss, email, ',');
			getline(ss, phone, ',');

			num = stoi(seat_no);

			if (num != seat_num) {
				Seat* newNode = new Seat(num, name, email, stoi(phone));
				if (tempHead == NULL) {
					tempHead = newNode;
					tempTail = newNode;
				}
				else {
					tempTail->next = newNode;
					tempTail = newNode;
				}
			}
		}
		readfile.close();

		ofstream writefile("ticket list.txt");
		Seat* temp = tempHead;
		while (temp != NULL) {
			writefile << temp->seat << "," << temp->name << "," << temp->email << "," << temp->phone << endl;
			temp = temp->next;
		}
		writefile.close();

		cout << "Seat " << seat_num << " has been canceled successfully." << endl;


	}



	void payment() {
		int choice;
		cout << "Enter the payment method. Press(1-2) " << endl;
		cout << "1) Bank Account " << endl << "2) Cash" << endl;
		cin >> choice;
		if (choice == 1) {
			cout << "Account Number = Pk900Hb00000012433213" << endl;
		}
		else if (choice == 2) {
			cout << "Please go and procceed to the cash Counter " << endl;
		}
		else
		{
			cout << "Invalid Input" << endl;
		}
	}

	void display() {
		ifstream readfile;
		readfile.open("ticket list.txt");
		string line;
		while (getline(readfile, line)) {
			cout << line << endl;
		}
	}

};


int main() {
	seat_list list;
	list.head = new Seat(1, "", "", 0);
	int choice;

	for (int i = 2; i <= 50; i++) {
		list.add_seat(i, "", "", 0);
	}

	do {
		cout << "\nMain Menu " << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "1) For Book Seat " << endl;
		cout << "2) For Caancel Booked Seat " << endl;
		cout << "3) Display Info Booked Seat " << endl;
		cout << "4) Exit From Main Menu " << endl;
		cout << "----------------------------------------------------- \n" << endl;

		cin >> choice;

		if (choice < 0 && choice > 5) {
			cout << "Invalid output" << endl;
		}
		if (choice == 1)
			list.bookSeat();
		else if (choice == 2) {
			list.cancel_seat();
		}
		else if (choice == 3)
			list.display();
		else
			cout << "You exit from main menu" << endl;
	} while (choice != 4);
}
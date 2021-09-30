#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

using namespace std;

bool GameOver;
int x, y, fx, fy, score;
int tail = 0;
int* tailx = new int[tail];
int* taily = new int[tail];
char symbol[] = {'a', 'd', 'w', 's'};

void Settings(int& width, int& length, int& allow);
void Output(int& width, int& length, int*& tailx, int*& taily);
int Input();
void Logic(const int& command, const int& allow, int& width, int& length, int*& tailx, int*& taily);

int main() {
	int command, allow = 0, width = 0, length = 0;
	Settings(width, length, allow);
	while (!GameOver) {
		Output(width, length, tailx, taily);
		cout << "X - " << x << " " << "Y - " << y + 1 << endl;
		cout << "Fruit X - " << fx << " " << "Fruit Y - " << fy << endl;
		command = Input();
		Logic(command, allow, width, length, tailx, taily);
	}
	system("cls");
	cout << "!!! GAME OVER !!!" << endl;
	cout << "Your score - " << score << endl;
	return 0;

}
void Settings(int& width, int& length, int& allow) {
	cout << "Allow passage through the walls? " << endl; // ���������� �� ������ ����� ����
	cout << "1 - YES" << endl;
	cout << "0 - NO" << endl;
	cin >> allow;
	system("cls");
	bool map_size = false;
	int answer;
	while(map_size == false){
		cout << "Set map size: width x length" << endl;
		cin >> width >> length;
		if(width >= 30 || length >= 20 || width <= 20 || length <= 10){
			system("cls");
			cout << "Are you sure to set this size o map? 1 - YES, 0 - NO" << endl;
			cin >> answer;
			if(answer == 1) map_size = true;
			else continue;
		}
	}
	GameOver = false; // ������ ���� (�.�. ��� �� ���������)
	// ���������� ������:
	x = width / 2 - 1; // -1 ����� ��������� ����������� ������
	y = length / 2 - 1; 
	// ��������� ���������� ������ (�� 1 �� ���������� �����):
	fx = 1 + rand() % (width - 1);
	fy = 1 + rand() % (length - 1);
	score = 0;
}
void Output(int& width, int& length, int*& tailx, int*& taily) {
	system("cls");
	for (int i = 0; i <= width + 1; i++) { //���������� ������� ������� // +1 ����� ��������� ����������� ������� �������
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < length; i++) { // i = y
		for (int j = 0; j <= width + 1; j++) { // j = x
			if (j == 0 || j == width + 1) {//���������� ����� � ������ ������ // +1 ����� ��������� ����������� ��� ��������� �������
				cout << "#";
			}
			else if (i == y && j == x) {//���������� ������
				cout << "0";
			}
			else if (i == fy && j == fx) {//���������� ������
				cout << "@";
			}
			else{
				bool print = false;
				for (int k = 0; k < tail; k++) {
					if (tailx[k] == j && taily[k] == i) {//���������� ������ 
						print = true;
						cout << "o";
					}
				}
				if (print == false) {//����� �� ���� ������ ��������
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i <= width + 1; i++) {//���������� ������ ������� // +1 ����� ��������� ����������� ������ �������
		cout << "#";
	}
	cout << endl;
	cout << "SCORE - " << score << endl;
}
int Input() {
	char sym;
	sym = _getch(); // ������������� ������� 
	if (sym == 'a') return 0;
	else if (sym == 'd') return 1;
	else if (sym == 'w') return 2;
	else if (sym == 's') return 3;
	else GameOver = true;
}
void Logic(const int& command, const int& allow, int& width, int& length, int*& tailx, int*& taily) {
	// ������ ������ � �����
	if (x == fx && y == fy) {
		score++;
		fx = 1 + rand() % (width - 1);
		fy = 1 + rand() % (length - 1);
		++tail;
	}
	// ������ ������
	int prevx = tailx[0];
	int prevy = taily[0];
	int prev2x, prev2y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < tail; i++) { // i = 1 ������ ��� ��� �������� ������ ��������
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	// ������ ��������
	if('a' == symbol[command]) x--;
	else if('d' == symbol[command]) x++;
	else if('w' == symbol[command]) y--;
	else if('s' == symbol[command]) y++;
	// ������ ����������� ����� ����
	if (allow == 1) {
		if (x > width) {
			x = 1;
		}
		else if (x <= 0) {
			x = width;
		}
		else if (y > length - 1) {
			y = 0;
		}
		else if (y < 0) {
			y = length - 1;
		}
	}
	else if(allow == 0) {
		if (x > width || x < 0 || y > length || y < 0) {
			GameOver = true;
		}
	}
	// ������ ������ � ������
	for (int i = 0; i < tail; i++) {
		if (tailx[i] == x && taily[i] == y) {
			GameOver = true;
		}
	}
	// 
	if (tail == 100) {
		GameOver = true;
		system("cls");
		cout << "!!! YOU WIN !!!" << endl;
		cout << "Your score - " << score;
	}
}


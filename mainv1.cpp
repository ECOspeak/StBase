#include <fstream>
#include <iostream>
#include <windows.h>
#include <string.h>

using namespace std;

int maxAmountOfStudent = 2;//������������ ���������� ���������
int amountOfStudent = 0;//������� ���������� ���������


struct Student {
	char FIO[50];
	char number[12];
	char phone[12];
};



Student *stGroup = new Student[maxAmountOfStudent];//�������� ������� ���������



//C��������� �� ����������� � �������� (� ���������� �������)
void sort(Student *&a, bool flag)//���������� ���������, flag-������ ��� ���� ����������� 
{
	for (int i = 0; i < amountOfStudent; i++) {
		// ���������� ��� �������� ��������.
		for (int j = 0; j < amountOfStudent - i - 1; j++) {
			if (flag) {
				if (strcmp(a[j].FIO, a[j + 1].FIO) < 0) {
					// ���� ��� ���� � ������������ �������, �� ������ �� �������.
					Student tmp;
					tmp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = tmp;
				}
			}
			else {
				if (strcmp(a[j].FIO, a[j + 1].FIO) > 0) {
					// ���� ��� ���� � ������������ �������, �� ������ �� �������,������ ��������
					Student tmp;
					tmp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = tmp;
				}

			}
		}
	}
}

//������ ��� ������ ������ ���������
void print(Student *a)
{
	for (int i = 0; i < amountOfStudent; i++)
	{
		cout << "�" << i + 1 << endl;
		cout << "�������:  " << a[i].FIO << endl;
		cout << "������:   " << a[i].number << endl;
		cout << "����� ��������: " << a[i].phone << endl;
		cout << endl;
	}
}

//���������� ������ ���������
void extendGroup(Student*& stGroup)//(*&)->������ �� ��������� ���������� ��� ��������� ����������� ��������� (stGroup=tmp;)
{
	maxAmountOfStudent *= 2;
	Student* tmp = new Student[maxAmountOfStudent];
	for (int i = 0; i < amountOfStudent; i++)
	{
		tmp[i] = stGroup[i]; // �������� �� ��������� ������
	}
	delete[] stGroup;
	stGroup = tmp;
}


//������� ������ ���������
void dextendGroup(Student*& stGroup)//(*&)->������ �� ���������,���������� ��� ��������� ����������� ��������� (stGroup=tmp;)
{
	if (maxAmountOfStudent / 2 == amountOfStudent)//���� ������ ���������� ����, �� �������� ��� �����.
	{
		maxAmountOfStudent /= 2;
		Student* tmp = new Student[maxAmountOfStudent];
		for (int i = 0; i < amountOfStudent; i++)
		{
			tmp[i] = stGroup[i]; // �������� �� ��������� ������
		}
		delete[] stGroup;
		stGroup = tmp;
	}
}


//�������� �� ������
void del(Student*& a, int position) {
	int i = position - 1;
	while (i != maxAmountOfStudent)
	{
		a[i] = a[i + 1];
		i++;
	}
	amountOfStudent--;
	dextendGroup(a);//�������� ������� ������

}

//����� � ����
void writetofile(Student *a) {
	ofstream fout("output.txt"); // ������ ������ ������ ofstream ��� ������ � ��������� ��� � ������ output.txt
	// ������ ����� � ����
	for (int i = 0; i < amountOfStudent - 1; i++)
	{
		fout << a[i].FIO << endl;
		fout << a[i].number << endl;
		fout << a[i].phone << endl;
	}
	fout << a[amountOfStudent - 1].FIO << endl;//����� ���������� �������� � ����
	fout << a[amountOfStudent - 1].number << endl;//������ ��������
	fout << a[amountOfStudent - 1].phone;//� ��������� ������ �� ������ ���� �������� �� ����� ������ �.�. ���� �� ���� �� ���� ����� ��������� �� ���� ��� ������� �� ���� ��� ������ ��� �������� ���������
	//�������� ������� ���������,�.�. ����� �� ����� ������
	fout.close(); // ��������� ����
}

//������ �� �����
void readfromfile(Student*& a) {//�� �� ��� � ������
	ifstream fin("input.txt");//������ �� ����� "input.txt"
	if (fin)//���� ���� ������� �������
	{
		while (!fin.eof()) {//���� ����� ����a, ���������� ������
			if (maxAmountOfStudent == amountOfStudent) {
				extendGroup(stGroup);//��������� ������, ���� 'if' ��������
			}
			fin.getline(a[amountOfStudent].FIO, 50, '\n');//��������� ��������� ����
			fin.getline(a[amountOfStudent].number, 12, '\n');
			fin.getline(a[amountOfStudent].phone, 12, '\n');
			amountOfStudent++;
		}
		fin.close();// ��������� ����
	}
}


int main() {
	SetConsoleCP(1251);//��� ����� � ��������� <windows.h>
	SetConsoleOutputCP(1251);//�� ������� ��������� ������(setlocale ������-�� ������� ����)
	int position, x;
	do {
		cout << "1. �������� ��������" << endl;
		cout << "2. ������� ��������" << endl;
		cout << "3. ������� ������ ���������" << endl;
		cout << "4. ��������� �� �����" << endl;
		cout << "5. ��������� � ����" << endl;
		cout << "6. ���������� ���������" << endl;
		cout << "0. �����" << endl;
		cout << "\n����� �������� > ";
		cin >> x;
		cout << endl;
		switch (x) {
		case 1:
			if (maxAmountOfStudent == amountOfStudent) {
				extendGroup(stGroup);
			}
			cout << "���: ";
			cin.ignore();//���������� ������� �� ����� ������.
			cin.getline(stGroup[amountOfStudent].FIO, 50);
			cout << "������: ";
			cin >> stGroup[amountOfStudent].number;
			cout << "����� �������� : ";
			cin >> stGroup[amountOfStudent].phone;
			amountOfStudent++;
			cout << endl;
			break;
		case 2:
			cout << "������� ����� ������ ��� �������� : ";
			cin >> position;
			del(stGroup, position);
			break;
		case 3:
			print(stGroup);
			break;
		case 4:
			readfromfile(stGroup);
			break;
		case 5:
			writetofile(stGroup);
			break;
		case 6:
			cout << "���������� �� �����������(1) ��� �� ��������(2) ?" << endl;
			cin >> position;
			if (position == 2)
				sort(stGroup, true);
			else
				sort(stGroup, false);
			break;

		}
	} while (x != 0);
	delete[] stGroup;//������� ������������ ������ ���������� ��� ������ ���������
	return 0;
}

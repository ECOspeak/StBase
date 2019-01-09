#include <fstream>
#include <iostream>
#include <windows.h>
#include <string.h>

using namespace std;

int maxAmountOfStudent = 2;//Максимальное количество студентов
int amountOfStudent = 0;//текущее количество студентов


struct Student {
	char FIO[50];
	char number[12];
	char phone[12];
};



Student *stGroup = new Student[maxAmountOfStudent];//создание массива студентов



//Cортировка по возрастанию и убыванию (в алфавитном порядке)
void sort(Student *&a, bool flag)//сортировка пузырьком, flag-маркер как надо сортировать 
{
	for (int i = 0; i < amountOfStudent; i++) {
		// сравниваем два соседних элемента.
		for (int j = 0; j < amountOfStudent - i - 1; j++) {
			if (flag) {
				if (strcmp(a[j].FIO, a[j + 1].FIO) < 0) {
					// если они идут в неправильном порядке, то меняем их местами.
					Student tmp;
					tmp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = tmp;
				}
			}
			else {
				if (strcmp(a[j].FIO, a[j + 1].FIO) > 0) {
					// если они идут в неправильном порядке, то меняем их местами,только наоборот
					Student tmp;
					tmp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = tmp;
				}

			}
		}
	}
}

//Шаблон для вывода списка студентов
void print(Student *a)
{
	for (int i = 0; i < amountOfStudent; i++)
	{
		cout << "№" << i + 1 << endl;
		cout << "Студент:  " << a[i].FIO << endl;
		cout << "Группа:   " << a[i].number << endl;
		cout << "Номер телефона: " << a[i].phone << endl;
		cout << endl;
	}
}

//расширение списка студентов
void extendGroup(Student*& stGroup)//(*&)->ссылка на указатель Используем для изменения возможности Указателя (stGroup=tmp;)
{
	maxAmountOfStudent *= 2;
	Student* tmp = new Student[maxAmountOfStudent];
	for (int i = 0; i < amountOfStudent; i++)
	{
		tmp[i] = stGroup[i]; // копируем во временный объект
	}
	delete[] stGroup;
	stGroup = tmp;
}


//Сужение списка студентов
void dextendGroup(Student*& stGroup)//(*&)->ссылка на указатель,используем для изменения возможности указателя (stGroup=tmp;)
{
	if (maxAmountOfStudent / 2 == amountOfStudent)//если список наполовину пуст, то уменьшим его вдвое.
	{
		maxAmountOfStudent /= 2;
		Student* tmp = new Student[maxAmountOfStudent];
		for (int i = 0; i < amountOfStudent; i++)
		{
			tmp[i] = stGroup[i]; // копируем во временный объект
		}
		delete[] stGroup;
		stGroup = tmp;
	}
}


//Удаление из списка
void del(Student*& a, int position) {
	int i = position - 1;
	while (i != maxAmountOfStudent)
	{
		a[i] = a[i + 1];
		i++;
	}
	amountOfStudent--;
	dextendGroup(a);//вызываем сужение списка

}

//Вывод в файл
void writetofile(Student *a) {
	ofstream fout("output.txt"); // создаём объект класса ofstream для записи и связываем его с файлом output.txt
	// запись строк в файл
	for (int i = 0; i < amountOfStudent - 1; i++)
	{
		fout << a[i].FIO << endl;
		fout << a[i].number << endl;
		fout << a[i].phone << endl;
	}
	fout << a[amountOfStudent - 1].FIO << endl;//вывод последнего студента в файл
	fout << a[amountOfStudent - 1].number << endl;//сделан отдельно
	fout << a[amountOfStudent - 1].phone;//в последенй строке не должно быть перехода на новою строку т.к. если мы этот же файл дадим программе на вход она считает на один раз больше чем записано студентов
	//реализую немного некрасиво,т.к. делаю не через строки
	fout.close(); // закрываем файл
}

//Чтение из файла
void readfromfile(Student*& a) {//то же что и раньше
	ifstream fin("input.txt");//Чтение из файла "input.txt"
	if (fin)//Если файл удалось открыть
	{
		while (!fin.eof()) {//если конец файлa, прекращаем чтение
			if (maxAmountOfStudent == amountOfStudent) {
				extendGroup(stGroup);//расширяем список, если 'if' сработал
			}
			fin.getline(a[amountOfStudent].FIO, 50, '\n');//считываем построчно файл
			fin.getline(a[amountOfStudent].number, 12, '\n');
			fin.getline(a[amountOfStudent].phone, 12, '\n');
			amountOfStudent++;
		}
		fin.close();// закрываем файл
	}
}


int main() {
	SetConsoleCP(1251);//Для этого и подключал <windows.h>
	SetConsoleOutputCP(1251);//на русский переводим данные(setlocale почему-то выдавал бред)
	int position, x;
	do {
		cout << "1. Добавить студента" << endl;
		cout << "2. Удалить студента" << endl;
		cout << "3. Вывести список студентов" << endl;
		cout << "4. Загрузить из файла" << endl;
		cout << "5. Выгрузить в файл" << endl;
		cout << "6. Сортировка элементов" << endl;
		cout << "0. Выйти" << endl;
		cout << "\nНомер операции > ";
		cin >> x;
		cout << endl;
		switch (x) {
		case 1:
			if (maxAmountOfStudent == amountOfStudent) {
				extendGroup(stGroup);
			}
			cout << "ФИО: ";
			cin.ignore();//игнорируем переход на новую строку.
			cin.getline(stGroup[amountOfStudent].FIO, 50);
			cout << "Группа: ";
			cin >> stGroup[amountOfStudent].number;
			cout << "Номер телефона : ";
			cin >> stGroup[amountOfStudent].phone;
			amountOfStudent++;
			cout << endl;
			break;
		case 2:
			cout << "введите номер записи для удаления : ";
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
			cout << "Сортировка по возрастанию(1) или по убыванию(2) ?" << endl;
			cin >> position;
			if (position == 2)
				sort(stGroup, true);
			else
				sort(stGroup, false);
			break;

		}
	} while (x != 0);
	delete[] stGroup;//очищаем динамическую память выделенную под группу студентов
	return 0;
}

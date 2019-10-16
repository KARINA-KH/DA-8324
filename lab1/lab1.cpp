// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
//#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>


using namespace std;

class Note {
public:
	string type;
	string title;
	vector<string> tags;
	int priority;
	virtual void showData() = 0;
	//void setData();
};

class NoteText : public Note { //запис нотатк
private:
	string text;
public:
	NoteText(string title, int priority, vector<string> tags) {
		type = "Text";
		this->title = title;
		this->tags = tags;
		this->priority = priority;
	};
	void setData(string text) { //запис 
		this->text = text;
	};
	void showData() { //виводить зміст
		cout << type << ": " << title << endl;
		cout << text << endl;
	}
};

class NoteList : public Note {
private:
	vector<string> list;
public:
	NoteList(string title, int priority, vector<string> tags) {
		type = "List";
		this->title = title;
		this->tags = tags;
		this->priority = priority;
	};
	void setData(vector<string> list) {
		this->list = list;
	};
	void showData() {
		cout << type << ": " << title << endl;
		if (!this->list.empty())
			for (unsigned int i = 0; i < this->list.size(); i++)
				cout << "# " << list[i] << endl;
	}
};

//class NoteTable: public Note{};
//class NoteFile: public Note{};
//class NoteCollection: public Note{};

struct Data {
	int id;
	time_t date;
	Note *note;
};

class Notepad { //-журнал
private:
	int counter = 0;
	Data notes[100];
public:
	void addNote(Note *note) {
		notes[counter].id = counter;
		notes[counter].note = note;
		notes[counter].date = time(0);
		counter++;
	};
	Data getNote(int id) {
		if (id > counter) throw "Out of array!";
		return notes[id];
	}
};

class Manager {
private:
	Notepad *notepad;
public:
	Manager() {
		notepad = new Notepad();
	}
	~Manager() {
		delete notepad;
	}
	void createNote(Note *note);
	//void deleteNote(int id);
	void findNote(int id);
	//void changeNote(int id);
	//void archiveNote();
};

void Manager::createNote(Note *note) {
	notepad->addNote(note);
}

void Manager::findNote(int id) {
	notepad->getNote(id).note->showData();
}

int main() {
	Manager *manager = new Manager();
	vector<string> tags = { "a", "b" };
	string s = "test";
	manager->createNote(new NoteText(s, 10, tags));
	s += "1";
	manager->createNote(new NoteList(s, 10, tags));

	manager->findNote(0);
	manager->findNote(1);

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <list>
#include <Windows.h>
#include <algorithm>

using namespace std;

class Note {
public:
	string type;
	string title;
	vector<string> tags;
	int priority;
	virtual void showData() = 0;
};

class NoteText : public Note {
private:
	string text;
public:
	NoteText(string title, int priority, vector<string> tags) {
		type = "Text";
		this->title = title;
		this->tags = tags;
		this->priority = priority;
	};
	void setData(string text) { this->text = text; }
	void showData() {
		cout << title << endl;
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
	void setData(vector<string> list) { this->list = list; }
	void showData() {
		cout << title << endl;
		if (!this->list.empty()) for (int i = 0; i < this->list.size(); i++) cout << "# " << list[i] << endl;
	}
};

//class NoteTable: public Note{};
//class NoteFile: public Note{};
//class NoteCollection: public Note{};

struct Data {
	int id;
	time_t date;
	Note* note;
	Data() :date(time(0)) {}
	Data(Note* note, int id) :date(time(0)), id(id), note(note) {}
};

class Notepad {
private:
	int counter = 0;
	vector<Data> notes;
	//Data notes[100];
public:
	void addNote(Note* note) {
		notes.resize(100);
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
	Notepad* notepad;
public:
	Manager() { notepad = new Notepad(); }
	~Manager() { delete notepad; }
	void createNote(Note* note) { notepad->addNote(note); }
	void deleteNote(int id);
	void findNote(int id) { notepad->getNote(id).note->showData(); }
	void changeNote(int id);
	void archiveNote();
};

bool operator == (Data date1, Data date2) { return date1.date == date2.date; }
bool operator != (Data date1, Data date2) { return date1.date != date2.date; }
bool operator > (const Data& d1, const Data& d2) { return d1.date > d2.date; }
bool operator < (const Data& d1, const Data& d2) { return d1.date < d2.date; }

string title;
bool p_title(Data& e) { return e.note->title == title; }

class Store :Data
{
public:
	list<Data> store;
	void show_store() { for (auto a : store)a.note->showData(); }
	void write_line() { cout << "________________________________________________________________________________\n\n"; }
	void find() {
		auto l = store.begin();
		while (store.end() != (l = find_if(l, store.end(), p_title)))l++->note->showData();
	}
}Store;




//static string noteType, tags, title;
//static int importance, a;
//static Data data;
//static list<Note> store;

int main() {
	Data data1(new NoteText("Hi", 10, { "h","i" }), 10);
	Sleep(1200);
	Data data2(new NoteText("Foo", 10, { "f" }), 10);
	Sleep(1200);
	Data data3(new NoteText("Bar", 10, { "b" }), 10);

	Store.store.push_back(data2);
	Store.store.push_back(data1);
	Store.store.push_back(data3);
	Store.store.push_back(data1);

	Store.show_store();

	Store.write_line();

	Store.store.sort();

	Store.show_store();

	Store.write_line();

	title = "Foo";
	Store.find();

	//Manager* manager = new Manager();
	//vector<string> tags = { "a", "b" };
	//string s = "test";
	//manager->createNote(new NoteText(s, 10, tags));
	//s += "1";
	//manager->createNote(new NoteList(s, 10, tags));

	//manager->findNote(0);
	//manager->findNote(1);
	//store.sort();
	return 0;
}
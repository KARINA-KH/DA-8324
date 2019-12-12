#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <list>
#include <Windows.h>
#include <algorithm>

using namespace std;

class Proto_Note {
public:
	vector<string> tags;
	int priority;
	string type;
};

class Note : protected Proto_Note {
public:
	string title;
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

struct Data {
	int id;
	time_t date, date_edit;
	Note* note;
	Data() :date(time(0)) {}
	Data(Note* note, int id) :date(time(0)), id(id), note(note) {}
};

class Notepad {
private:
	int counter = 0;
	vector<Data> notes;
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
	void findNote(int id) { notepad->getNote(id).note->showData(); }
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

	Store* Store;
	list<Data> store, archive;
	void show_store() { for (auto a : store)a.note->showData(); }
	void show_archive() { for (auto a : archive)a.note->showData(); }
	void write_line() { cout << "________________________________________________________________________________\n\n"; }

	void changeNote(Data new_data) {
		auto l = store.begin();
		while (store.end() != (l = find_if(l, store.end(), p_title))) {
			l = store.erase(l);
			if (l != store.end()) l++;
		}
		new_data.date_edit = time(0);
		store.push_back(new_data);
	}

	void deleteNote() {
		auto l = store.begin();
		while (store.end() != (l = find_if(l, store.end(), p_title))) {
			l = store.erase(l);
			if (l != store.end()) l++;
		}
	}

	void back_to_store() {
		auto l = archive.begin();
		while (archive.end() != (l = find_if(l, archive.end(), p_title))) {
			store.push_back(*l);
			l = archive.erase(l);
			if (l != archive.end()) l++;

		}
	}

	void add_to_archive() {
		auto l = store.begin();
		while (store.end() != (l = find_if(l, store.end(), p_title))) {
			archive.push_back(*l);
			l = store.erase(l);
			if (l != store.end()) l++;
		}
	}
	void find() {
		auto l = store.begin();
		while (store.end() != (l = find_if(l, store.end(), p_title)))l++->note->showData();
	}
}Store;

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

	title = "Foo";
	Store.find();
	Store.add_to_archive();

	Store.write_line();
	Store.show_archive();


	Store.write_line();
	Store.show_store();

	Store.back_to_store();

	title = "Bar";
	Store.deleteNote();
	Store.write_line();
	Store.show_store();

	return 0;
}

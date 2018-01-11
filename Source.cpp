#include "AAtree.h"
#include "AVLtree.h"
#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <ctime>
#include "tests.h"


#define ok "CORRECT"
#define err "ERROR"

using namespace std;
bool fileisequal(const string &, const string &);
bool lineisok(const string &, const string &);

int findkey(const string &);
int findvalue(const string &);

void avl_check(ostream &);
void aa_check(ostream &);


int main(int argc, char *argv[]) {
	if (argc < 4) {
		return 0;
	}
	
	std::string line;
	std::ifstream fileIN(argv[1]);
	assert(fileIN);
	std::ofstream fileOut(argv[2]);
	assert(fileOut);

	avl_tree<int> avl_tree;

	srand(time(0));

	while (getline(fileIN, line)) {
		if (line.find("delete") == 0) {
			if (lineisok(line, "delete")) {
				if (!avl_tree._remove(findkey(line))) {
					fileOut << "error" << endl;
				}
				else {
					fileOut << "ok" << endl;
				}
			}
			else {
				fileOut << "error" << endl;
			}
		}
		if (line == "print") {
			avl_tree.in_order_traversal(fileOut);
			fileOut << endl;
		}
		if (line.find("add") == 0) {
			if (lineisok(line, "add") != 0) {
				avl_tree.insert(findkey(line), findvalue(line));
			}
			else {
				fileOut << "error" << endl;
			}
		}
		if (line.find("search") == 0) {
			if (lineisok(line, "search") != 0) {
				if (!avl_tree.search(findkey(line))) {
					fileOut << "error" << endl;
				}
				else {
					fileOut << "ok" << endl;
				}

			}
			else {
				fileOut << "error" << endl;
			}
		}
		if (line == "min") {
			fileOut << avl_tree.minimum() << endl;
		}
		if (line == "max") {
			fileOut << avl_tree.maximum() << endl;
		}
		if (line == " ") {
			fileOut << "error" << endl;
		}
	}

	cout << "runtime = " << clock() / 1000.0 << endl;

	

	fileIN.clear();
	fileIN.seekg(0);
	fileOut.clear();
	fileOut.seekp(0);

	

	aa_tree<int> aatree;

	srand(time(0));

	while (getline(fileIN, line)) {
		if (line.find("delete") == 0) {
			if (lineisok(line, "delete")) {
				if (!aatree.Delete(findkey(line))) {
					fileOut << "error" << endl;
				}
				else {
					fileOut << "ok" << endl;
				}
			}
			else {
				fileOut << "error" << endl;
			}
		}
		if (line == "print") {
			aatree.in_order_traversal(fileOut);
			fileOut << endl;
		}
		if (line.find("add") == 0) {
			if (lineisok(line, "add") != 0) {
				aatree.insert(findkey(line), findvalue(line));
			}
			else {
				fileOut << "error" << endl;
			}
		}
		if (line.find("search") == 0) {
			if (lineisok(line, "search") != 0) {
				if (!aatree.search(findkey(line))) {
					fileOut << "error" << endl;
				}
				else {
					fileOut << "ok" << endl;
				}
			}
			else {
				fileOut << "error" << endl;
			}
		}
		if (line == "min") {
			fileOut << aatree.minimum() << endl;
		}
		if (line == "max") {
			fileOut << aatree.maximum() << endl;
		}
		if (line == " ") {
			fileOut << "error" << endl;
		}
	}

	cout << "runtime = " << clock() / 1000.0 << endl;


	std::ofstream correct_avl_out("avl.txt", std::ios::out);
	std::ofstream correct_aa_out("aa.txt", std::ios::out);
	avl_check(correct_avl_out);
	aa_check(correct_aa_out);

	







	fileIN.close();
	fileOut.close();

	return 0;
}


bool lineisok(const string &s, const string &command) {
	istringstream iss(s);
	string tmp;

	iss >> tmp;
	if (tmp != command) {
		return false;
	}
	tmp.clear();
	iss >> tmp;

	if (tmp.empty()) {
		return false;
	}
	tmp.clear();
	iss >> tmp;

	if (tmp.empty()) {
		return false;
	}

	tmp.clear();
	iss >> tmp;

	return tmp.empty();
}
bool fileisequal(const string &firstfilename, const string &secondfilename) {
	ifstream firstfile(firstfilename), secondfile(secondfilename);
	assert(firstfile);
	assert(secondfile);

	string buffer1((istreambuf_iterator<char>(firstfile)), istreambuf_iterator<char>());
	string buffer2((istreambuf_iterator<char>(secondfile)), istreambuf_iterator<char>());
	firstfile.close();
	secondfile.close();

	return (buffer1 == buffer2);
}

int findkey(const string &s) {
	istringstream iss(s);
	string tmp;
	iss >> tmp;
	tmp.clear();
	iss >> tmp;
	int key = atoi(tmp.c_str());
	return key;
}
int findvalue(const string &s) {
	istringstream iss(s);
	string tmp;
	iss >> tmp;
	tmp.clear();
	iss >> tmp;
	tmp.clear();
	iss >> tmp;
	int value = atoi(tmp.c_str());
	return value;
}

void avl_check(ostream &outstr) {
	outstr << "--------------------------------------------------------" << endl;
	outstr << "|		avl theoretical test			|" << endl;
	outstr << "--------------------------------------------------------" << endl;


	outstr << "Creating test:		";
	avl_tree<int> * avl = new avl_tree<int>();
	(avl) ? outstr << ok << endl : outstr << err << endl;


	outstr << "empty test:		";
	avl->_remove(0);
	(avl->empty()) ? outstr << ok << endl : outstr << err << endl;


	outstr << "Inserting test:		";
	avl->insert(16, 16);
	avl->insert(1, 1);
	avl->insert(18, 18);
	avl->insert(583, 583);
	(avl->height() == 3) ? outstr << ok << endl : outstr << err << endl;

	outstr << "Searching test:		";
	(avl->search(1) &&
		avl->search(16) &&
		avl->search(18) &&
		avl->search(583) &&
		!avl->search(544)) ? outstr << ok << endl : outstr << err << endl;


	outstr << "MIN, MAX test:		";
	(avl->minimum() == 1 && avl->maximum() == 583) ? outstr << ok << endl : outstr << err << endl;



	outstr << "Removing node test :	";
	avl->_remove(18);

	(avl->search(01) &&
		avl->search(16) &&
		!avl->search(18) &&
		avl->search(583) &&
		avl->height() == 2) ? outstr << ok << endl : outstr << err << endl;


	outstr << "Removing leaves test:	";
	avl->_remove(1);
	avl->_remove(583);

	(avl->search(16) &&
		!avl->search(18) &&
		!avl->search(583) &&
		avl->height() == 1) ? outstr << ok << endl : outstr << err << endl;




}
void aa_check(ostream &outstr) {
	outstr << "--------------------------------------------------------" << endl;
	outstr << "|		aa theoretical test			|" << endl;
	outstr << "--------------------------------------------------------" << endl;

	outstr << "Creating tree test:	";
	aa_tree<int> * aa = new aa_tree<int>();
	(aa) ? outstr << ok << endl : outstr << err << endl;


	outstr << "Empty test:		";
	aa->Delete(0);
	(aa->empty()) ? outstr << ok << endl : outstr << err << endl;


	outstr << "Inserting test:		";
	aa->insert(16, 16);
	aa->insert(1, 1);
	aa->insert(18, 18);
	aa->insert(583, 583);
	(aa->height() == 3) ? outstr << ok << endl : outstr << err << endl;


	outstr << "Searching test:		";
	(aa->search(1) &&
		aa->search(16) &&
		aa->search(18) &&
		aa->search(583) &&
		!aa->search(544)) ? outstr << ok << endl : outstr << err << endl;


	outstr << "MIN, MAX test:		";
	(aa->minimum() == 1 && aa->maximum() == 583) ? outstr << ok << endl : outstr << err << endl;



	outstr << "Removing node test:	";
	aa->Delete(1);

	(!aa->search(1) &&
		aa->search(16) &&
		aa->search(18) &&
		aa->search(583) &&
		aa->height() == 3) ? outstr << ok << endl : outstr << err << endl;


	outstr << "Removing leaves test:	";
	aa->Delete(16);
	aa->Delete(583);

	(!aa->search(16) &&
		aa->search(18) &&
		!aa->search(583) &&
		aa->height() == 1) ? outstr << ok << endl : outstr << err << endl;
	
}








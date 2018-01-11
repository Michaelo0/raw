#include "aatree.h"
#include "avltree.h"
#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <ctime>


bool fileisequal(const std::string &, const std::string &);
bool lineisok(const std::string &, const std::string &);

int findkey(const std::string &);
int findvalue(const std::string &);


int main(int argc, char *argv[]) {
	if (argc < 4) {
		return 0;
	}
	std::string line;
	std::ifstream filein(argv[1]);
	assert(filein);
	std::ofstream fileout(argv[2]);
	assert(fileout);

	/*тесты для авл-дерева*/

	avl_tree<int> avl_tree;

	srand(time(0));

	while (getline(filein, line)) {
		if (line.find("delete") == 0) {
			if (lineisok(line, "delete")) {
				if (!avl_tree._remove(findkey(line))) {
					fileout << "error" << std::endl;
				}
				else {
					fileout << "ok" << std::endl;
				}
			}
			else {
				fileout << "error" << std::endl;
			}
		}
		if (line == "print") {
			avl_tree.in_order_traversal(fileout);
			fileout << std::endl;
		}
		if (line.find("add") == 0) {
			if (lineisok(line, "add") != 0) {
				avl_tree.insert(findkey(line), findvalue(line));
			}
			else {
				fileout << "error" << std::endl;
			}
		}
		if (line.find("search") == 0) {
			if (lineisok(line, "search") != 0) {
				if (!avl_tree.search(findkey(line))) {
					fileout << "error" << std::endl;
				}
				else {
					fileout << "ok" << std::endl;
				}

			}
			else {
				fileout << "error" << std::endl;
			}
		}
		if (line == "min") {
			fileout << avl_tree.minimum() << std::endl;
		}
		if (line == "max") {
			fileout << avl_tree.maximum() << std::endl;
		}
		if (line == " ") {
			fileout << "error" << std::endl;
		}
	}

	std::cout << "runtime = " << clock() / 1000.0 << std::endl;

	if (fileisequal(argv[2], argv[3])) {
		std::cout << "correct" << std::endl;
	}
	else {
		std::cout << "not correct" << std::endl;
	}


	filein.clear();
	filein.seekg(0);
	fileout.clear();
	fileout.seekp(0);

	/*тесты для аа-дерева*/

	aa_tree<int> aatree;

	srand(time(0));

	while (getline(filein, line)) {
		if (line.find("delete") == 0) {
			if (lineisok(line, "delete")) {
				if (!aatree.Delete(findkey(line))) {
					fileout << "error" << std::endl;
				}
				else {
					fileout << "ok" << std::endl;
				}
			}
			else {
				fileout << "error" << std::endl;
			}
		}
		if (line == "print") {
			aatree.in_order_traversal(fileout);
			fileout << std::endl;
		}
		if (line.find("add") == 0) {
			if (lineisok(line, "add") != 0) {
				aatree.insert(findkey(line), findvalue(line));
			}
			else {
				fileout << "error" << std::endl;
			}
		}
		if (line.find("search") == 0) {
			if (lineisok(line, "search") != 0) {
				if (!aatree.search(findkey(line))) {
					fileout << "error" << std::endl;
				}
				else {
					fileout << "ok" << std::endl;
				}
			}
			else {
				fileout << "error" << std::endl;
			}
		}
		if (line == "min") {
			fileout << aatree.min() << std::endl;
		}
		if (line == "max") {
			fileout << aatree.max() << std::endl;
		}
		if (line == " ") {
			fileout << "error" << std::endl;
		}
	}

	std::cout << "runtime = " << clock() / 1000.0 << std::endl;

	if (fileisequal(argv[2], argv[3])) {
		std::cout << "correct" << std::endl;
	}
	else {
		std::cout << "not correct" << std::endl;
	}

	filein.close();
	fileout.close();

	return 0;
}
bool lineisok(const std::string &s, const std::string &command) {
	std::istringstream iss(s);
	std::string tmp;

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
bool fileisequal(const std::string &firstfilename, const std::string &secondfilename) {
	std::ifstream firstfile(firstfilename), secondfile(secondfilename);
	assert(firstfile);
	assert(secondfile);

	std::string buffer1((std::istreambuf_iterator<char>(firstfile)), std::istreambuf_iterator<char>());
	std::string buffer2((std::istreambuf_iterator<char>(secondfile)), std::istreambuf_iterator<char>());
	firstfile.close();
	secondfile.close();

	return (buffer1 == buffer2);
}

int findkey(const std::string &s) {
	std::istringstream iss(s);
	std::string tmp;
	iss >> tmp;
	tmp.clear();
	iss >> tmp;
	int key = atoi(tmp.c_str());
	return key;
}
int findvalue(const std::string &s) {
	std::istringstream iss(s);
	std::string tmp;
	iss >> tmp;
	tmp.clear();
	iss >> tmp;
	tmp.clear();
	iss >> tmp;
	int value = atoi(tmp.c_str());
	return value;
}

//int main()
//{
//	avl_tree<int>* _avl = new avl_tree<int>;
//	_avl->insert(1, 2);
//	_avl->insert(7, 21);
//	_avl->insert(9, 22);
//	/*_avl->insert(11, 32);*/
//
//	///*auto n = _avl->search(1);
//	//if (n != nullptr) {
//	//	std::cout << std::endl;
//	//	std::cout << "Found node with key 3" << std::endl;
//	//	std::cout << std::endl;
//	//	n->info();
//	//}
//
//	//_avl->_remove(7);
//	_avl->_remove(7);
//	_avl->in_order_traversal();
//
//	getchar();
//
//}
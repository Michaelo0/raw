#include <iostream>
#include <fstream>

template <class T>
struct aa_tree_node {
	aa_tree_node *right;
	aa_tree_node *left;
	aa_tree_node *parent;
	int count, level;
	T key;
	T value;

	aa_tree_node(T key, T value) {
		this->key = key;
		this->value = value;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		int count = 0;
		int level = 1;
	}
	int Level() { return this ? level : -1; }

};

template <class T>
class aa_tree {
	aa_tree_node<T> *root;

	aa_tree_node<T> *insertRecursive(aa_tree_node<T> *temp, aa_tree_node<T> *ins) {
		if (root == nullptr) {
			root = ins;
			ins->count = 1;
			ins->parent = nullptr;
			ins->left = nullptr;
			ins->right = nullptr;
			return root;
		}
		if (ins->value <= temp->value && ins->key != temp->key) {
			if (temp->left) {
				return insertRecursive(temp->left, ins);
			}
			temp->left = ins;
			ins->parent = temp;
			ins->count = 1;
			rebal(ins);

			return ins;
		}
		if (ins->value > temp->value || ins->key != temp->key) {
			if (temp->right) {
				return insertRecursive(temp->right, ins);
			}
			temp->right = ins;
			ins->parent = temp;
			ins->count = 1;
			rebal(ins);

			return ins;
		}
		temp->count++;

		delete ins;
		return temp;
	}


	void clear(aa_tree_node <T> * x) {
		if (x == nullptr) return;
		clear(x->left);
		clear(x->right);
		delete x;
	}

	void skew(aa_tree_node<T> *node)
	{
		aa_tree_node<T> *left = node->left;
		if (left && left->level == node->level) node->left = left->right, left->right = node, node = left;

	}
	void rebal(aa_tree_node<T> *temp) {
		temp->left = nullptr;
		temp->right = nullptr;
		temp->level = 1;
		for (temp = temp->parent; temp != root; temp = temp->parent) {
			if (temp->level != (temp->left ? temp->left->level + 1 : 1)) {
				skew(temp);
				if (temp->right == nullptr) {
					temp = temp->parent;
				}
				else if (temp->level != temp->right->level) {
					temp = temp->parent;
				}
			}
			if (temp->parent != root) {
				if (!split(temp->parent)) {
					break;
				}
			}
		}
	}
	void print(std::ostream &ostream, aa_tree_node<T> *temp) {
		if (!temp) {
			return;
		}
		print(ostream, temp->left);
		ostream << temp->value << " ";
		ostream << "Key: " << temp->key << " Value: " << temp->value << std::endl;
		print(ostream, temp->right);
	}

	bool split(aa_tree_node<T> *node)
	{
		aa_tree_node<T> *right = node->right;
		if (right && right->right->level == node->level) {
			node->right = right->left, right->left = node, node = right, node->level++;
			return true;
		}return false;
	}

	bool DeleteHelper(aa_tree_node<T> *parent, aa_tree_node<T> *current, T key) {
		if (!current) {
			return false;
		}
		if (current->key == key) {
			if (current->left == nullptr || current->right == nullptr) {
				aa_tree_node<T>* temp = current->left;
				if (current->right) {
					temp = current->right;
				}
				if (parent) {
					if (parent->left == current) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
				}
				else {
					root = temp;
				}
			}
			else {
				aa_tree_node<T>* validSubs = current->right;
				while (validSubs->left) {
					validSubs = validSubs->left;
				}
				T temp = current->key;
				current->key = validSubs->key;
				validSubs->key = temp;
				return DeleteHelper(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return DeleteHelper(current, current->left, key) ||
			DeleteHelper(current, current->right, key);
	}
public:
	aa_tree() {
		root = nullptr;

	}

	~aa_tree() {
		clear(root);
	}


	T insert(T key, T value) {
		aa_tree_node<T> *temp = new aa_tree_node<T>(key,value);
		temp = insertRecursive(root, temp);
		return temp->count;
	}
	bool Delete(T key) {
		return this->DeleteHelper(nullptr, root, key);
	}
	T min() {
		aa_tree_node<T> *N = root;
		while (N->left != nullptr) {
			N = N->left;
		}
		return N->value;
	}

	
	
	T max() {
		aa_tree_node<T> *N = root;
		while (N->right != nullptr) {
			N = N->right;
		}
		return N->value;
	}

	aa_tree_node <T> *search(T key) {
		aa_tree_node <T> *x = root;
		while (x != nullptr) {
			if (key > x->key) {
				x = x->right;
			}
			else if (key < x->key) {
				x = x->left;
			}
			else {
				return x;
			}
		}
		return nullptr;
	}
	void in_order_traversal(std::ostream &ostream) {
		print(ostream, root);
	}
};


//template <class T>
//void aa_tree<T>::skew(aa_tree_node<T> *temp)
//{
//	aa_tree_node<T> *ptr = temp->left;
//	if (temp->parent->left == temp)
//		temp->parent->left = ptr;
//	else
//		temp->parent->right = ptr;
//	ptr->parent = temp->parent;
//	temp->parent = ptr;
//	temp->left = ptr->right;
//	if (temp->left != nullptr)
//		temp->left->parent = temp;
//	ptr->right = temp;
//	temp->level = (temp->left ? temp->left->level + 1 : 1);
//}


//template <class T>
//bool aa_tree<T>::split(aa_tree_node<T> *temp)
//{
//	aa_tree_node<T>* ptr = temp->right;
//	if (ptr && ptr->right && (ptr->right->level == temp->level)) {
//		if (temp->parent->left == temp) {
//			temp->parent->left = ptr;
//		}
//		else {
//			temp->parent->right = ptr;
//		}
//		ptr->parent = temp->parent;
//		temp->parent = ptr;
//		temp->right = ptr->left;
//		if (temp->right != nullptr) {
//			temp->right->parent = temp;
//		}
//		ptr->left = temp;
//		ptr->level = temp->level + 1;
//		return true;
//	}
//	return false;
//}




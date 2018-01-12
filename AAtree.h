#include <iostream>
#include <fstream>

template <class T>
struct aa_tree_node {
	aa_tree_node *right;
	aa_tree_node *left;
	aa_tree_node *parent;
	T key;
	T value;
	unsigned long long  level;

	aa_tree_node(T key, T value) {
		this->key = key;
		this->value = value;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		unsigned long long level = 1;
	}
	unsigned long long Level() { return this ? level : -1; }
	void info(std::ostream &ostream) {
		ostream << this->value << " ";
		ostream << "Key: " << this->key << " Value: " << this->value << std::endl;
	}
};

template <class T>
class aa_tree {
	aa_tree_node<T> *root;

	aa_tree_node<T> *_insert(aa_tree_node<T>* temp, aa_tree_node<T> *ins) {
		if (root == nullptr) {
			ins->parent = nullptr;
			ins->left = nullptr;
			ins->right = nullptr;
			root = ins;

			return root;
		}
		if (ins->key < temp->key) {
			if (temp->left) {
				return _insert(temp->left, ins);
			}
			temp->left = ins;
			ins->parent = temp;
			rebal(ins);

			return ins;
		}
		if (ins->key > temp->key) {
			if (temp->right) {
				return _insert(temp->right, ins);
			}
			temp->right = ins;
			ins->parent = temp;
			rebal(ins);

			return ins;
		}

		delete ins;
		return temp;
	}


	void clear(aa_tree_node <T> * x) {
		if (x == nullptr) return;
		clear(x->left);
		clear(x->right);
		delete x;
	}
	unsigned long long height(aa_tree_node <T> *x) {
		if (x == nullptr) return 0;
		return std::max(height(x->left), height(x->right)) + 1;
	}

	void skew(aa_tree_node<T> *node)
	{
		aa_tree_node<T> *ptr = node->left;
		if (node->parent->left == node)
			node->parent->left = ptr;
		else
			node->parent->right = ptr;
		ptr->parent = node->parent;
		node->parent = ptr;
		node->left = ptr->right;
		if (node->left != nullptr)
			node->left->parent = node;
		node->right = node;
		node->level = (node->left ? node->left->level + 1 : 1);

	}
	void rebal(aa_tree_node<T> *node) {
		node->left = nullptr;
		node->right = nullptr;
		node->level = 1;
		for (node = node->parent; node != root; node = node->parent) {
			if (node->level != (node->left ? node->left->level + 1 : 1)) {
				skew(node);
				if (node->right == nullptr) {
					node = node->parent;
				}
				else if (node->level != node->right->level) {
					node = node->parent;
				}
			}
			if (node->parent != root) {
				if (!split(node->parent)) {
					break;
				}
			}
		}
	}
	void pre_order_traversal(std::ostream &ostream, aa_tree_node<T> *x) {
		if (!x) return;
		x->info(ostream);
		pre_order_traversal(x->left);
		pre_order_traversal(x->right);
	}
	void in_order_traversal(std::ostream &ostream, aa_tree_node<T> *x) {
		if (!x) {
			return;
		}
		in_order_traversal(ostream, x->left);
		x->info(ostream);
		in_order_traversal(ostream, x->right);
	}
	void post_order_traversal(std::ostream &ostream, aa_tree_node<T> *x) {
		if (x == nullptr) return;
		post_order_traversal(x->left);
		post_order_traversal(x->right);
		x->info(ostream);
	}

	bool split(aa_tree_node<T> *node)
	{
		aa_tree_node<T>* ptr = node->right;
		if (ptr && ptr->right && (ptr->right->level == node->level)) {
			if (node->parent->left == node) {
				node->parent->left = ptr;
			}
			else {
				node->parent->right = ptr;
			}
			ptr->parent = node->parent;
			node->parent = ptr;
			node->right = ptr->left;
			if (node->right != nullptr) {
				node->right->parent = node;
			}
			ptr->left = node;
			ptr->level = node->level + 1;
			return true;
		}
		return false;
	}

	bool _remove(aa_tree_node<T> *parent, aa_tree_node<T> *current, T key) {
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
				return _remove(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return _remove(current, current->left, key) ||
			_remove(current, current->right, key);
	}
public:
	aa_tree() {
		root = nullptr;

	}

	~aa_tree() {
		clear(root);
	}


	void insert(T key, T value) {
		aa_tree_node<T> *node = new aa_tree_node<T>(key,value);
		node = _insert(root, node);
		
	}
	bool remove(T key) {
		return this->_remove(nullptr, root, key);
	}
	T minimum() {
		aa_tree_node <T> *x = root;
		if (x == nullptr) return 0;
		while (x->left != nullptr) x = x->left;
		return x->key;
	}

	T maximum() {
		aa_tree_node <T> *x = root;
		if (x == nullptr) return 0;
		while (x->right != nullptr) x = x->right;
		return x->key;
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

	void pre_order_traversal(std::ostream &ostream) {
		pre_order_traversal(ostream, root);
	}

	void in_order_traversal(std::ostream &ostream) {
		in_order_traversal(ostream, root);
	}

	void post_order_traversal(std::ostream &ostream) {
		post_order_traversal(ostream, root);
	}

	bool empty() {
		if (root == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	
	
	unsigned long long height() {
		return height(root);
	}
};







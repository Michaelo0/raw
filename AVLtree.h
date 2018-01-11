
#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>



template <typename T>
struct avl_tree_node {
	T key;     ///< The key of the node
	T value; ///< The value of the node
	unsigned long long height;
	unsigned long long balance_factor; ///< The avl tree balance factor of this node
	avl_tree_node *parent;  ///< A pointer to the parent of the node
	avl_tree_node *left;    ///< A pointer to the left child of the node
	avl_tree_node *right;   ///< A pointer to the right child of the node
							

	avl_tree_node(T key, T value) {
		this->key = key;
		this->value = value;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		unsigned long long height = 1;
		unsigned long long balance_factor = 1;
	}

	void info(std::ostream &ostream)  {
		ostream << this->value << " ";
		ostream << "Key: " << this->key << " Value: " << this->value << std::endl;
	}
};
template <typename T>
class avl_tree {
private:
	avl_tree_node <T> *root;
	void pre_order_traversal(std::ostream &ostream, avl_tree_node<T> *x) {
		if (!x) return;
		x->info(ostream);
		pre_order_traversal(x->left);
		pre_order_traversal(x->right);
	}
	void in_order_traversal(std::ostream &ostream, avl_tree_node<T> *x) {
		if (!x) {
			return;
		}
		in_order_traversal(ostream, x->left);
		x->info(ostream);
		in_order_traversal(ostream, x->right);
	}
	void post_order_traversal(std::ostream &ostream, avl_tree_node<T> *x) {
		if (x == nullptr) return;
		post_order_traversal(x->left);
		post_order_traversal(x->right);
		x->info(ostream);
	}
	
	unsigned long long height(avl_tree_node <T> *x) {
		if (x == nullptr) return 0;
		return std::max(height(x->left), height(x->right)) + 1;
	}

	unsigned long long size(avl_tree_node <T> *x) {
		if (x == nullptr) return 0;
		return size(x->left) + size(x->right) + 1;
	}
	avl_tree_node <T> * rotate_right(avl_tree_node <T> * rotation_root) {
		avl_tree_node <T> * new_root = rotation_root->left;
		avl_tree_node <T> * orphan_subtree = new_root->right;

		rotation_root->left = orphan_subtree;
		if (orphan_subtree != nullptr) {
			orphan_subtree->parent = rotation_root;
		}

		new_root->right = rotation_root;

		if (rotation_root->parent == nullptr) {
			root = new_root;
		}
		else if (rotation_root == rotation_root->parent->left) {
			rotation_root->parent->left = new_root;
		}
		else if (rotation_root == rotation_root->parent->right) {
			rotation_root->parent->right = new_root;
		}
		new_root->parent = rotation_root->parent;
		rotation_root->parent = new_root;

		setBalance(rotation_root);
		setBalance(new_root);

		return new_root;
	}
	avl_tree_node <T> * rotate_left(avl_tree_node <T> * rotation_root) {
		avl_tree_node <T> * new_root = rotation_root->right;
		avl_tree_node <T> * orphan_subtree = new_root->left;

		rotation_root->right = orphan_subtree;
		if (orphan_subtree != nullptr) {
			orphan_subtree->parent = rotation_root;
		}

		new_root->left = rotation_root;

		if (rotation_root->parent == nullptr) {
			root = new_root;
		}
		else if (rotation_root == rotation_root->parent->left) {
			rotation_root->parent->left = new_root;
		}
		else {
			rotation_root->parent->right = new_root;
		}
		new_root->parent = rotation_root->parent;
		rotation_root->parent = new_root;

		

		setBalance(rotation_root);
		setBalance(new_root);
		return new_root;
	}
	avl_tree_node <T>* rotate_left_then_right(avl_tree_node <T> *n)
	{
		n->left = rotate_left(n->left);
		return rotate_right(n);
	}
	avl_tree_node <T>* rotate_right_then_left(avl_tree_node <T> *n)
	{
		n->right = rotate_right(n->right);
		return rotate_left(n);
	}
	 avl_tree_node <T> * insert(
		avl_tree_node <T> * current,
		avl_tree_node <T> * parent,
		T key,
		T value) {

		 avl_tree_node <T> * inserted_node = nullptr;

		if (current == nullptr) {
			current = new avl_tree_node <T>(key, value);
			inserted_node = current;
			current->parent = parent;

			if (parent == nullptr) {
				root = current;
			}
			else if (current->key > parent->key) {
				parent->right = current;
			}
			else if (current->key < parent->key) {
				parent->left = current;
			}

		}
		else if (key > current->key) {
			inserted_node = insert(current->right, current, key, value);
		}
		else if (key < current->key) {
			inserted_node = insert(current->left, current, key, value);
		}

		current->balance_factor = (height(current->right) - height(current->left));

		
		if (current->balance_factor == -2) {
			
			if (current->left->balance_factor == 1) {
				rotate_left(current->left);
			}
			rotate_right(current);
		}
		
		else if (current->balance_factor == 2) {
			// If right subtree is left heavy -- "double left"
			if (current->right->balance_factor == -1) {
				rotate_right(current->right);
			}
			rotate_left(current);
		}
		return inserted_node;
	}
	void clear(avl_tree_node <T> *x)
	{
		if (x == nullptr) return;
		clear(x->left);
		clear(x->right);
		delete x;
	}
		avl_tree_node <T> *rebalance(avl_tree_node <T> *n)
	{
		setBalance(n);
		 if (n->balance_factor == 2) {
			if (height(n->right->right) >= height(n->right->left))
				n = rotate_left(n);
			else
				n = rotate_right_then_left(n);
		}
		if (n->balance_factor == -2) {
			if (height(n->left->left) >= height(n->left->right))
				n = rotate_right(n);
			else
				n = rotate_left_then_right(n);
		}
		if (n->parent != nullptr) {
			rebalance(n->parent);
		}
		else {
			root = n;
		}

		return n;
	}



	avl_tree_node <T> *remove(avl_tree_node <T>  *temp, T key) {
		avl_tree_node <T> *t;
		if (temp == nullptr) {
			return temp;
		}
		if (temp->key == key) {
			if (temp->left == nullptr || temp->right == nullptr) {
				if (temp->left == nullptr) {
					t = temp->right;
				}
				else {
					t = temp->left;
				}
				delete temp;
				return t;
			}
			else {
				for (t = temp->right; t->left != nullptr; t = t->left);
				temp->key = t->key;
				temp->right = remove(temp->right, t->key);
				return rebalance(temp);
			}
		}
		if (key < temp->key) {
			temp->left = remove(temp->left, key);
		}
		else {
			temp->right = remove(temp->right, key);
		}

		return rebalance(temp);
	}
public:
	avl_tree() {
		root = nullptr;
	}
	~avl_tree() {
		clear(root);
	}
	
	void pre_order_traversal(std::ostream &ostream) {
		pre_order_traversal(ostream,root);
	}
	
	void in_order_traversal(std::ostream &ostream) {
		in_order_traversal(ostream, root);
	}
	
	void post_order_traversal(std::ostream &ostream) {
		post_order_traversal(ostream,root);
	}
	

	 avl_tree_node <T> * insert(T key, T value) {
		return insert(root, nullptr, key, value);
	}
	
	 avl_tree_node <T> *search(T key) {
		avl_tree_node <T> *x = root;
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

	bool _remove(T key) {
		avl_tree_node <T> * x = search(key);
		if (x) {
			root = remove(root, key);
			return true;
		}
		return false;
	}
	
	 T minimum() {
		avl_tree_node <T> *x = root;
		if (x == nullptr) return 0;
		while (x->left != nullptr) x = x->left;
		return x->key;
	}
	
	 T maximum() {
		avl_tree_node <T> *x = root;
		if (x == nullptr) return 0;
		while (x->right != nullptr) x = x->right;
		return x->key;
	}
	
	unsigned long long height() {
		return height(root);
	}
	
	unsigned long long size() {
		return size(root);
	}

	
	bool empty() {
		if (root == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	
	unsigned long long get_height(avl_tree_node <T> * x)
		{
			if (x) return x->height;	
			return 0;
		}

	void set_height(avl_tree_node <T> * x)
		{
			
			x->height = (get_height(x->left) > get_height(x->right) ? get_height(x->left) : get_height(x->right)) + 1;
		}

	void setBalance(avl_tree_node <T> *x) {
		x->balance_factor = height(x->right) - height(x->left);
	}
	

};

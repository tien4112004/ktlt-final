/**
 * @author phanttien
 * @email phanttien@outlook.com
 * @create date 2023-06-03 11:40:21
 * @modify date 2023-06-03 11:40:21
 * @desc [XEPHANG2]
 */

#include <iostream> 
#include <queue>
using namespace std;

struct Node {
	int key;
	Node* next;
};

Node* createNode(int key) {
	Node* new_node = new Node{key, nullptr};
	return new_node;
}

struct List {
	Node* head;
	Node* tail;

	Node* push_front(int key) {
		Node* node = createNode(key);
		node->next = head;
		head = node;
		if (tail == nullptr) tail = node;
		return node;
	}
	
	Node* push_back(int key) {
		Node* node = createNode(key);
		if (tail == nullptr) {
			head = tail = node;
		}
		else {
			tail->next = node;
			tail = node;
		}
		return node;
	}

	void remove_node(int key) {
		Node* current = head;
		Node* prev = nullptr;
		while (current != nullptr && current->key != key) {
			prev = current;
			current = current->next;
		}
		if (current == head) {
			head = head->next;
		}
		else {
			prev->next = current->next;
		}
		if (current == tail) tail = prev;

		delete current;
		return;
	}

	void print_list() {
		Node* current = head;
		if (head == nullptr && tail == nullptr) {
			cout << "Empty!\n";
			return;
		} 
		cout << "\nContents in list: \n";
		cout << "Head = " << head->key << '\n';
		cout << "Tail = " << tail->key << '\n';
		while (current != nullptr) {
			cout << current->key << ' ';
			current = current->next;
		}

		cout << '\n';
	} 
};

void rebuild(List* list, int n) {
	if (list == nullptr || list->head == nullptr) return;
	bool track[n + 1] = {false};
	queue<int> Q; // hold new order of the list

	// create queue with new order of the list
	Node* current = list->head;
	while (current != nullptr) {
		int key = current->key;
		if (track[key] == false) {
			Q.push(key);
			track[key] = true;
		}
		current = current->next;
	}

	// remove all nodes of the old list
	while (list->head != nullptr) {
		list->remove_node(list->head->key);
	}
	// list will empty after this process

	// rebuild new list within the new order from Q
	while (Q.empty() == false) {
		int key = Q.front();
		list->push_back(key);
		Q.pop();
	}
	// list->print_list();
}

int main() {
	int n, m; cin >> n >> m;
	List* list = new List{nullptr, nullptr};
	for (int i = 1; i <= n; i++) {
		list->push_back(i);
	}

	queue<int> Q;
	for (int i = 0; i < m; i++) {
		int x; cin >> x;
		Q.push(x);
		if (x == list->tail->key) {
			while (Q.empty() == false) {
				list->push_front(Q.front());
				Q.pop();
			}
			// list->print_list();
			rebuild(list, n);
			// list->print_list();
		}
		cout << list->tail->key << ' ';
	} 
	return 0;
}
#include <iostream>
#include <stdexcept>

/**
 * Singly Linked List Implementation
 * 
 * This class provides a complete implementation of a singly linked list
 * with operations for adding, removing, and displaying nodes.
 */
class LinkedList {
private:
	/**
	 * Node structure representing a single element in the linked list
	 * Each node contains a value and a pointer to the next node
	 */
	struct Node {
		int value;      // Data stored in the node
		Node* next;     // Pointer to the next node in the list
		
		/**
		 * Constructor for creating a new node
		 * @param v The value to store in this node
		 */
		explicit Node(int v) : value(v), next(nullptr) {}
	};

	Node* head;      // Pointer to the first node in the list
	size_t length;   // Number of nodes in the list

	/**
	 * Helper function to get a node at a specific index
	 * @param index The zero-based index of the node to retrieve
	 * @return Pointer to the node at the specified index
	 * @throws std::out_of_range if index is out of bounds
	 */
	Node* get_node(size_t index) const {
		if (index >= length) throw std::out_of_range("Index out of range");
		Node* curr = head;
		for (size_t i = 0; i < index; ++i) curr = curr->next;
		return curr;
	}

public:
	/**
	 * Constructor - creates an empty linked list
	 */
	LinkedList() : head(nullptr), length(0) {}
	
	/**
	 * Destructor - properly deallocates all nodes to prevent memory leaks
	 */
	~LinkedList() {
		Node* curr = head;
		while (curr) {
			Node* next = curr->next;
			delete curr;
			curr = next;
		}
	}

	// Prevent copying to avoid shallow copy issues
	LinkedList(const LinkedList&) = delete;
	LinkedList& operator=(const LinkedList&) = delete;

	/**
	 * Get the number of nodes in the list
	 * @return The size of the list
	 */
	size_t size() const { return length; }
	
	/**
	 * Check if the list is empty
	 * @return True if the list contains no nodes
	 */
	bool empty() const { return length == 0; }

	/**
	 * Add a node to the beginning of the list
	 * @param value The value to add to the front of the list
	 */
	void push_front(int value) {
		Node* node = new Node(value);
		node->next = head;
		head = node;
		++length;
	}

	/**
	 * Add a node to the end of the list
	 * @param value The value to add to the back of the list
	 */
	void push_back(int value) {
		Node* node = new Node(value);
		if (!head) {
			head = node;
		} else {
			Node* tail = head;
			while (tail->next) tail = tail->next;
			tail->next = node;
		}
		++length;
	}

	/**
	 * Insert a node at a specific position in the list
	 * @param index The position to insert at (0 to length)
	 * @param value The value to insert
	 * @throws std::out_of_range if index is out of bounds
	 */
	void insert_at(size_t index, int value) {
		if (index > length) throw std::out_of_range("Index out of range");
		if (index == 0) { push_front(value); return; }
		if (index == length) { push_back(value); return; }
		Node* prev = get_node(index - 1);
		Node* node = new Node(value);
		node->next = prev->next;
		prev->next = node;
		++length;
	}

	/**
	 * Delete a node at a specific position
	 * @param index The zero-based index of the node to delete
	 * @return True if deletion was successful, false otherwise
	 */
	bool delete_at(size_t index) {
		if (empty()) {
			std::cerr << "Error: delete_at on empty list\n";
			return false;
		}
		if (index >= length) {
			std::cerr << "Error: index out of range\n";
			return false;
		}
		if (index == 0) {
			Node* old = head;
			head = head->next;
			delete old;
			--length;
			return true;
		}
		Node* prev = get_node(index - 1);
		Node* target = prev->next;
		prev->next = target->next;
		delete target;
		--length;
		return true;
	}

	/**
	 * Delete the first occurrence of a specific value
	 * @param value The value to search for and delete
	 * @return True if the value was found and deleted, false otherwise
	 */
	bool delete_value(int value) {
		if (empty()) {
			std::cerr << "Error: delete_value on empty list\n";
			return false;
		}
		if (head->value == value) {
			Node* old = head;
			head = head->next;
			delete old;
			--length;
			return true;
		}
		Node* prev = head;
		Node* curr = head->next;
		while (curr) {
			if (curr->value == value) {
				prev->next = curr->next;
				delete curr;
				--length;
				return true;
			}
			prev = curr;
			curr = curr->next;
		}
		std::cerr << "Info: value not found\n";
		return false;
	}

	/**
	 * Display all nodes in the list in a readable format
	 */
	void print() const {
		std::cout << "[";
		Node* curr = head;
		while (curr) {
			std::cout << curr->value;
			if (curr->next) std::cout << " -> ";
			curr = curr->next;
		}
		std::cout << "] (size=" << length << ")\n";
	}
};

/**
 * Helper function to print section dividers for better test output organization
 * @param title The title to display in the divider
 */
static void divider(const char* title) {
	std::cout << "\n=== " << title << " ===\n";
}

/**
 * Main function demonstrating the linked list implementation
 * with comprehensive test cases covering all operations
 */
int main() {
	// Test Set 1: Basic push_front/push_back and delete_by_index
	divider("Test 1: push_front/back and delete_at");
	LinkedList list1;
	list1.push_back(10);
	list1.push_back(20);
	list1.push_front(5);     // [5, 10, 20]
	list1.print();

	list1.delete_at(1);      // delete 10 -> [5, 20]
	list1.print();

	// Test Set 2: Insert in middle, delete by value (present and absent)
	divider("Test 2: insert_at and delete_value");
	LinkedList list2;
	list2.push_back(1);
	list2.push_back(3);
	list2.insert_at(1, 2);   // [1, 2, 3]
	list2.print();

	list2.delete_value(2);   // remove 2 -> [1, 3]
	list2.print();

	list2.delete_value(42);  // not found
	list2.print();

	// Test Set 3: Error handling on empty and out-of-range
	divider("Test 3: error handling");
	LinkedList list3;
	bool ok;

	ok = list3.delete_at(0); // error: empty
	std::cout << "delete_at on empty returned: " << (ok ? "true" : "false") << "\n";

	try {
		list3.insert_at(1, 99); // out of range (only index 0 allowed on empty)
	} catch (const std::exception& ex) {
		std::cout << "Caught exception: " << ex.what() << "\n";
	}
	list3.insert_at(0, 99); // valid
	list3.print();

	try {
		ok = list3.delete_at(5); // out of range
	} catch (...) {
		// not thrown due to graceful error; just demonstrating call
	}
	std::cout << "delete_at(5) returned: " << (ok ? "true" : "false") << "\n";
	list3.print();

	return 0;
}



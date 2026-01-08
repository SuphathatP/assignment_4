#pragma once
#include <iostream>
#include <functional>
#include <cassert>

#ifndef EXLUDE_RECURSIVE

#ifndef RECURSIFY_FUNCTION
#define RECURSIFY_FUNCTION(FN, TYPE) 	template<typename ... _Types> \
TYPE FN(T first, _Types... rest) { \
	FN(first); \
	FN(rest...); \
};
#endif // !RECURSIFY_FUNCTION
#endif // !EXLUDE_RECURSIVE

// base element class for LinkedList
template <typename T>
struct Node {
	T data;
	Node<T>* next;

	Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
struct LinkedList {
	Node<T>* head;
	Node<T>* tail;

	LinkedList() {
		head = tail = nullptr;
	}

	template<typename ... _Types>
	LinkedList(_Types... items) {
		head = tail = nullptr;
		push_back(items...);
	}

	/*
	* if multiple agruments are passed, they are proccessed in reverse
	* 
	*/
	void push_front(T item) {
		Node<T>* new_beg = new Node<T>(item);

		// if empty, initilize with the new item + early return
		if (this->_init_if_no_head(new_beg)) {
			new_beg->next = head;
			head = new_beg;
		}
	}

	void push_back(T item) {
		Node<T>* new_end = new Node<T>(item);
		if (this->_init_if_no_head(new_end)) {
			/*head = tail = new_end;
			return;*/
		tail->next = new_end;
		tail = new_end;
		}
	}
	#ifndef EXLUDE_RECURSIVE
	RECURSIFY_FUNCTION(push_front, void)
	RECURSIFY_FUNCTION(push_back, void)
	#endif !EXLUDE_RECURSIVE

	T operator[](unsigned int index) {
		unsigned int count = 0;
		Node<T>* curr = head;
		do {
			if (count == index) 
				return curr->data;
			//std::cout << curr->data;
			curr = curr->next;
			count++;
		} while (curr != nullptr);

		assert((void("index out of range"), false));
		//static_assert(false, "index out of range");
		//throw std::runtime_error("index out of range");
	}

	T pop(unsigned int index){
		unsigned int count=0u;
		Node<T>* curr=head;
		Node<T>* prev=nullptr;
		Node<T>* next=nullptr;
		T wanted;
		do {
			if (count == index - 1) {
				prev = curr;

				assert((void("index out of range"), curr->next!=nullptr));
				wanted = curr->next->data;
				//delete curr->next;
				if(
					curr->next // index
					&& curr->next->next // index + 1
					){
					curr->next = curr->next->next;
				}
				return wanted;
			}

			curr = curr->next;
			count++;
		} while (curr != nullptr);

		assert((void("index out of range"), false));
	}

	void remove(unsigned int index){
		unsigned int count=0u;
		Node<T>* curr=head;
		Node<T>* prev=nullptr;
		//Node<T>* next=nullptr;
		do {
			if (count == index - 1) {
				prev = curr;
				Node<T>* _next = curr->next;
				
				// if end of array, we can skip this
				if (_next->next != nullptr)
				{
					prev->next = _next->next;
				}
				break;
			}
			curr = curr->next;
			count++;
		} while (curr != nullptr);
	}
	

	size_t Length(){
		if (head == nullptr)
			return 0;
		if (head->next == nullptr)
			return 1;
		//if (head->next == tail)
		//	return 2;

		Node<T>* curr = head;
		size_t count = 0;

		/*
		 * 1 if not empty:
		 *  2 advance pointer curr
		 *  3 increment count
		 *  4 if curr: goto 2
		 */
		do {
			//std::cout << curr->data;
			curr = curr->next;
			count++;
		} while (curr != nullptr);

		return count;
	}

	void print() {
		if (head == nullptr) return;

		Node<T>* curr = head;
		do {
			std::cout << curr->data << "\n";
			curr = curr->next;
		} while (curr != nullptr);
	}

	void forEach(std::function<void(Node<T>*)> fn) {
		Node<T>* curr = head;

		do {
			fn(curr);
			curr = curr->next;
		} while (curr != nullptr);
	}

private:
	inline bool _init_if_no_head(Node<T>* ele) {
		if (head != nullptr) 
			return true;

		head = tail = ele;
		return false;
	}
};
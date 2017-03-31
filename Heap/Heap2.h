#pragma once
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>
#include <exception>
#include <memory>
#include <array>

class Heap
{
public:

	std::shared_ptr<int[]> p;

	Heap(size_t intialCapacity) : capacity{ intialCapacity } {
		heap = new int[capacity];
		lowWater = capacity >> 2;
		last = 0;
	}

	~Heap() {
		delete[](heap);
	}

	// removes and returns the root
	int pop() {
		if (last == 0) {
			return 0;
		}

		int result{ heap[1] };
		heap[1] = heap[last];
		shrink();
		bubbleDown(1);

		return result;
	}

	void insert(int v) {
		grow();
		heap[last] = v;
		bubbleUp(last);
	}

	void show() {
		std::cout << "Heap size = " << last << "  Last = " << last << "  Heap capacity = " << capacity << std::endl;
		auto it{ heap + 1 }; // ignore position 0
		auto i{ last };
		while (i--) {
			std::cout << *it << ", ";
			it++;
		}
		std::cout << std::endl;
	}

	void initialise() {
		std::stringstream ss{ R"(6,7,13,16,4,12,8,7,5,4,)" }; //
		int input;
		char delimiter;
		while (ss >> input >> delimiter) {
			insert(input);
		}
	}

private:
	int* heap;
	size_t capacity;
	size_t lowWater;
	size_t last;
	int width{ sizeof(int) };

	// returns the parent of the node
	size_t parent(size_t v) {
		if (!(v | 0x0001)) v--;
		return v >> 1;
	}

	// shinks the heap to a minimum size of zero. 
	void shrink() {
		if (last == 0) return;
		last--;
		if (last < lowWater) {
			auto temp = new int[lowWater];
			memcpy(temp, heap, (last+1) * width);
			delete[](heap);
			heap = temp;
			capacity = lowWater;
			if (capacity > 4) {
				lowWater = capacity >> 2;
			}
			else {
				lowWater = 2;
			}
		}
	}

	// grows the heap to maximum size of CAPACITY-1
	void grow() {
		if (last < (capacity - 1)) {
			last++;
		}
		else {
			capacity = capacity << 1;
			auto temp = new int[capacity];
			memcpy(temp, heap, (1+last) * width); 
			delete[](heap);
			heap = temp;
			lowWater = capacity >> 2;
			last++;
		}
	}

	// returns the leftmost child index of v with no guarantee that the child exists
	size_t child(size_t v) {
		return v << 1;
	}

	// swaps values in the two indexes passed as arguments using heap[0] as temp storage
	void swap(size_t lhs, size_t rhs) {
		heap[0] = heap[rhs];
		heap[rhs] = heap[lhs];
		heap[lhs] = heap[0];
	}

	// push current value down if it is larger than the smallest child
	void bubbleDown2(size_t current) {
		size_t lChild{ child(current) };
		size_t rChild{ lChild + 1 };
		size_t minChild;
		if (lChild > last) return;
		if (lChild == last) {
			minChild = lChild;
		}
		if (rChild <= last) {
			minChild = (heap[lChild] < heap[rChild]) ? lChild : rChild;
		}
		if (heap[minChild] < heap[current]) { swap(current, minChild); }
		bubbleDown2(minChild);
	}

	// push current value down if it is larger than the smallest child
	void bubbleDown(size_t current) {
		size_t minChild{ child(current) };  // assume leftChild is minChild
		if (minChild > last) return;  // if leftChild is > last then so is rightChild so we're done
		size_t rChild{ minChild + 1 };  // otherwise we might have a rightChild
		if (rChild <= last) {  // in which case its index will be at most last
			minChild = (heap[minChild] < heap[rChild]) ? minChild : rChild;  // if we have a rightChild then check our assumption and swap if this was wrong
		} // by this point we have the min child
		if (heap[minChild] < heap[current]) { swap(current, minChild); }
		bubbleDown(minChild);
	}

	// promote the current value if it is smaller than the parent
	void bubbleUp(size_t current) {
		size_t par{ parent(current) };
		if ((par == 0) || heap[current] >= heap[par]) return;
		swap(current, par);
		bubbleUp(par);
	}

};


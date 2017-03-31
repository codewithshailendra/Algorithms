#pragma once
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>
#include <exception>

class Heap
{
public:

	Heap(size_t intialCapacity) : capacity{ intialCapacity } {
		heap.resize(capacity);
		lowWater = capacity >> 2;
		last = 0;
	}

	// removes and return the root
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
		std::cout << "Heap size = " << last << "  Last = " << last << "  Heap capacity = " << heap.size() << std::endl;
		auto it{ ++heap.cbegin() }; // ignore position 0
		auto i{ last };
		while (i--) {
			std::cout << *it << ", ";
			it++;
		}
		std::cout << std::endl;
	}

private:
	size_t capacity;
	std::vector<int> heap;
	size_t lowWater;
	size_t last;

	// returns the parent of the node
	size_t parent(size_t v) {
		if (!(v | 0x0001)) v--;
		return v >> 1;
	}

	// shinks the heap to a minimum size of zero. Repositions a single child into the leftmost position.
	void shrink() {
		if (last) last--;
		if (last < lowWater) {
			heap.resize(lowWater);
			capacity = lowWater;
			lowWater = capacity >> 2;
		}
	}

	// grows the heap to maximum size of CAPACITY-1
	void grow() {
		if (last < (capacity - 1)) {
			last++;
		}
		else {
			capacity = capacity << 1;
			heap.resize(capacity);
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


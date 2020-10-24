#include "SLLString.h"

SLLString::SLLString(const std::string& str) : SLLString() {
	_size = str.size();
	if (_size == 0) {
		head = nullptr;
		return;
	}

	auto iter = str.cbegin();
	head = new Node(*iter, nullptr);
	Node* current = head;
	++iter;

	for (; iter < str.cend(); ++iter) {
		current->next = std::make_unique<Node>(*iter, nullptr);
		current = current->next.get();
	}
}

SLLString::SLLString(const SLLString& other) {
	_size = other._size;
	if (_size == 0) {
		head = nullptr;
		return;
	}

	Node* strCurrent = other.head;
	head = new Node(strCurrent->value, nullptr);
	Node* current = head;
	strCurrent = strCurrent->next.get();

	for (size_t i = 0; i < other._size - 1; ++i) {
		current->next = std::make_unique<Node>(strCurrent->value, nullptr);
		current = current->next.get();
		strCurrent = strCurrent->next.get();
	}
}

int SLLString::findSubstring(const SLLString& substring) {
	if (substring._size == 0) {
		return 0;
	}

	for (size_t i = 0; i < _size; ++i) {
		for (size_t substringIndex = 0; substringIndex < _size - i; ++substringIndex) {
			if (nodeAt(i + substringIndex).value != substring[substringIndex]) {
				break;
			}

			if (substringIndex == substring._size - 1) {
				return i;
			}
		}
	}

	return -1;
}

void SLLString::insert(size_t index, char c) {
	if (index == 0) {
		head = new Node(c, std::unique_ptr<Node>(head));
	} else {
		Node& previous = nodeAt(index - 1);
		previous.next = std::make_unique<Node>(c, std::move(previous.next));
	}
	++_size;
}

const SLLString::Node& SLLString::nodeAt(size_t index) const {
	if (index >= _size) {
		throw std::out_of_range("index is out of range");
	}

	Node* current = head;
	for (size_t i = 0; i < index; ++i) {
		current = current->next.get();
	}
	return *current;
}

char& SLLString::operator[](const int index) {
	return nodeAt(index).value;
}

char SLLString::operator[](size_t index) const {
	return nodeAt(index).value;
}

SLLString& SLLString::operator=(const SLLString& other) {
	SLLString copy(other);
	std::swap(head, copy.head);
	_size = copy._size;
	return *this;
}

bool SLLString::operator==(const SLLString& rhs) const {
	if (_size != rhs._size) {
		return false;
	}

	for (size_t i = 0; i < _size; ++i) {
		if (operator[](i) != rhs[i]) {
			return false;
		}
	}

	return true;
}

SLLString& SLLString::operator+=(const SLLString& rhs) {
	if (_size == 0) {
		*this = rhs;
		return *this;
	}

	SLLString copy = rhs;
	nodeAt(_size - 1).next = std::unique_ptr<Node>(copy.head);
	copy.head = nullptr;
	_size += rhs._size;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const SLLString& str) {
	for (size_t i = 0; i < str.size(); ++i) {
		os << str[i];
	}
	return os;
}

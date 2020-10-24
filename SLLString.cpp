#include "SLLString.h"

SLLString::SLLString(const std::string& str) {
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
		current->next_ = std::make_unique<Node>(*iter, nullptr);
		current = current->next_.get();
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
	strCurrent = strCurrent->next_.get();

	for (size_t i = 0; i < other._size - 1; ++i) {
		current->next_ = std::make_unique<Node>(strCurrent->value, nullptr);
		current = current->next_.get();
		strCurrent = strCurrent->next_.get();
	}
}

int SLLString::length() { // NOLINT(readability-make-member-function-const)
	if (_size > std::numeric_limits<int>::max()) {
		throw std::out_of_range("_size is larger than max int");
	}
	return static_cast<int>(_size);
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
				return static_cast<int>(i);
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
		previous.next_ = std::make_unique<Node>(c, std::move(previous.next_));
	}
	++_size;
}

void SLLString::remove(size_t index) {
	if (index >= _size) {
		throw std::out_of_range("index is out of range");
	}

	if (index == 0) {
		Node* tmp = head;
		head = head->next_.release();
		delete tmp;
	} else {
		Node& previous = nodeAt(index - 1);
		previous.next_ = std::move(previous.next_->next_);
	}
	--_size;
}

void SLLString::erase(char c) {
	// Not the most efficient implementation but it works
	for (size_t i = 0; i < _size; ++i) {
		if (nodeAt(i).value == c) {
			remove(i);
			--i;
		}
	}
}

const SLLString::Node& SLLString::nodeAt(size_t index) const {
	if (index >= _size) {
		throw std::out_of_range("index is out of range");
	}

	Node* current = head;
	for (size_t i = 0; i < index; ++i) {
		current = current->next_.get();
	}
	return *current;
}

char& SLLString::operator[](const int index) {
	if (index < 0) {
		throw std::out_of_range("index is out of range");
	}
	return nodeAt(static_cast<size_t>(index)).value;
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
	nodeAt(_size - 1).next_ = std::unique_ptr<Node>(copy.head);
	copy.head = nullptr; // Prevent double free
	_size += rhs._size;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const SLLString& str) {
	for (size_t i = 0; i < str.size(); ++i) {
		os << str[i];
	}
	return os;
}

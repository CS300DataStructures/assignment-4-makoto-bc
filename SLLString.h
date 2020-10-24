#ifndef ASSIGNMENT_4_MAKOTO_BC__SLLSTRING_H_
#define ASSIGNMENT_4_MAKOTO_BC__SLLSTRING_H_

#include <string>
#include <ostream>
#include <memory>

class SLLString {
private:
	class Node {
	public:
		Node(char value, std::unique_ptr<Node> next)
			: value(value)
			  , next(std::move(next)) {}

		char value;
		std::unique_ptr<Node> next;
	};

public:
	SLLString()
		: head(nullptr)
		  , _size(0) {}

	SLLString(const std::string& str); // NOLINT(google-explicit-constructor)

	SLLString(const SLLString& other);

	SLLString(SLLString&& string) noexcept
		: SLLString() {
		std::swap(head, string.head);
		std::swap(_size, string._size);
	}

	~SLLString() {
		delete head;
	}

	int length() { // NOLINT(readability-make-member-function-const)
		if (_size > std::numeric_limits<int>::max()) {
			throw std::out_of_range("_size is larger than int");
		}
		return static_cast<int>(_size);
	}

	size_t size() const {
		return _size;
	}

	int findSubstring(const SLLString& substring);

	void insert(size_t index, char c);

	void remove(size_t index);

	void erase(char c);

	Node& nodeAt(size_t index) {
		return const_cast<Node&>(const_cast<const SLLString&>(*this).nodeAt(index));
	}

	const Node& nodeAt(size_t index) const;

	char& operator[](const int index); // NOLINT(readability-avoid-const-params-in-decls)

	char operator[](size_t index) const;

	SLLString& operator=(const SLLString& other);

	bool operator==(const SLLString& rhs) const;

	SLLString& operator+=(const SLLString& other);

	friend std::ostream& operator<<(std::ostream& os, const SLLString& str);

private:
	Node* head;
	size_t _size;
};

#endif //ASSIGNMENT_4_MAKOTO_BC__SLLSTRING_H_

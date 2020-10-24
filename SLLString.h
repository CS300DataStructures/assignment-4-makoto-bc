#ifndef ASSIGNMENT_4_MAKOTO_BC__SLLSTRING_H_
#define ASSIGNMENT_4_MAKOTO_BC__SLLSTRING_H_

#include <string>
#include <ostream>
#include <memory>

/**
 * String implementation using a linked list.
 */
class SLLString {
private:
	class Node {
	public:
		Node(char value, std::unique_ptr<Node> next)
			: value(value)
			  , next(next.get())
			  , next_(std::move(next)) {}

		char value;
		Node* next;
		std::unique_ptr<Node> next_;
	};

public:
	SLLString()
		: head(nullptr)
		  , _size(0) {}

	/**
	 * Copies all chars from other.
	 */
	SLLString(const std::string& other); // NOLINT(google-explicit-constructor)

	SLLString(const SLLString& other);

	SLLString(SLLString&& string) noexcept
		: SLLString() {
		std::swap(head, string.head);
		std::swap(_size, string._size);
	}

	~SLLString() {
		delete head;
	}

	/**
	 * Size of this string.
	 * @see size()
	 */
	int length();

	size_t size() const {
		return _size;
	}

	/**
	 * @return Index of substring in this string if it exists, or -1 if it does not exist.
	 */
	int findSubstring(const SLLString& substring);

	/**
	 * Inserts c at index.
	 * @throws std::out_of_range index is out of range
	 */
	void insert(size_t index, char c);

	/**
	 * Removes char at index.
	 * @throws std::out_of_range index is out of range
	 */
	void remove(size_t index);

	/**
	 * Removes all occurrences of c.
	 */
	void erase(char c);

	/**
	 * @return Node at index
	 * @throws std::out_of_range index is out of range
	 */
	Node& nodeAt(size_t index) {
		return const_cast<Node&>(const_cast<const SLLString&>(*this).nodeAt(index));
	}

	/**
	 * @return Node at index
	 * @throws std::out_of_range index is out of range
	 */
	const Node& nodeAt(size_t index) const;

	char& operator[](const int index); // NOLINT(readability-avoid-const-params-in-decls)

	char operator[](size_t index) const;

	SLLString& operator=(const SLLString& other);

	bool operator==(const SLLString& rhs) const;

	bool operator!=(const SLLString& rhs) const {
		return !(*this == rhs);
	}

	/**
	 * Concatenates other to the end of this string.
	 * @return this
	 */
	SLLString& operator+=(const SLLString& other);

	friend std::ostream& operator<<(std::ostream& os, const SLLString& str);

private:
	Node* head;
	size_t _size;
};

#endif //ASSIGNMENT_4_MAKOTO_BC__SLLSTRING_H_

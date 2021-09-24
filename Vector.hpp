#pragma once

#include <stdexcept>
#include <utility>

template <typename T>
class Vector {
public:
	Vector();
	explicit Vector(size_t count, const T& value = T());
	explicit Vector(size_t count);
	Vector(const Vector& another);
	Vector operator=(const Vector& another);
	Vector(Vector&& another);
	Vector operator=(Vector&& another);
	Vector(std::initializer_list<T> ilist);

public:
	void assign(size_t count, const T& value = T());
	void assign(std::initializer_list<T> ilist);

public:
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	T& at(size_t index);
	const T& at(size_t index) const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	
public:
	bool empty();
	const bool empty() const;
	size_t size();
	const size_t size() const;
	size_t max_size();
	const size_t max_size() const;
	size_t capacity();
	const size_t capacity() const;

public:
	void reserve(size_t new_capacity);
	void push_back(const T& val);
	template<typename... Args>
	void emplace_back(Args... args);
	void clear();
	void swap(size_t l_index, size_t r_index);
	void pop_back();
	void resize(size_t count);
	void resize(size_t count, const T& val);

public:
	class iterator;
	class const_iterator;
	class rev_iterator;
	class const_rev_iterator;

	iterator begin();
	iterator end();
	const_iterator cbegin();
	const_iterator cend();
	rev_iterator rbegin();
	rev_iterator rend();
	const_rev_iterator crbegin();
	const_rev_iterator crend();

	class iterator {
	public:
		iterator(T* p) : p{ p } {}
		iterator operator++() {
			p++;
			return *this;
		}

		iterator operator++(int) {
			iterator ret_val = *this;
			p++;
			return ret_val;
		}

		iterator operator+(int offset) {
			return iterator(p + offset);
		}

		iterator operator-(int offset) {
			return iterator(p - offset);
		}

		T& operator*() { return *p; }
		bool operator==(const iterator& another) { return p == another.p; }
		bool operator!=(const iterator& another) { return !(*this == another); }
	private:
		T* p;
	};

	class const_iterator {
	public:
		const_iterator(T* p) : p{ p } {}
		const_iterator operator++() {
			p++;
			return *this;
		}

		const_iterator operator++(int) {
			const_iterator ret_val = *this;
			p++;
			return ret_val;
		}

		const_iterator operator+(int offset) {
			return const_iterator(p + offset);
		}

		const_iterator operator-(int offset) {
			return const_iterator(p - offset);
		}

		const T& operator*() const { return *p; }
		bool operator==(const const_iterator& another) { return p == another.p; }
		bool operator!=(const const_iterator& another) { return !(*this == another); }

	private:
		T* p;
	};

	class rev_iterator {
	public:
		rev_iterator(T* p) : p{ p } {}
		rev_iterator operator++() {
			p--;
			return *this;
		}

		rev_iterator operator++(int) {
			rev_iterator ret_val = *this;
			p--;
			return ret_val;
		}

		rev_iterator operator+(int offset) {
			return rev_iterator(p - offset);
		}

		rev_iterator operator-(int offset) {
			return rev_iterator(p + offset);
		}

		T& operator*() { return *p; }
		bool operator==(const rev_iterator& another) { return p == another.p; }
		bool operator!=(const rev_iterator& another) { return !(*this == another); }
	private:
		T* p;
	};

	class const_rev_iterator {
	public:
		const_rev_iterator(T* p) : p{ p } {}
		const_rev_iterator operator++() {
			p--;
			return *this;
		}

		const_rev_iterator operator++(int) {
			const_rev_iterator ret_val = *this;
			p--;
			return ret_val;
		}

		const_rev_iterator operator+(int offset) {
			return const_rev_iterator(p - offset);
		}

		const_rev_iterator operator-(int offset) {
			return const_rev_iterator(p + offset);
		}

		const T& operator*() const { return *p; }
		bool operator==(const const_rev_iterator& another) { return p == another.p; }
		bool operator!=(const const_rev_iterator& another) { return !(*this == another); }

	private:
		T* p;
	};

private:
	T* m_data{ nullptr };
	size_t m_capacity{ 20 };
	size_t m_size{ 0 };
};

template<typename T>
inline Vector<T>::Vector()
{
	m_data = new T[m_capacity];
}

template<typename T>
inline Vector<T>::Vector(size_t count, const T& value)
{
	m_capacity = count * 2;
	m_data = new T[m_capacity];
	for (size_t i = 0; i < count; i++)
		m_data[i] = value;
}

template<typename T>
inline Vector<T>::Vector(size_t count)
{
	m_capacity = count * 2;
	m_data = new T[m_capacity];
}

template<typename T>
inline Vector<T>::Vector(const Vector<T>& another)
{
	m_capacity = another.m_capacity;
	m_size = another.m_size;
	m_data = new T[m_capacity];
	for (size_t i = 0; i < m_size; i++)
		m_data[i] = another.m_data[i];
}

template<typename T>
inline Vector<T> Vector<T>::operator=(const Vector<T>& another)
{
	if (this == &another)
		return *this;

	return Vector(another);
}

template<typename T>
inline Vector<T>::Vector(Vector<T>&& another)
{
	m_capacity = another.m_capacity;
	m_size = another.m_size;
	for (size_t i = 0; i < m_size; i++)
		m_data[i] = std::move(another.m_data[i]);
}

template<typename T>
inline Vector<T> Vector<T>::operator=(Vector<T>&& another)
{
	if (this == &another)
		return *this;

	return Vector<T>(std::forward<Vector<T>&&>(another));
}

template<typename T>
inline Vector<T>::Vector(std::initializer_list<T> ilist)
{
	m_capacity = ilist.size() * 2;
	m_size = 0;
	m_data = new T[m_capacity];

	for (T value : ilist)
		m_data[m_size++] = value;
}

template<typename T>
inline T& Vector<T>::operator[](size_t index)
{
	return m_data[index];
}

template<typename T>
inline const T& Vector<T>::operator[](size_t index) const {
	return m_data[index];
}

template<typename T>
inline T& Vector<T>::at(size_t index) {
	if (index >= m_size)
		throw std::out_of_range{ "vector index out of range" };

	return m_data[index];
}

template<typename T>
inline const T& Vector<T>::at(size_t index) const {
	if (index >= m_size)
		throw std::out_of_range{ "vector index out of range" };

	return m_data[index];
}

template<typename T>
inline T& Vector<T>::front() {
	return m_data[0];
}

template<typename T>
inline const T& Vector<T>::front() const {
	return m_data[0];
}

template<typename T>
inline T& Vector<T>::back() {
	return m_data[m_size - 1];
}

template<typename T>
inline const T& Vector<T>::back() const {
	return m_data[m_size - 1];
}

template<typename T>
inline bool Vector<T>::empty()
{
	return m_size == 0;
}

template<typename T>
inline const bool Vector<T>::empty() const
{
	return m_size == 0;
}

template<typename T>
inline size_t Vector<T>::size()
{
	return m_size;
}

template<typename T>
inline const size_t Vector<T>::size() const
{
	return m_size;
}

template<typename T>
inline size_t Vector<T>::max_size()
{
	return UINT64_MAX;
}

template<typename T>
inline const size_t Vector<T>::max_size() const
{
	return UINT64_MAX;
}

template<typename T>
inline size_t Vector<T>::capacity()
{
	return m_capacity;
}

template<typename T>
inline const size_t Vector<T>::capacity() const
{
	return m_capacity;
}

template<typename T>
inline void Vector<T>::assign(size_t count, const T& value)
{
	for (size_t i = 0; i < count; i++)
		push_back(value);
}

template<typename T>
inline void Vector<T>::assign(std::initializer_list<T> ilist)
{
	for (T& item : ilist)
		push_back(item);
}

template<typename T>
inline void Vector<T>::reserve(size_t new_capacity)
{
	if (new_capacity <= m_capacity)
		return;

	T* tempbuf = new T[m_size];
	for (size_t i = 0; i < m_size; i++)
		tempbuf[i] = m_data[i];

	delete[] m_data;
	m_capacity = new_capacity;
	m_data = new T[m_capacity];

	for (size_t i = 0; i < m_size; i++)
		m_data[i] = tempbuf;

	delete[] tempbuf;
}

template<typename T>
inline void Vector<T>::push_back(const T& val)
{
	if (m_size + 1 >= m_capacity)
		reserve(m_capacity * 2);

	m_data[m_size++] = val;
}

template<typename T>
inline void Vector<T>::clear()
{
	m_size = 0;
}

template<typename T>
inline void Vector<T>::swap(size_t l_index, size_t r_index)
{
	std::swap(m_data.at(l_index), m_data.at(r_index));
}

template<typename T>
inline void Vector<T>::pop_back()
{
	m_size--;
}

template<typename T>
inline void Vector<T>::resize(size_t count)
{
	if (count > m_size) {
		size_t difference = count - m_size;
		for (size_t i = 0; i < difference; i++)
			push_back(T());
	}
	else
		m_size = count;
}

template<typename T>
inline void Vector<T>::resize(size_t count, const T& val)
{
	if (count > m_size) {
		size_t difference = count - m_size;
		for (size_t i = 0; i < difference; i++)
			push_back(val);
	}
	else
		m_size = count;
}

template<typename T>
template<typename ...Args>
inline void Vector<T>::emplace_back(Args ...args)
{
	if (m_size + 1 >= m_capacity)
		reserve(m_capacity * 2);

	m_data[m_size++] = T(args...);
}

template<typename T>
inline Vector<T>::iterator Vector<T>::begin()
{
	return iterator(m_data);
}

template<typename T>
inline Vector<T>::iterator Vector<T>::end()
{
	return iterator(m_data + m_size);
}

template<typename T>
inline Vector<T>::const_iterator Vector<T>::cbegin()
{
	return const_iterator(m_data);
}

template<typename T>
inline Vector<T>::const_iterator Vector<T>::cend()
{
	return const_iterator(m_data + m_size);
}

template<typename T>
inline Vector<T>::rev_iterator Vector<T>::rbegin()
{
	return rev_iterator(m_data + m_size - 1);
}

template<typename T>
inline Vector<T>::rev_iterator Vector<T>::rend()
{
	return rev_iterator(m_data - 1);
}

template<typename T>
inline Vector<T>::const_rev_iterator Vector<T>::crbegin()
{
	return const_rev_iterator(m_data + m_size - 1);
}

template<typename T>
inline Vector<T>::const_rev_iterator Vector<T>::crend()
{
	return const_rev_iterator(m_data - 1);
}

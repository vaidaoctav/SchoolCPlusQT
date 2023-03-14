#pragma once

template <typename TElem>
class IteratorVector;

template <typename TElem>
class Vector {
private:
	int leng;
	int cp;
	TElem* elems;
public:

	/*
	* Default constructor
	*/
	Vector();

	/*
	* Copy constructor
	*/
	Vector(const Vector& ot);

	/*
	* Destructor
	*/
	~Vector();

	/*
	* Operator assignment
	*/
	Vector& operator=(const Vector& ot);

	/*
	* [] operator
	*/
	TElem& operator[](int poz);

	/*
	* Operator assignment for r-value
	*/
	Vector(Vector&& ot);

	/*
	* Copy constructor for r-value
	*/
	Vector& operator=(Vector&& ot);

	/*
	* Return the size of the Vector
	*/
	int size();

	/*
	* Add an element at the end of the list
	*/
	void push_back(TElem value);

	/*
	* Change the size of the Vector
	*/
	void resize(int new_capacity);

	/*
	* Return the adress of the first element of the list
	*/
	TElem* begin();

	/*
	* Return the adress of the last element of the list
	*/
	TElem* end();

	/*
	* Remove the last element of the list
	*/
	void pop_back();

	/*
	* Delete an element
	*/
	void erase(TElem elem);

	friend class IteratorVector<TElem>;
	IteratorVector < TElem > iterator();
};

template<typename TElem>
Vector<TElem>::Vector() :elems{ new TElem[1] }, cp{ 1 }, leng{ 0 }{}

template<typename TElem>
Vector<TElem>::Vector(const Vector& ot) {
	elems = new TElem[ot.cp];
	for (int i = 0; i < ot.leng; i++)
		elems[i] = ot.elems[i];
	leng = ot.leng;
	cp = ot.cp;
}

template<typename TElem>
inline Vector<TElem>::~Vector() {
	delete[] elems;
}

template<typename TElem>
Vector<TElem>& Vector<TElem>::operator=(const Vector<TElem>& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	elems = new TElem[ot.cp];

	for (int i = 0; i < ot.leng; i++)
		elems[i] = ot.elems[i];

	leng = ot.leng;
	cp = ot.cp;

	return *this;
}

template<typename TElem>
inline TElem& Vector<TElem>::operator[](int poz) {
	return elems[poz];
}


template<typename TElem>
Vector<TElem>::Vector(Vector&& ot) {
	elems = ot.elems;
	leng = ot.leng;
	cp = ot.cp;

	ot.elems = nullptr;
	ot.leng = 0;
	ot.cp = 0;
}

template<typename TElem>
Vector<TElem>& Vector<TElem>::operator=(Vector&& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elems;

	elems = ot.elems;
	leng = ot.leng;
	cp = ot.cp;

	ot.elems = nullptr;
	ot.leng = 0;
	ot.cp = 0;
	return *this;
}

template<typename TElem>
inline int Vector<TElem>::size() {
	return leng;
}

template<typename TElem>
void Vector<TElem>::push_back(TElem value) {
	if (cp == leng) {
		resize(2 * cp);
	}
	elems[leng++] = value;
}

template<typename TElem>
inline void Vector<TElem>::resize(int new_capacity) {
	cp = new_capacity;

	int lim;
	if (new_capacity < leng)
		lim = new_capacity;
	else
		lim = leng;

	TElem* aux = new TElem[cp];
	for (int i = 0; i < lim; i++)
		aux[i] = elems[i];

	delete[] elems;
	elems = aux;
}

template<typename TElem>
inline TElem* Vector<TElem>::begin() {
	return elems;
}

template<typename TElem>
inline TElem* Vector<TElem>::end() {
	return &(this->elems[(this->leng) - 1]) + 1;
}

template<typename TElem>
inline void Vector<TElem>::pop_back() {
	if (leng > 0)
		leng--;
}

template<typename TElem>
inline void Vector<TElem>::erase(TElem elem) {
	for (int i = 0; i < this->leng; i++)
		if (elem == this->elems[i]) {
			for (int j = i; j < this->leng - 1; j++)
				this->elems[j] = this->elems[j + 1];
			this->leng--;
			return;
		}
}

template<typename TElem>
inline IteratorVector<TElem> Vector<TElem>::iterator()
{
	return IteratorVector<TElem>(*this);
}










template <typename TElem>
class IteratorVector {
private:
	int poz = 0;
	const Vector<TElem>& v;
public:
	IteratorVector(Vector <TElem>& vct) :v{ vct } {};

	/*
	* Return the value from poz = index
	*/
	TElem value(const int& index);

	/*
	* Return the current value of the iterator
	*/
	TElem current_value();

	/*
	* Move to the next value of the Vector
	*/
	void next();
};

template<typename TElem>
TElem IteratorVector<TElem>::value(const int& index) {
	return v.elems[index];
}

template<typename TElem>
inline TElem IteratorVector<TElem>::current_value() {
	return v.elems[poz];
}

template<typename TElem>
inline void IteratorVector<TElem>::next() {
	poz++;
}
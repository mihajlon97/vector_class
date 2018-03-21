/*
class Const_Iterator {
	public:
		using value_type = Vector::value_type;
		using difference_type = Vector ::difference_type;
		using reference = Vector::reference;
		using pointer = Vector::pointer;
		using iterator_category = std::forward_iterator_tag;
	private:
		pointer ptr;
		const Vector* vec;
	public:
		Const_Iterator() {}
		Const_Iterator(pointer ptr, Vector* vec) : ptr{ptr}, vec{vec} {}
		Const_Iterator(pointer ptr, const Vector* vec) : ptr{ptr}, vec{vec} {}
		const Const_Iterator& operator++() {
			if(*this == vec->end()) throw runtime_error("Out of bounds!");
			++ptr;
			return *this;
		}
		const Const_Iterator operator++(int) {
			const Const_Iterator old(*this);
			++*this;
			return old;
		}
		friend bool operator!=(const Const_Iterator& lop, const Const_Iterator& rop) {
			return lop.ptr != rop.ptr;
		}
		friend bool operator==(const Const_Iterator& lop, const Const_Iterator& rop) {
			return lop.ptr == rop.ptr;
		}
		friend Vector::difference_type operator-(const Vector::Const_Iterator& lop, const Vector::Const_Iterator& rop) { 
			return lop.ptr-rop.ptr;
		}
		const pointer operator->() {
			return ptr;
		}
		const reference operator*() {
			if(*this == vec->end()) throw runtime_error("Out of bounds!");
			return *ptr;
		}
		const reference operator*() const {
			if(*this == vec->end()) throw runtime_error("Out of bounds!");
			return *ptr;
		}
	};
	
	class Iterator {
	public:
		using value_type = Vector::value_type;
		using difference_type = Vector ::difference_type;
		using reference = Vector::reference;
		using pointer = Vector::pointer;
		using iterator_category = std::forward_iterator_tag;
	private:
		pointer ptr;
		Vector* vec;
	public:
		Iterator () {}
		Iterator(pointer ptr, Vector* vec) : ptr{ptr}, vec{vec} {}
		Iterator& operator++() {
			if(*this == vec->end()) throw runtime_error("Out of bounds!");
			++ptr;
			return *this;
		}
		Iterator operator++(int) {
			Iterator old(*this);
			++*this;
			return old;
		}
		friend bool operator!=(const Iterator& lop, const Iterator& rop) {
			return lop.ptr != rop.ptr;
		}
		friend bool operator==(const Iterator& lop, const Iterator& rop) {
			return lop.ptr == rop.ptr;
		}
		pointer operator->() {
			return ptr;
		}
		reference operator*() {
			if(*this == vec->end()) throw runtime_error("Out of bounds!");
			return *ptr;
		}
		const reference operator*() const {
			if(*this == vec->end()) throw runtime_error("Out of bounds!");
			return *ptr;
		}
		operator Const_Iterator() const { return Const_Iterator(this->ptr, this->vec); }
	};
	
public:
	using iterator = Iterator;
	using const_iterator = Const_Iterator;
private:
	static constexpr size_type min_size {5};
	size_type max_size {min_size};
	size_type sz {0};
	pointer values {nullptr};
	
	void new_buf(size_type sz) {
		pointer buf{new value_type[sz]};
		for (size_type i{0}; i < this->sz; ++i) {
			buf[i] = values[i];
		}
		delete[] values;
		values = buf;
		max_size = sz;
	}
public:
	Vector() : Vector(min_size) {}
	Vector(size_type sz) : max_size{sz < min_size ? min_size : sz}, sz{0}, 
						values{new value_type [sz < min_size ? min_size : sz]} {}
	Vector(std::initializer_list<value_type> l) : Vector(l.size()) {
		int i{0};
		sz=l.size();
		for (const auto& value : l) 
			values[i++] = value;
	}		
	Vector(const Vector& v) : Vector(v.max_size) {
		int i{0};
		sz=v.sz;
		for (const auto& value : v) 
			values[i++] = value;
	}
	~Vector() {
		delete[] values;
	}
	Vector& operator= (Vector v) {
		swap(max_size, v.max_size);
		swap(sz, v.sz);
		swap(values, v.values);
		return *this;
	}
	void reserve(size_type sz) {
		if (sz < min_size) sz = min_size;
		if (sz <= max_size) return;
		new_buf(sz);
	}
	void shrink_to_fit() {
		new_buf(sz);
	}
	void push_back(value_type val) {
		if (sz == max_size){
			reserve(max_size*2);
		}
		values[sz++] = val;
	}
	iterator erase (const_iterator pos) {
		auto diff = pos-begin();
		
		if (diff < 0 || static_cast<size_type>(diff) >= sz) {
			throw runtime_error("Iterator out of bounds");
		}
		size_type current {static_cast<size_type>(diff)};
		for (size_type i{current}; i < sz-1; ++i) {
			values[i] = values[i+1];
		}
		--sz;
		return iterator{values+current, this};
	}
	iterator insert (const_iterator pos, const_reference val) {
		auto diff = pos-begin();
		if (diff < 0 || static_cast<size_type> (diff) > sz) {
			throw runtime_error("Iterator out of bounds");
		}
			
			size_type current{static_cast<size_type>(diff)};
			if (sz >= max_size) {
				reserve(max_size*2+1);
			}
			for (size_type i{sz}; i-->current;) {
				values[i+1] = values[i];
			}
			values[current] = val;
			++sz;
			
			return iterator{values+current, this};
		}
	size_type size() {
		return sz;
	}
	bool empty() {
		return !sz;
	}
	void clear() {
		sz=0;
	}
	void pop_back() {
		if(!empty()) {
			sz--;
		}	
	}
	reference operator[] (size_type n) {
		if (sz<=n) throw invalid_argument ("This place is empty!");
		return values[n];
	}
	const reference operator[] (size_type n) const {
		if (sz<=n) throw invalid_argument ("This place is empty!");
		return values[n];
	}
	iterator begin() {
		return iterator(&(this->values[0]), this);
	}
	iterator end() {
		return iterator(&(this->values[sz]), this);
	}
	const_iterator begin() const {
		return const_iterator(values, this);
	}
	const_iterator end() const {
		return const_iterator(values+sz, this);
	}
};
*/



#include <iostream>
#include <initializer_list>
#include <algorithm>

using namespace std;

template <typename T>
class Vector;


template<typename T>
ostream& operator<< (ostream&, const Vector<T>&);



template <typename T>
class Vector{
  public:

  	class ConstIterator;
  	class Iterator;

  	using value_type = T;
  	using size_type = size_t;
  	using difference_type = ptrdiff_t;
  	using reference = value_type&;
  	using const_reference = const value_type&;
  	using pointer = value_type*;
  	using const_pointer = const value_type*;

  	using iterator = Iterator;
  	using const_iterator = ConstIterator;

  private:
  	pointer values;
  	size_type sz;
  	size_type max_sz;

  public:

  	class ConstIterator{
  	  public:
  	  	  using value_type = Vector::value_type;
  		  using difference_type = Vector::difference_type;
  		  using reference = Vector::reference;
          using const_reference = Vector::const_reference;
  		  using pointer = Vector::pointer;
  		  using iterator_category = forward_iterator_tag;
  	  private:
  	  	const_pointer ptr;
  	  public:
  	  	ConstIterator(){this->ptr=0;}
  	  	ConstIterator(pointer p){this->ptr=p;}

        ConstIterator& operator++(){if(*this==end()) throw runtime_error("Out of bounds!"); ptr++; return *this;}
		const_pointer operator->() {return ptr;}
		
		friend bool operator!=(const ConstIterator& lop, const ConstIterator& rop){return (lop.ptr!=rop.ptr);}
		friend bool operator==(const ConstIterator& lop, const ConstIterator& rop){return (lop.ptr==rop.ptr);}

		const_reference operator*() const{if(*this==end()) throw runtime_error("Out of bounds!"); return *ptr;}
        //friend bool operator<(const ConstIterator& lop, const ConstIterator& rop);
        //bool operator<(const ConstIterator& it){return (*ptr<*it.ptr);}
        //bool operator<(const_reference rop)const{return (*ptr<rop);}

        friend difference_type operator-(const ConstIterator& lop, const ConstIterator& rop){
			return lop.ptr - rop.ptr;
		}
		
    };

  	class Iterator{
		public:
			using value_type = Vector::value_type;
			using difference_type = Vector::difference_type;
			using reference = Vector::reference;
			using const_reference = Vector::const_reference;
			using pointer = Vector::pointer;
			using iterator_category = forward_iterator_tag;
		private:
			pointer ptr;

	    public:
			Iterator(){this->ptr=0;}
		    Iterator(pointer p){this->ptr=p;}
		    Iterator& operator++(){ptr++;return *this;}

			
			friend bool operator!=(const Iterator& lop, const Iterator& rop){return static_cast<ConstIterator>(lop)!=rop;}
			
			friend bool operator==(const Iterator& lop, const Iterator& rop){return static_cast<ConstIterator>(lop)==rop;}


		    //bool operator<(const Iterator& it){return (*ptr>*it.ptr);}
			//bool operator<(const_reference it){return (*ptr<it);}

		    reference operator*(){return *ptr;}


			friend difference_type operator-(const Iterator& lop, const Iterator& rop){
				return static_cast<ConstIterator>(lop) - rop;
			}
        	//friend bool operator<(const ConstIterator& lop, const ConstIterator& rop);

        	operator ConstIterator() const{
				return ConstIterator(ptr);
        	}

	};

	static constexpr size_type min_sz{2};

    Vector():Vector(min_sz){};
    Vector(const Vector& v):Vector(){
		for (size_type i{0}; i < v.sz; i++)
			push_back(v.values[i]);
    }

    Vector(initializer_list<value_type> l):Vector(){
		for (const auto& e : l)
			push_back(e);
    }

    Vector& operator=(Vector& v){
		swap(sz, v.sz);
		swap(max_sz, v.max_sz);
		swap(values, v.values);
		return *this;
    }

    Vector(size_type max){
		sz = 0;
		max_sz = (max > min_sz) ? max : min_sz;
		values = new value_type[max_sz];
    }

    ~Vector(){
		delete[] values;
    }

    value_type getvalue(size_type i)const{return this->values[i];}


    value_type sum(){
		if (empty())
			throw runtime_error("Vector ist leer");
		value_type sum = 0;
		for (size_type i = 0; i < sz; i++)
			sum += values[i];
		return sum;
    }

    value_type min(){
		if (empty())
			throw runtime_error("Vector ist leer");
		value_type min = values[0];
		for (size_type i = 1; i < sz; i++)
			if (min > values[i])
			min = values[i];
		return min;
    }


    value_type max() const{
      //if (empty())
    	//  throw runtime_error("Vector ist leer");
      //value_type max = values[0];
      //for (size_type i = 1; i < sz; i++)
      //	if (max < values[i])
    	//  max = values[i];
      //return max;

      //, [] (const_reference l, const_reference r){return l==r;}

      auto it = max_element(begin(), end());
      return *it;
    }

    size_type size() const{return sz;}


    bool empty() const{
		if(sz==0)
			return true;
		return false;
    }

    void pop_back(){
		if (empty())
    		throw runtime_error("Vector ist leer");
		sz--;
		shrink_to_fit();
    }

    void shrink_to_fit(){
		if (max_sz > sz) return;
		change_size(sz < min_sz ? min_sz : sz);
    }

    void push_back(value_type n){
		if (max_sz == sz)
    		change_size(2*max_sz);
		values[sz] = n;
		sz++;
    }

    void reserve(size_type newsize){change_size(newsize);}
		void change_size(size_type newsize){
    	value_type *buf = new value_type [newsize];
    	for (size_type i = 0; i < sz; i++)
    		buf[i] = values[i];
    	delete[] values;
    	values = buf;
    	max_sz = newsize;
    }

    iterator insert (const_iterator pos, const_reference val){
    	auto diff = pos-begin();
    	if(diff<0 || static_cast<size_type>(diff)>sz)
    		throw runtime_error("Iterator out of bounds");
    	size_type current{static_cast<size_type>(diff)};
    	if(sz>=max_sz)
    		reserve(max_sz*2);
    	for(size_t i{sz}; i-- > current;)
    		values[i+1]=values[i];
    	values[current]=val;
    	++sz;
    	return Vector::iterator{values+current};
    }

    iterator erase (const_iterator pos){
    	auto diff = pos-begin();
    	if(diff<0 || static_cast<size_type>(diff)>sz)
    		throw runtime_error("Iterator out of bounds");
    	size_type current{static_cast<size_type>(diff)};

    	for(size_t i{current}; i<sz-1; ++i)
    		values[i]=values[i+1];
    	--sz;
    	return Vector::iterator{values+current};
    }

    void clear(){
      sz = 0;
      shrink_to_fit();
    }

    ostream& printKontra(std::ostream &os) const{
    	os << "Begin: " << *begin() <<endl;
    	os << "End: " << *end() << endl;
    	os << "Size: " << sz << endl;

    	cout << '[';

    	bool first{true};
    	for(const auto& elem : *this){
    	//for(auto it=begin();it!=end();--it){
        if(first)
          first = false;
        else
          os << ", ";
        os << elem;
    	}
    	os << ']';
      return os;
    }

    //Operatoren
    reference operator[](size_type val){
      if (val < 0 || val >= sz)
    		throw runtime_error("Index ist ungueltig");
      return values[val];
    }

    const_reference operator[](size_type val) const{
      if (val <= 0 && val >= sz)
    		throw runtime_error("Index ist ungueltig");
      return values[val];
    }

    iterator begin() {return Iterator{values};}
	iterator end() {return Iterator{values+sz};}
	const_iterator begin() const{return ConstIterator{values};}
	const_iterator end() const{return ConstIterator{values+sz};}

    iterator getIteratorOnPos(size_type i){return Iterator{&values[i]};};
    const_iterator getIteratorOnPos(size_type i)const{return ConstIterator{&values[i]};};

/*

    friend bool operator==(const Vector& lop, const Vector& rop);
    friend bool operator>(const Vector& lop, const Vector& rop);
    friend Vector& operator+(istream&, const Vector&);
    friend Vector operator+(const Vector& lop, const Vector& rop);


    ostream& operator<<(ostream& os){
      print(os);
    }
*/
    ostream& print(ostream& os){
      os << "[";
      for (size_type i = 0; i < sz; i++){
    		os << values[i];
    		if (i != sz - 1){
    	  	os << ", ";
    		}else{
    	  	os << "]";
    	  	break;
    		}
      }
      return os;
    }
	
    istream& operator>>(istream& is){
      char c;
      is >> c;
      if (c != '[') throw runtime_error ("[ expected");

      clear();
      is >> c;
      if (c != ']')
        return is;
      is.putback(c);
      do {
        value_type d;
        is >> d;
        push_back(d);
        is >> c;
        if (c != ',' && c != ']') throw runtime_error (", or ] expected");
      }while (c != ']');

      return is;
    }
};


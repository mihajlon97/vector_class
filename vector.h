#include <iostream>
#include <initializer_list>

using namespace std;

class Vector{
  public:

  	class ConstIterator;
  	class Iterator;

  	using value_type = double;
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
  		  //using iterator_category = Vector::forward_iterator_tag;
  	  private:
  	  	pointer ptr;
  	  public:
  	  	ConstIterator();
  	  	ConstIterator(pointer);

        ConstIterator& operator++();
		    bool operator!=(const ConstIterator&);
        bool operator==(const ConstIterator&);
		    reference operator*();
		    const_reference operator*() const;
  	};


  	class Iterator{
      public:
        using value_type = Vector::value_type;
  		  using difference_type = Vector::difference_type;
  		  using reference = Vector::reference;
        using const_reference = Vector::const_reference;
  		  using pointer = Vector::pointer;

      private:
        pointer ptr;

	    public:
	  	  Iterator();
		    Iterator(pointer);
		    Iterator& operator++();
		    bool operator!=(const Iterator&);
        bool operator==(const Iterator&);

        //Difference in implementation??
		    reference operator*();
		    const_reference operator*() const;
	   };


	  static constexpr size_type min_sz{2};

    Vector():Vector(min_sz){};
    Vector(const Vector& neu);
    Vector(initializer_list<value_type>);
    Vector& operator=(Vector&);
    Vector(size_type);
    ~Vector();

    value_type getvalue(size_type) const;
    value_type sum();
    value_type min();
    value_type max();

    size_type size() const;

    bool empty() const;

    void pop_back();
    void shrink_to_fit();
    void push_back(value_type);
    void reserve(size_type);
	  void change_size(size_type);

    //const_iterator operator ConstIterator();
    iterator insert (const_iterator, const_reference);
    iterator erase (const_iterator);

    //void insert (size_type, value_type);
    //void erase (size_type);
    void clear();

    ostream& printKontra(ostream &) const;
    ostream& print(ostream &) const;
    istream& read(istream &);

    //Operatoren
    reference operator[](size_type);
    const_reference operator[](size_type) const;

    iterator begin() {return Iterator{values};}
	  iterator end() {return Iterator{values+sz};}
	  const_iterator begin() const{return ConstIterator{values};}
	  const_iterator end() const{return ConstIterator{values+sz};}

    //friend difference_type operator-(const const_iterator& lop, const const_iterator& rop);

    friend bool operator==(const Vector& lop, const Vector& rop);
    friend bool operator>(const Vector& lop, const Vector& rop);
    friend ostream& operator<<(ostream&, const Vector&);
    friend istream& operator>>(istream&, const Vector&);
    friend Vector& operator+(istream&, const Vector&);
    friend Vector operator+(const Vector& lop, const Vector& rop);

};

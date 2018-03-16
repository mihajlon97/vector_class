#include <iostream>
#include <stdexcept>
#include "vector.h"

using namespace std;

// ------- Vector ConstIterator Methoden ---------


Vector::ConstIterator::ConstIterator(){
	this->ptr = 0;
}

Vector::ConstIterator::ConstIterator(Vector::pointer p){
	this->ptr = p;
}

Vector::ConstIterator& Vector::ConstIterator::operator++(){
	this->ptr++;
}

bool Vector::ConstIterator::operator!=(const ConstIterator& it){
	return (*ptr!=*it.ptr);
}

bool Vector::ConstIterator::operator==(const ConstIterator& it){
	return (*this!=it);
}

Vector::ConstIterator::reference Vector::ConstIterator::operator*(){
	return *ptr;
}

Vector::ConstIterator::const_reference Vector::ConstIterator::operator*() const{
	return *ptr;
}





// ------- Vector Iterator Methoden ---------
Vector::Iterator::Iterator(){
	this->ptr = 0;
}

Vector::Iterator::Iterator(Vector::pointer p){
	this->ptr = p;
}

Vector::Iterator& Vector::Iterator::operator++(){
	++this->ptr;
}

bool Vector::Iterator::operator!=(const Iterator& it){
	return (*ptr!=*it.ptr);
}

bool Vector::Iterator::operator==(const Iterator& it){
	return (*this!=it);
}

Vector::Iterator::reference Vector::Iterator::operator*(){
	return *ptr;
}

Vector::Iterator::const_reference Vector::Iterator::operator*() const{
	return *ptr;
}





//------- Vector public Methoden --------
Vector::Vector(size_type max){
  sz = 0;
  max_sz = (max > min_sz) ? max : min_sz;
  values = new value_type[max_sz];
}

Vector::Vector(const Vector& vek):Vector::Vector(){
  for (size_type i = 0; i < vek.sz; i++)
    push_back(vek.values[i]);
}

Vector::Vector(initializer_list<value_type> liste):Vector(){
  for (const auto& element : liste)
    push_back(element);
}

Vector& Vector::operator=(Vector& neu){
  swap(sz, neu.sz);
  swap(max_sz, neu.max_sz);
  swap(values, neu.values);
  return *this;
}

Vector::~Vector(){
  delete[] values;
}

void Vector::change_size(size_type newsize) {
	double *buf = new value_type [newsize];
	for (size_type i = 0; i < sz; i++)
		buf[i] = values[i];
	delete[] values;
	values = buf;
	max_sz = newsize;
}

Vector::value_type Vector::getvalue(size_type index) const{
   return this->values[index];
}

Vector::size_type Vector::size() const{
  return sz;
}

bool Vector::empty() const{
  if(sz == 0)
    return true;
  return false;
}

void Vector::pop_back(){
  if (empty())
		throw runtime_error("Vector ist leer");
  sz--;
  shrink_to_fit();
}

void Vector::push_back(value_type n){
  if (max_sz == sz)
		change_size(2*max_sz);
  values[sz] = n;
  sz++;
}

void Vector::shrink_to_fit(){
  if (max_sz > sz) return;
  change_size(sz < min_sz ? min_sz : sz);
}

void Vector::reserve(size_type newsize){
  change_size(newsize);
}

double& Vector::operator[](size_type val){
  if (val < 0 || val >= sz)
		throw runtime_error("Index ist ungueltig");
  return values[val];
}

const double& Vector::operator[](size_type val) const{
  if (val <= 0 && val >= sz)
		throw runtime_error("Index ist ungueltig");
  return values[val];
}

void Vector::clear(){
  sz = 0;
  shrink_to_fit();
}

ostream& Vector::print(std::ostream &os) const{
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

ostream& Vector::printKontra(std::ostream &os) const{
	os << "Begin: " << *begin() <<endl;
	os << "End: " << *end() << endl;
	os << "Size: " << sz << endl;
	os << "[";

	for(Vector::const_reference elem : *this){
		os << elem;
		//print [1,2,3, statt [1,2,3]
		if (elem != end()){
	  	os << ", ";
		}else{
	  	os << "]";
	  	break;
		}
	}
  return os;
}

istream& Vector::read(istream &is){
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

Vector::value_type Vector::sum(){
  if (empty())
	throw runtime_error("Vector ist leer");
  value_type sum = 0;
  for (size_type i = 0; i < sz; i++)
  	sum += values[i];
  return sum;
}

Vector::value_type Vector::min(){
  if (empty())
	throw runtime_error("Vector ist leer");
  value_type min = values[0];
  for (size_type i = 1; i < sz; i++)
  	if (min > values[i])
	  min = values[i];
  return min;
}

Vector::value_type Vector::max(){
  if (empty())
	throw runtime_error("Vector ist leer");
  value_type max = values[0];
  for (size_type i = 1; i < sz; i++)
  	if (max < values[i])
	  max = values[i];
  return max;
}

//Operator funktioniert nicht

//Vector::const_iterator Vector::operator ConstIterator(){
//	return Vector::const_iterator();
//}


Vector::iterator Vector::insert(Vector::const_iterator pos, Vector::const_reference val) {
/*
	auto diff = pos-begin();
	if(diff<0 || static_cast<size_type>(diff)>sz)
		throw runtime_error("Iterator out of bounds");
	size_type current{static_cast<size_type>(diff)};
	if(sz>=max_sz)
		reserve(max_sz*2); //max_sz*2+10, wenn Ihr Container max_sz==0 erlaubt
	for(size_t i {sz}; i-->current;)
		values[i+1]=values[i];
	values[current]=val;
	++sz;
	return Vector::iterator{values+current};
	*/
}

Vector::iterator Vector::erase(Vector::const_iterator pos) {
/*
	auto diff = pos-begin();
	if(diff<0 || static_cast<size_type>(diff)>sz)
		throw runtime_error("Iterator out of bounds");
	size_type current{static_cast<size_type>(diff)};

	for(size_t i {current}; i<sz-1; ++i)
		values[i]=values[i+1];
	--sz;
	return Vector::iterator{values+current};
	*/
}

/*
void Vector::insert (size_type pos, value_type wert){
  if (pos < 0 || pos >= sz)
	throw runtime_error("Index ist ungueltig");
  else{
    if (max_sz == sz)
		reserve (2*max_sz);
    for (size_type i = sz; i != pos; i--)
  		values[i] = values [i-1];
    values[pos] = wert;
  }
  sz++;
}

void Vector::erase(size_type pos){
  if (pos < 0 || pos >= sz)
	throw runtime_error("Index ist ungueltig");
  else{
    for (size_type i = pos; i < sz; i++)
  	values[i] = values [i+1];
  }
  sz--;
  shrink_to_fit();
}
*/
ostream& operator<<(ostream& os, const Vector& v){
  return v.print(os);
}

istream& operator>>(istream& is, Vector& v){
 return v.read(is);
}

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



// ------- Vector Iterator Methoden ---------


Vector::Iterator::Iterator(Vector::pointer p){
	this->ptr = p;
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
	}
	else{
	  os << "]";
	  break;
	}
  }
  return os;	
}

istream& Vector::read(istream &is){
  char c; 
  is >> c;
  if (c != '[')
	throw runtime_error ("[ expected");
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

ostream& operator<<(ostream& os, const Vector& v){
  return v.print(os);
}

istream& operator>>(istream& is, Vector& v){
 return v.read(is);
}

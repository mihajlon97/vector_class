#include<iostream>
#include"vector.h"
using namespace std;


//Vector::difference_type operator-(const Vector::ConstIterator& lop, const Vector::ConstIterator& rop){
//	return lop.ptr - rop.ptr;
//}

int main() {

  Vector::value_type val;
  Vector::size_type size;
  Vector::difference_type diff;
  Vector::reference ref = val;
  Vector::const_reference cref = val;
  Vector::pointer ptr = &val;
  Vector::const_pointer cptr = &val;
  Vector::iterator *it;
  Vector::const_iterator *cit;



  Vector v{1,2,3};
  v.printKontra(cout);

  return 0;
}

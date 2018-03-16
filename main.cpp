#include <iostream>
#include "vektor.h"

using namespace std;

bool operator==(const Vektor& lop, const Vektor& rop){
    if (lop.sz != rop.sz)
		return false;
    for (size_t i = 0; i < lop.sz; i++)
		if (lop[i] != rop.values[i])
	 		return false;
    return true;
}

bool operator!=(const Vektor& lop, const Vektor& rop){
    if (lop == rop)
		return false;
    return true;
}

bool operator>(const Vektor& lop, const Vektor& rop){
    size_t i = 0;
    while (i < lop.sz && i<rop.sz && lop.values[i] == rop.values[i]) ++i;
	return (i >= rop.sz && lop.sz>rop.sz) || (i <= rop.sz && i < lop.sz && lop.values[i] > rop.values[i]);
}

bool operator<=(const Vektor& lop, const Vektor& rop){
    if (lop > rop)
		return false;
    return true;
}

bool operator>=(const Vektor& lop, const Vektor& rop){
    if (lop > rop && lop == rop)
		return true;
    return false;
}

bool operator<(const Vektor& lop, const Vektor& rop){
    if (lop > rop && lop != rop)
		return true;
    return false;
}


Vektor operator+(const Vektor& lop, const Vektor& rop){
    Vektor sum(lop.sz + rop.sz);
    while(sum.sz != (lop.sz + rop.sz))
	  if (sum.sz < lop.sz)
	    sum.push_back(lop.getvalue(sum.sz));
	  else
	    sum.push_back(rop.getvalue(sum.sz - lop.sz));
    return sum;
}

int main(){
  Vektor v1;
  Vektor v2(3);
  v2.push_back(10);
  v2.push_back(11);
  v2.push_back(12);
  v2.print(cout);
  cout << endl << "Size : " << v2.size() << endl;
  v2.insert(2,13);
  cout << "Size : " << v2.size() << endl;

  Vektor v3;
  v3.push_back(20);
  v3.push_back(13);
  v3.push_back(42);
  cout << v2 << v3 << endl;

  Vektor v4 {v2 + v3};
  v4.print(cout);
  cout << " size :" << v4.size() << endl;

  Vektor v5(v4);
  v5.print(cout);
  cout << endl << endl;
  Vektor v6{v2};
  v6.print(cout);

  cout << endl << endl;
  initializer_list<double> liste = {1,2,3,4,5,6};

  Vektor v7{liste};
  v7.print(cout);



  return 0;
}

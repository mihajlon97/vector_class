#include<iostream>
#include"vector.h"
using namespace std;


Vector<?>::difference_type operator-(const Vector::ConstIterator& lop, const Vector::ConstIterator& rop){
	return lop.ptr - rop.ptr;
}

bool operator<(const Vector<?>::ConstIterator& lop, const Vector::ConstIterator& rop){
	return lop.ptr<rop.ptr;
}
bool myfn(Vector::const_reference l, Vector::const_reference r){return l<r;}


int main(){
	Vector<?> a = Vector();
	try{
		cout << a[0] << '\n';
	}
	catch(exception& e){
		cout << "woups" << '\n';
	}
	a.push_back(12);
	cout << a[0] << '\n';
	Vector<?> b = Vector(a);
	cout << b[0] << '\n';
	Vector<?> c = Vector{1,3,4};
	cout << c[2] << '\n';
	c = b;
	cout << c[0] << '\n';
	c[0] = 5;
	cout << c[0] << '\n';
	cout << b[0] << '\n';

	cout << "Size, empty, clear \n";
	cout << a.size() << '\n';
	a.empty() ? cout << "yes \n" : cout << "no \n";
	a.clear();
	cout << a.size() << '\n';
	a.empty() ? cout << "yes \n" : cout << "no \n";

	cout << "Pop back and [] \n";
	Vector d = Vector{5,6,7,8};
	d.pop_back();
	try{
		cout << d[3] << '\n';
	}
	catch(exception e){
		cout << "woups2" << '\n';
	}
	d.print(cout);
	cout << endl << "---------Test Erase-------" << endl;
	cout << "Erase pos: 1"<< endl;
	d.erase(d.getIteratorOnPos(1));
	d.print(cout);

	cout << endl << "---------Test Insert-------" << endl;
	cout << "Insert:8 - pos: 1"<< endl;
	d.insert(d.getIteratorOnPos(1),8);
	d.print(cout);

	cout << endl << "---------Test Algorithms-------" << endl;
	Vector algo{7, 1.4, 8.2, 9, -4.5, -0.5};
	algo.print(cout);
	cout << endl;
	cout << "Sum: " << algo.sum() << endl;
	auto be=d.begin();
	auto en=d.end();
	cout << "Begin: " << *be << endl;
	cout << "End: " << *en << endl;

	auto it = max_element(be,en, [] (Vector::const_reference l, Vector::const_reference r){return l>r;});
	cout << "Max: " << *it << endl;
	cout << "Max: " << d.max() << endl;
	cout << "Min: " << d.min() << endl;


	return 0;
}

/*
Ausgabe:
	woups
	12
	12
	4
	12
	5
	12
	Size, empty, clear
	1
	no
	0
	yes
	Pop back and []
	woups2
*/

#include<iostream>
#include<unordered_map>
#include<stdexcept>
#include<algorithm>
#include<numeric>
#include<iterator>
#include"vector.h"
using namespace std;

class Person {
  string vorname;
  string zuname;
  int alter;
public:
  Person() {} //notwendig um leere Arrayeintraege zu initialisieren
  Person(string vorname, string zuname, int alter) : vorname{vorname}, zuname{zuname}, alter{alter} {}
  virtual ~Person() {}
  string getName() const {return zuname+" "+vorname;}
  int getAlter() const {return alter;}
  void setAlter(int alter) {
    if (alter<0) throw runtime_error("alter muss >= 0 sein!");
    this->alter = alter;
  }
  virtual bool operator<(const Person& p)const{
	  return (this->getAlter()<p.getAlter());
  }
  virtual ostream& print(ostream& o) const {
    return o<<'['<<zuname<<' '<<vorname<<' '<<alter<<']';
  }
};

class Angestellte: public Person {
  int personal_nummer;
public:
  Angestellte() : Person() {} //notwendig, um leere Arrayeintraege zu initialisieren
  Angestellte(string vorname, string zuname, int alter, int personal_nummer) : Person{vorname, zuname, alter}, personal_nummer{personal_nummer} {}
  ostream& print(ostream& o) const override {
    o<<'*'<<personal_nummer<<'*';
    return Person::print(o);
  }
};

ostream& operator<<(ostream&o, const Person& p) {
  return p.print(o);
}

int main() {
  //Napravi Int Vector i odradi sumu preko lambda expression funkcije ->15
  Vector<int> vi {1,2,3,4,5};
  cout<<accumulate(vi.begin(), vi.end(), 0, [] (int sum, int elem) {return sum+elem;})<<'\n';

   //Napravi String Vector i odradi erase na iterator gde je "bb" 
  Vector<string> vs {"a","bb","ccc"};
  vs.erase(find(vs.begin(), vs.end(), "bb"));
  
  //Dodaj na svaki element u String Vectoru char "z" i ispisi Vector ->az cccz
  for (auto& s : vs) s+="z";
  for (const auto& s : vs) cout<<s<<' ';
  cout<<'\n';

  //Napravi Angestellte Vector
  Vector<Angestellte> va {Angestellte{"Otto","Mueller",39,5}, Angestellte{"Hans","Bauer",36,1}, Angestellte{"Lisa","Mueller",25,2}, Angestellte{"Maria", "Mayer",40,3}};
  
  //Napravi Person Vector
  Vector<Person> vp;
  
  //Kopiraj elemente iz Angestellte Vector u Person Vector pomocu back_inserter (bez *personal_nummer*)
  copy(va.begin(), va.end(), std::back_inserter(vp));
  
  //Ispisi Angestellte Vector
  for (const auto& p : va) cout << p << " ";
  cout << '\n';
   //Ispisi Person Vector
  for (const auto& p : vp) cout << p << " ";

  cout<<"\n\n";
  
  //Pos je jednak String Vectoru
  auto pos = vs.begin();
  
  //Transformisi Vector String u Vector Angestellte 
  transform(va.begin(), va.end(), std::inserter(vs,++pos), [] (const Angestellte& a) {return a.getName();});
  for_each(vs.begin(), vs.end(), [] (const string& s) {cout<<s<<'\n';});
  cout<<'\n';

  // Was fehlt in der Klasse Person, damit das folgende Statement kompiliert? -> Fehlt operator <
  // Warum fehlt das nicht auch in der Klasse Angestellte? -> Weil die Mutterklasse das schon hat
  cout << "Max Alter: " << *max_element(va.begin(), va.end()) << endl;
  cout << "Min Alter: " << *min_element(va.begin(), va.end()) << endl;
  

  // Geben Sie nun analog die juengste Angestellte aus (ohne weitere Aenderungen in Person bzw. Angestellte) - Fertig 

  return 0;
}


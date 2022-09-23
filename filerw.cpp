#include <iostream>
#include <fstream>
using namespace std;

int main () {
  ifstream myfile;
  myfile.open ("example.txt");
//   myfile << 10.12 <<"\t"<<1.23<<"\n";

  float a,b;
  myfile >> a>>b;
  cout<<a<<"\t"<<b;
  myfile.close();
    return 0;
}
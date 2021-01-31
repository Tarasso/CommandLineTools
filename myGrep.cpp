#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
 ifstream input;
 input.open(argv[1]);
 string line = "";
 string search = argv[2];
 while(getline(input, line))
 {
  if(line.find(search) != string::npos)
  {
   cout << line << endl;
  }
 }
}

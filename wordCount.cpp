#include <iostream>
#include <fstream>

using namespace std;

int main(int charc, char** argv)
{
 ifstream input;
 input.open(argv[1]);
 int lineCount = 0;
 int wordCount = 0;
 int charCount = 0;
 string line = "";
 char nextChar;
 while(getline(input,line))
 {
  lineCount += 1;
  for (int i=0; i<int(line.length()); i++)
   {
    charCount += 1;
    nextChar = line.at(i);
    if(isspace(line[i]))
     wordCount += 1;
   }
 }
 
 cout << lineCount << " " << wordCount << " " << charCount << endl;
}

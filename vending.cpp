#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

vector<string> names;
vector<int> quantities;
vector<float> prices;
float balence = 0.0;

//prints what is in the machine
void printInventory()
{
  cout << endl;
  cout << "*******************************" << endl;
  cout << setw(9) << "Item" << "    " << setw(8) << "Quantity" << "    " << setw(6) << "Prices" << endl;
  for(int i = 3; i < names.size(); i++)
  {
    cout << setw(9) << names.at(i) << "    " << setw(8) << quantities.at(i) << "    " << setw(6) << prices.at(i) << endl;
  }
  cout << "*******************************" << endl;
  cout << endl;
}

//formatted print for the balence
void printBalence()
{
  cout << "Balence: $ " << balence << endl << endl;
}

//adds the correct amount to balence
void addBalence(string currentCoin)
{
  if(currentCoin=="quarter")
  {
    balence += .25;
    quantities.at(0) += 1; //increases quarters by 1
  }
  else if(currentCoin=="dime")
  {
    balence += .1;
    quantities.at(1) += 1; //increases dimes by 1
  }
  else if(currentCoin=="nickel")
  {
    balence += .05;
    quantities.at(2) += 1; //increases nickels by 1
  }
  else
    cout << currentCoin << " is not supported." << endl;
}

//add coins to machine
void addCoins(string line)
{
  string currentCoin;
  for(int i=0;i<line.size();i++)
  {
      if(isspace(line[i]))
      {
        addBalence(currentCoin);
        currentCoin="";
      }
      else
      {
        currentCoin = currentCoin + line[i];
      }
  }
  addBalence(currentCoin);
}

//charges amount to balence
void decreaseBalence(float cost)
{
  balence -= cost;
  if(balence<.01)
    balence = 0;
}

//finds item in inventory
int find(string name)
{
  for(int i = 0; i < names.size(); i++)
  {
    if(names.at(i)==name)
      return i;
  }

  return -1;
}

//handles the purchase of an item
void press(string item, int index, bool isCoin = false)
{
  if(index==-1)
    cout << "Item unavailable." << endl;
  else
  {
    int quantity = quantities.at(index);
    float cost = prices.at(index);
    if(isCoin)
    {
      if(quantity>0)
      {
        cout << "Dispensing: " << item << endl;
        quantities.at(index) -= 1;
        decreaseBalence(cost);
        printBalence();
      }
    }
    else if(item=="quarter" || item=="dime" || item=="nickel")
      cout << "Haha nice try. Try again." << endl;
    else if(quantity==0)
      cout << "Sorry, we are out of " << item << ". :(" << endl;
    else if(cost>balence)
      cout << "Insufficient funds." << endl;
    else
    {
      cout << "Dispensing: " << item << endl;
      quantities.at(index) -= 1;
      decreaseBalence(cost);
      printInventory();
      printBalence();
    }
  }
}

//returns change to the user
void makeChange()
{
  while(balence>0)
  {
    if(balence>=.25)
      press("quarter",0,true);
    if(balence>=.10)
      press("dime",1,true);
    if(balence>=.05)
      press("nickel",2,true);
  }
  cout << "Change made. Remaining balence: $" << balence << endl;
}

int main(int argc, char** argv)
{
  //read input from file
  ifstream input;
  input.open(argv[1]);
  if(!input.is_open())
  {
    cout << "Unable to open file, please enter a valid file" << endl;
  }
  else{
  string name;
  int quantity;
  float price;

  //store input
  while(input >> name >> quantity >> price)
  {
    names.push_back(name);
    quantities.push_back(quantity);
    prices.push_back(price);
  }

  //initial print
  printInventory();
  printBalence();


  //constantly directs user input
  string line;
  while(getline(cin,line))
  {
    if(line.find("quit")!=string::npos) //exit program
    {
      cout << "\nExiting Program" << endl;
      break;
    }
    else if(line.find("press")!=string::npos) //buying an iten
    {
      string item = line.substr(line.find(' ')+1,line.size());
      int index = find(item);
      press(item,index);
    }
    //add coins to balence
    else if(line.find("quarter")!=string::npos || line.find("dime")!=string::npos || line.find("nickel")!=string::npos)
    {
      addCoins(line);
      printInventory();
      printBalence();
    }
    else if(line.find("change")!=string::npos) //returns change
      makeChange();
    else //command not understood
    {
      cout << "\nPlease enter a valid command." << endl;
    }

  }
  }
}

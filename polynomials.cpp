#include<iostream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

vector<string> split(string s, char c)
{
  istringstream ss(s);
  string token;
  vector<string> tokens;
  while(getline(ss,token,c))
    tokens.push_back(token);
  return tokens;
}

void vecPrint(vector<string> vec)
{
  for(int i = 0; i < vec.size(); i++)
  {
    cout << vec[i] << ",";
  }
  cout << endl;
}

void throwError()
{
  cout << "Invalid Input" << endl;
  cout << "Valid Arguments:" << endl;
  cout << "quit - exits the program" << endl;
  cout << "<poly> - read it in; print it out" << endl;
  cout << "SUM <poly> <poly> - prints out the sum of 2 polynomials" << endl;
  cout << "PROD <poly> <poly> - prints out the product of 2 polynomials" << endl;
  cout << "DERIV <poly> - creates the derivative a polynomial and prints it out" << endl;
  cout << "ROOT <poly> - use NewtonRaphson iteration to find a root and print it out" << endl;
}

class polynomial
{
public:
  vector<string> signedTerms;
  vector<int> pows;
  vector<int> coes;
  void clearEmpty()
  {
    for(int i = signedTerms.size()-1; i >= 0; i--)
    {
      if(signedTerms[i]=="")
        signedTerms.erase(signedTerms.begin()+i);
    }
  }
  polynomial(string input)
  {
    vector<string> positives = split(input,'+');
    for(int i = 0; i < positives.size(); i++)
    {
      if(positives[i][0]=='-')
        continue;
      else
        positives[i] = "+" + positives[i];
    }
    for(int i = 0; i < positives.size(); i++)
    {
      vector<string> negatives = split(positives[i],'-');
      signedTerms.push_back(negatives[0]);
      for(int j = 1; j < negatives.size(); j++)
      {
        negatives[j] = "-" + negatives[j];
        signedTerms.push_back(negatives[j]);
      }
    }
    clearEmpty();
    for(int i = 0; i < signedTerms.size(); i++)
    {
      pows.push_back(getPower(signedTerms[i]));
      if(signedTerms[i].find('x')==string::npos)
      {
        if(signedTerms[i].find('+')!=string::npos)
        {
          coes.push_back(stoi(signedTerms[i].substr(1)));
          continue;
        }
        else
        {
          coes.push_back(stoi(signedTerms[i]));
          continue;
        }
      }
      vector<string> terms1 = split(signedTerms[i],'x');
      int co1;
      if(terms1[0].size()==1 && terms1[0]=="+")
        co1 = 1;
      else if(terms1[0].size()==1 && terms1[0]=="-")
        co1 = -1;
      else
      {
        if(terms1[0].find('+')!=string::npos)
          terms1[0] = terms1[0].substr(1);

        co1 = stoi(terms1[0]);
      }
      coes.push_back(co1);
    }
  }
  polynomial(vector<string> terms)
  {
    signedTerms = terms;
    clearEmpty();
    for(int i = 0; i < signedTerms.size(); i++)
    {
      pows.push_back(getPower(signedTerms[i]));
      if(signedTerms[i].find('x')==string::npos)
      {
        if(signedTerms[i].find('+')!=string::npos)
        {
          coes.push_back(stoi(signedTerms[i].substr(1)));
          continue;
        }
        else
        {
          coes.push_back(stoi(signedTerms[i]));
          continue;
        }
      }
      vector<string> terms1 = split(signedTerms[i],'x');
      int co1;
      if(terms1[0].size()==1 && terms1[0]=="+")
        co1 = 1;
      else if(terms1[0].size()==1 && terms1[0]=="-")
        co1 = -1;
      else
      {
        if(terms1[0].find('+')!=string::npos)
          terms1[0] = terms1[0].substr(1);

        co1 = stoi(terms1[0]);
      }
      coes.push_back(co1);
    }
  }
  int getPower(string term)
  {
    int powerNum;
    if(term.find("^")==string::npos)
    {
      if(term.find("x")==string::npos)
        powerNum = 0;
      else
        powerNum = 1;
    }
    else
    {
      int pos = term.find("^")+1;
      powerNum = stoi(term.substr(pos));
    }
    return powerNum;
  }
  string termSum(string term1, string term2, int power)
  {
    if(term1.find('x')==string::npos)
      return to_string(stoi(term1)+stoi(term2));
    string newTerm;
    vector<string> terms1 = split(term1,'x');
    int co1;
    if(terms1[0].size()==1)
      co1 = 1;
    else
    {
      if(terms1[0].find('+')!=string::npos)
        terms1[0] = terms1[0].substr(1);

      co1 = stoi(terms1[0].substr(1));
    }
    vector<string> terms2 = split(term2,'x');
    int co2;
    if(terms2[0].size()==1)
      co2 = 1;
    else
    {
      if(terms2[0].find('+')!=string::npos)
        terms2[0] = terms2[0].substr(1);
      co2 = stoi(terms2[0].substr(1));
    }
    int newCo = co1 + co2;
    if(newCo > 0)
      newTerm = "+";
    else if (newCo < 0)
      newTerm = "-";
    else
      return "";
    if(power==1)
      newTerm += to_string(newCo)+"x";
    else
      newTerm += to_string(newCo)+"x^"+to_string(power);
    return newTerm;
  }
  polynomial sum(polynomial other)
  {
    vector<string> ans;
    for(int i = 0; i < signedTerms.size(); i++)
    {
      if(signedTerms[i]=="")
        continue;
      ans.push_back(signedTerms[i]);
    }
    for(int i = 0; i < other.signedTerms.size(); i++)
    {
      if(other.signedTerms[i]=="")
        continue;
      ans.push_back(other.signedTerms[i]);
    }
    polynomial p(ans);
    p.combineLikeTerms();
    return p;
  }
  void print()
  {
    for(int i = 0; i < signedTerms.size(); i++)
    {
      if(i==0 && signedTerms.size()==1 && signedTerms[0]=="0")
        {
          cout << "0" << endl;
          break;
        }
      if(signedTerms[i]=="0")
        continue;

      if(i==0 && signedTerms[i][0]=='+')
        cout << signedTerms[i].substr(1);
      else
        cout << signedTerms[i];
    }
    cout << endl;
  }
  polynomial deriv()
  {
    vector<string> ret;
    for(int i = 0; i <signedTerms.size(); i++)
    {
      if(signedTerms[i]=="")
        continue;
      int po = getPower(signedTerms[i]);
      vector<string> terms = split(signedTerms[i],'x');
      int co;
      bool isNeg=false;
      if(terms[0][0]=='-')
        isNeg=true;
      if(terms[0].size()==1)
        co = 1;
      else
        co = stoi(terms[0].substr(1));
      int newCo = po*co;
      po--;
      string ans;
      if(isNeg)
        ans = "-"+to_string(newCo);
      else
        ans = "+"+to_string(newCo);
      if(po==1)
        ret.push_back(ans+"x");
      else if(po==0)
        ret.push_back(ans);
      else if(po==-1)
        ret.push_back("0");
      else
        ret.push_back(ans+"x^"+to_string(po));
    }
    polynomial newPoly(ret);
    return newPoly;
  }
  float eval(float x)
  {
    float sum = 0;
    for(int i = 0; i < signedTerms.size(); i++)
    {
      int po = pows[i];
      int co = coes[i];
      sum += pow(x,po)*co;
    }
    return sum;
  }
  void root()
  {
    float difference = 9999999;
    float tol = .000001;
    float x = 0;

    double h = eval(x) / deriv().eval(x);
    while (abs(h) >= tol)
    {
        h = eval(x)/deriv().eval(x);
        x = x - h;
    }
    cout << "root(P): " << x << " P(r)= " << eval(x) << endl;
  }
  void combineLikeTerms()
  {
    vector<string> newTerms;
    int maxPow = 0;
    for(int i = 0; i < pows.size(); i++)
    {
      if (pows[i] > maxPow)
        maxPow = pows[i];
    }

    for(int i = maxPow; i >= 0; i--)
    {
      int sum = 0;
      for(int j = 0; j < signedTerms.size(); j++)
      {
        if(i == pows[j])
          sum += coes[j];
      }

      string newTerm;
      if(sum>0)
        newTerm += "+";

      if(sum==0)
        continue;
      if(sum!=1)
        newTerm += to_string(sum);

      if(i==1)
        newTerm += "x";
      else if(i==0)
        newTerm += "";
      else
        newTerm += "x^"+to_string(i);

    newTerms.push_back(newTerm);
    }
    signedTerms = newTerms;
  }
  polynomial prod(polynomial other)
  {
    vector<string> ret;
    for(int i = 0; i < signedTerms.size(); i++)
    {
      int po = getPower(signedTerms[i]);
      vector<string> terms = split(signedTerms[i],'x');
      bool isNeg=false;
      if(terms[0][0]=='-')
        isNeg=true;

      int co = coes[i];

      for(int j = 0; j < other.signedTerms.size(); j++)
      {
        int po2 = getPower(other.signedTerms[j]);
        vector<string> terms2 = split(other.signedTerms[j],'x');
        bool isNeg2=false;
        if(terms2[0][0]=='-')
          isNeg2=true;
        int co2 = other.coes[j];

        int poNew = po + po2;
        int coNew = co * co2;

        string ans;
        if(isNeg)
          ans = to_string(coNew);
        else
          ans = "+"+to_string(coNew);
        if(poNew==1)
          ret.push_back(ans+"x");
        else if(poNew==0)
          ret.push_back(ans);
        else if(poNew==-1)
          continue;
        else
          ret.push_back(ans+"x^"+to_string(poNew));
      }
    }
    polynomial retPoly(ret);
    retPoly.combineLikeTerms();
    return retPoly;
  }
};

int main()
{
  string line;
  while(getline(cin,line))
  {
    vector<string> words = split(line,' ');
    if(line.find("quit")!=string::npos) //exit program
    {
      cout << "Exiting Program" << endl;
      break;
    }
    else if(line.find("deriv")!=string::npos)
    {
      if(words.size()!=2)
        throwError();
      else
      {
        polynomial poly1(words[1]);
        cout << "P = ";
        poly1.print();
        cout << "dP/dx = ";
        poly1.deriv().print();
        cout << endl;
      }
    }
    else if(line.find("sum")!=string::npos)
    {
      if(words.size()!=3)
        throwError();
      else
      {
        polynomial poly1(words[1]);
        polynomial poly2(words[2]);
        cout << "P = ";
        poly1.print();
        cout << "Q = ";
        poly2.print();
        cout << "P+Q = ";
        poly1.sum(poly2).print();
        cout << endl;
      }
    }
    else if(line.find("prod")!=string::npos)
    {
      if(words.size()!=3)
        throwError();
      else
      {
        polynomial poly1(words[1]);
        polynomial poly2(words[2]);
        cout << "P = ";
        poly1.print();
        cout << "Q = ";
        poly2.print();
        cout << "P*Q = ";
        poly1.prod(poly2).print();
        cout << endl;
      }
    }
    else if(line.find("root")!=string::npos)
    {
      if(words.size()!=2)
        throwError();
      else
      {
        polynomial poly1(words[1]);
        cout << "P = ";
        poly1.print();
        poly1.root();
        cout << endl;
      }
    }
    else if(words.size()==1)
    {
      polynomial poly1(line);
      poly1.print();
      cout << endl;
    }
    else
      throwError();
  }
}

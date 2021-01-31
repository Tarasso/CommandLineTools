#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

int startDayofMonth;
int numDays;

//Gauss's algorithm, Disparate variation to calculate day of the week a month starts on
int startDay(int m,int y, int d=1)
{
  int Y;
  (m<3)? Y=y-1:Y=y;
  y = Y%100;
  int c = Y/100;
  int shiftedMonth;
  switch(m)
  {
    case 1: shiftedMonth = 11; break;
    case 2: shiftedMonth = 12; break;
    case 3: shiftedMonth = 1; break;
    case 4: shiftedMonth = 2; break;
    case 5: shiftedMonth = 3; break;
    case 6: shiftedMonth = 4; break;
    case 7: shiftedMonth = 5; break;
    case 8: shiftedMonth = 6; break;
    case 9: shiftedMonth = 7; break;
    case 10: shiftedMonth = 8; break;
    case 11: shiftedMonth = 9; break;
    case 12: shiftedMonth = 10; break;
  }
  int weekDay = int((d+int(floor(2.6*shiftedMonth-.2))+y+y/4+c/4-2*c))%7;
  if(weekDay<0)
   weekDay += 7;
   return weekDay;
}

//function to check is the year given is a leap year
bool isLeapYear(int year)
{
  if(year % 400 == 0 || year % 4 == 0 && !(year % 100 == 0))
    return true;
  else
    return false;
}

//prints begining of the calendar
void printHeader(int month, int year)
{
  string monthTitle = "";
  switch(month)
  {
    case 1: monthTitle = "January"; numDays= 31; break;
    case 2: monthTitle = "February"; (isLeapYear(year))? numDays=29:numDays=28; break;
    case 3: monthTitle = "March"; numDays= 31; break;
    case 4: monthTitle = "April"; numDays= 30; break;
    case 5: monthTitle = "May"; numDays= 31;break;
    case 6: monthTitle = "June"; numDays= 30; break;
    case 7: monthTitle = "July"; numDays= 31; break;
    case 8: monthTitle = "August"; numDays= 31; break;
    case 9: monthTitle = "September"; numDays= 30; break;
    case 10: monthTitle = "October"; numDays= 31; break;
    case 11: monthTitle = "November"; numDays= 30; break;
    case 12: monthTitle = "December"; numDays= 31; break;
  }
  cout << "Calendar for " << monthTitle << " " << year << endl;
  cout << "|---------------------------|" << endl;
  cout << "|Sun|Mon|Tue|Wed|Thu|Fri|Sat|" << endl;
  cout << "|---------------------------|" << endl;
}

//prints end of the calendar
void printFoot()
{
  cout << "|---------------------------|" << endl;
}

//checks to see if given month and day is a holidays
bool isHoliday(int month, int day)
{
  if(month==7 && day ==4) //4th of July
    return true;
  else if(month==10 && day==31) //Halloween
    return true;
  else if(month==12 && day==25) //Christmas
    return true;
  else
    return false;
}

//fills in the calendar
void fillCalendar(int month, int year)
{
  int day = 1;
  int weeks = 5;
  int daysSkipped = 0;

  //adjusts the amount of weeks in a month
  if(startDayofMonth==5 && numDays==31 || startDayofMonth==6 && numDays>29)
    weeks = 6;
  else if(startDayofMonth==0 && !isLeapYear(year) && month==2)
    weeks = 4;

 //iterates over each week in a month
 for(int i = 0; i < weeks; i++)
 {
   //iterates over each day in a week
   for(int j = 0; j < 7; j++)
   {
     //creates "empty" boxes on calendar after printing all days in a month
     if(day > numDays)
     {
       cout << "|   ";
       continue;
     }

     cout << "| ";

     //prints "empty" boxes on calendar before it prints day 1
     if(i == 0 && j < startDayofMonth)
     {
       cout << "  ";
       continue;
     }

     //formats single digit
     if(day<10) cout << " ";
      cout << day++;

   }

   cout << "|" << endl;

   //iterates through each day and identifies holidays
   for(int j = 0; j < 7; j++)
   {
     //keeps track of what number day the loop is on
     int currentDay = (i)*7+(j+1)-daysSkipped;
     //skips over days before the first of the month
     if(i == 0 && j < startDayofMonth)
     {
       daysSkipped++;
       cout << "|   ";
       continue;
     }
     cout << "|";
     //checks to see if the current day is a holiday and marks it accordingly
     if(isHoliday(month, currentDay)) cout << " * ";
     else cout << "   ";
   }
   cout << "|" << endl;
   printFoot();
 }
}


int main(int argc, char ** argv)
{
  //create needed variables
  int month = atoi(argv[1]);
  int year = atoi(argv[2]);
  startDayofMonth = startDay(month,year);
  printHeader(month, year);
  fillCalendar(month, year);
}

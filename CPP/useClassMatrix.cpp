#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <stdexcept>
 
#include "class_matrix.h"
 
int main()
{ 
   using namespace MatrSpace;
   srand(static_cast<unsigned>(time(NULL)));
   ConsoleMatr<int> Ob1;
   size_t row, col;
   std::cout<<"Enter num of rows and cols for 1-st matrix: ";
   std::cin>>row>>col;
   Ob1.SetSize(row, col);
 
   int choise=0;
   std::cout<<"Enter 1 for fill matrix from keyboard\n"
      <<"Enter 2 for random fill matrix\n";
   std::cin>>choise;
   if(choise==1)
      std::cin>>Ob1;
   else if(choise==2)
      Ob1.random_fill();
   else
   {
      std::cerr<<"There is no such option\n";
      return 0;
   }
   std::cout<<std::endl;
   
   ConsoleMatr<int> Ob2;
   std::cout<<"Enter num of rows and cols for 2-nd matrix: ";
   std::cin>>row>>col;
   Ob2.SetSize(row, col);
 
   choise=0;
   std::cout<<"Enter 1 for fill matrix from keyboard\n"
      <<"Enter 2 for random fill matrix\n";
   std::cin>>choise;
   if(choise==1)
      std::cin>>Ob2;
   else if(choise==2)
      Ob2.random_fill();
   else
   {
      std::cerr<<"There is no such option\n";
      return 0;
   }
   std::cout<<std::endl;
 
   ConsoleMatr<int> Ob3;
   std::cout<<"First matrix\n\n"<< Ob1 <<'\n';
   std::cout<<"Second matrix\n\n"<< Ob2 <<'\n';
   try
   {
       Ob3=Ob1*Ob2;
   }
   catch(const std::invalid_argument&e) 
   {
      std::cout<<e.what()<<'\n';
      return 0;
   }
   std::cout<<"Multy of first matrix to second matrix\n\n";
   std::cout<<Ob3<<'\n';
   return 0;
}
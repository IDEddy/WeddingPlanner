#ifndef ICT_DATE_H__
#define ICT_DATE_H__
// header file includes
#include <iostream>
#include <cstring>
#include <string>



namespace ict {
   // Error code values go here

#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4


   class Date {
   private:
      // private member variables
	   int readErrorCode_;
	   int year_;
	   int mon_;
	   int day_;
      // private member functions and setters

      int value()const;
	  void errCode(int errorCode);

   public:
      // constructors
	   Date();
	   Date(int year_,int  mon_,int day_);
      // operator overloads
	   bool operator==(const Date& D)const;
	   bool operator!=(const Date& D)const;
	   bool operator<(const Date& D)const;
	   bool operator>(const Date& D)const;
	   bool operator<=(const Date& D)const;
	   bool operator>=(const Date& D)const;

      // IO member functions
	   std::istream& read(std::istream& istr);
	   std::ostream& write(std::ostream& ostr)const ;

      // public member functions and getters
      int mdays()const;
	  int errCode() const;
	  bool bad() const;


   };
   // operator << and >> overloads prototypes for ostream and istream go here
  
   std::ostream& operator<<(std::ostream& os, const Date& );
   std::istream& operator>>(std::istream& is, Date& );
 
}
#endif

// header files go here


#include "Date.h"
#include "wpgeneral.h"

using namespace std;

namespace ict {
	// returns a unique value representing the date
	// this value is used to compare two dates
	int Date::value()const {
		return year_ * 372 + mon_ * 31 + day_;
	}

	// bool validate(), this is an optional private function
	// for validation logic and setting the _readErrorCode.
	// see the read() function description for more details





	// mdays():
	// returns the day of the month.
	// _mon value must be set for this function to work
	// if _mon is invalid, this function returns -1
	// leap years are considered in this logic
	int Date::mdays()const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
		mon--;
		return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
	}

	// constructors
	Date::Date() {
		year_ = 0;
		mon_ = 0;
		day_ = 0;
		readErrorCode_ = NO_ERROR;

	}


	Date::Date(int year, int  mon, int day) {
		year_ = year;
		mon_ = mon;
		day_ = day;
		readErrorCode_ = NO_ERROR;
	}

	// member functions

	void Date::errCode(int errorCode) {

		readErrorCode_ = errorCode;
	}

	int Date::errCode() const {

		return readErrorCode_;
	}

	bool Date::bad()const {
		return readErrorCode_ != 0; 

	}


	// operators

	bool Date::operator==(const Date& D)const {
		return this->value() == D.value();
	}
	bool Date::operator!=(const Date& D)const {
		return this->value() != D.value();
	}
	bool Date::operator<(const Date& D)const {
		return this->value() < D.value();
	}
	bool Date:: operator>(const Date& D)const {
		return this->value() > D.value();
	}
	bool Date::operator<=(const Date& D)const {
		return this->value() <= D.value();

	}
	bool Date::operator>=(const Date& D)const {
		return this->value() >= D.value();


	}


	// IO functions
	istream& Date::read(std::istream& istr) {
	
		char junk1;
		char junk2;

	
		istr >> year_ >> junk1 >> mon_ >> junk2 >> day_;

		if (istr.fail() ) {
			readErrorCode_ = CIN_FAILED;
		
			
		}
		else
		{
			errCode(NO_ERROR);
			if (year_ > MAX_YEAR || year_ < MIN_YEAR) {
				errCode(YEAR_ERROR);
			}
			else if (mon_ > MAX_MONTH || mon_ < MIN_MONTH) {
				errCode(MON_ERROR);
			}
			else if ( day_ > mdays() || day_ <= 0 ) {
	
				errCode(DAY_ERROR);
			}
	
		}

		return istr;


	}
	ostream& Date::write(std::ostream& ostr) const {

		ostr << year_ << "/" ;
		if(mon_ < 10){
		ostr << "0" << mon_ << "/";
		}else{
		ostr << mon_ << "/";
		}

		if(day_ < 10){
		ostr << "0" << day_ ;
		}else{
		ostr << day_ ;
		}
		
		
		return ostr;
	}


	// non-memeber operator overloads

	std::ostream& operator<<(std::ostream& os, const  Date& input) {
		input.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is, Date& input) {
		input.read(is);
		return is;
	}

}

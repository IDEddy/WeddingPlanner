#define _CRT_SECURE_NO_WARNINGS
#include "Error.h"
#include <cstring>
using namespace std;

namespace ict{

	Error::Error() {
		message_ = nullptr;
	
	}

	Error::Error(const char* Error) {
		message_ = nullptr;
		message(Error);
	}
	Error::~Error() {
		delete[] message_;
	}
	Error& Error::operator=(const char* errorMessage) {
		
		
		clear();
		message(errorMessage);
		return *this;

	}


	void Error::message(const char* value) {
		int length = strlen(value);
		
		
		delete[] message_;
		
		message_ = new char[length + 1];
		strcpy(message_, value);
	}
	void Error::clear() {
		delete [] message_;
		message_ = nullptr;
	
	}

	bool Error::isClear()const  {
		return message_ == nullptr;
	}

	const char* Error::message()const {
		return message_;
	
	}

	std::ostream& operator<<(std::ostream& os,const Error& s) {
		
		if (!s.isClear()) {
			os << s.message();
		}
	
		return os;
	
	}




}

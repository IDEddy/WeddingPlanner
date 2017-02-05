#ifndef ICT_CUSTOMMADE_H__
#define ICT_CUSTOMMADE_H__
#include "OnShelf.h"
#include "Date.h"
#include "Error.h"
#include "Good.h"

namespace ict {
   class CustomMade : public OnShelf{
   private:
	   Date delivery_;
	  
   public:
	   CustomMade() :OnShelf('C') {}
	  
//	   using OnShelf::OnShelf;

      	
	  void delivery(const Date &value);

	  std::fstream& store(std::fstream& file, bool addNewLine = true) const;

	  std::fstream& load(std::fstream& file);
	  std::ostream& display(std::ostream& ostr, bool linear) const;
	  std::istream& conInput(std::istream& istr);
	  const Date& delivery()const;

	  
   };
}


#endif

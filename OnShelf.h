#ifndef ICT_ONSHELF_H__
#define ICT_ONSHELF_H__
#include "Good.h"
#include "Error.h"
#include <fstream>
#include <iomanip>
using namespace std;

namespace ict {
   class OnShelf : public Good{
   private:
	   char recTag_;

   protected:
	   Error err_;

   public:
	
	   OnShelf(const char charInput  = 'O');

	   std::fstream& store(std::fstream& file, bool addNewLine = true) const;
	   std::fstream& load(std::fstream& file);
	   ostream& display(ostream& os, bool linear) const;

	   istream& conInput(istream& istr);
   
   };
}
#endif
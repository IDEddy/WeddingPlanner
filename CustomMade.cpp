#include "CustomMade.h"

namespace ict {



	const Date& CustomMade::delivery()const {
		return delivery_;


	}

	void CustomMade::delivery(const Date &value) {

		delivery_ = value;
	}

	fstream& CustomMade::store(fstream& file, bool addNewLine)const {
		
		OnShelf::store(file,false);
		file << "," << delivery();		
		if (addNewLine) {
			file  << endl;

		}
		
		return file;
	}


	fstream& CustomMade::load(fstream& file) {

		
		OnShelf::load(file);
				
		delivery_.read(file);
		file.ignore(1);
		return file;
	}

	ostream& CustomMade::display(ostream& ostr, bool linear)const {

		OnShelf::display(ostr, linear);

		if (err_.isClear() == false) {
			return ostr;
		}
		else  if (err_.isClear() ) {

			if (linear) {
				/*left justified in MAX_SKU_LEN characters*/
			ostr << delivery();

			}
			else {

		ostr << endl <<"delivery date: " << delivery();


			}


		}

		return ostr;
	}

	istream& CustomMade::conInput(istream& istr) {

		OnShelf::conInput(istr);
		Date tempDate;

		if (err_.isClear()) {


			cout << "delivery date (YYYY/MM/DD) : ";

			istr >> tempDate;
				
				
				if (tempDate.errCode() == CIN_FAILED) {
					err_.message("Invalid Date Entry");
					istr.setstate(ios::failbit);
				
				}
				else if (tempDate.errCode() == YEAR_ERROR) {
					err_.message("Invalid Year in Date Entry");
					istr.setstate(ios::failbit);
			
				}
				else if (tempDate.errCode() == MON_ERROR) {
					err_.message("Invalid Month in Date Entry");
					istr.setstate(ios::failbit);
				
				}
				else if (tempDate.errCode() == DAY_ERROR) {
					err_.message("Invalid Day in Date ENtry");
					istr.setstate(ios::failbit);
		
				}
			
				else {
				
				err_.clear();	
			}


				if(istr.fail()){
				return istr;
				}else{
				delivery_ = tempDate;
				}
		

			

		}

				return istr;


	}

}

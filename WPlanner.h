#ifndef ICT_WPlanner_H__
#define ICT_WPlanner_H__
#include "Good.h"
#include <fstream>
#include <iostream>

namespace ict {
   class WPlanner{
      char filename_[256];
	  /*the good items*/
      Good* items_[MAX_NO_RECS];
      std::fstream datafile_;
      int noOfItems_;



      int menu();
	  void loadRecs();
      void saveRecs();
      void listItems()const;
      int SearchItems(const char* sku)const;
      void updateQty();
      void addItem(bool isCustomMade);
      void deleteItem();
      void getSku(char* sku);
   public:
      //Copy and assignment prevention goes here:


      WPlanner(const char* filename);
      int run();
   };
}
#endif

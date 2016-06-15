/* testing Modify
 * must have GraduationPlan.o Semester.o Course.o New.o ProjAux.o View.o Modify.o
 * must also have all *.h Files, and a GraduationPlan.txt file built
 * 
 * compile g++ -Wall -ansi -o testView testView.cpp GraduationPlan.o Semester.o Course.o New.o ProjAux.o View.o Modify.o
 * 
 * Use View functionality to confirm things from Modify
 */

#include "Course.h"
#include "Semester.h"
#include "GraduationPlan.h"

#include "Modify.h"
#include "View.h"
#include "New.h"
#include "Proj.h"

int main()
{

   cout << "\tTesting View Functionality." << endl << endl;
   cout << "You will need to have a GraduationPlan.txt built" << endl;

   vector<char> yesNo;
   yesNo.push_back('Y');
   yesNo.push_back('N');
   char yesnoChoice = GetMenuResponse( yesNo );

   if ( yesnoChoice == 'N' )
      exit(-1);

   vector<Course> courseList;
   courseList = buildCourseInfo();

   GraduationPlan gradplan;

   gradplan = buildPlan( courseList );

   char validResponse = ' ';

   do
   {
      validResponse = displayMainMenu( );

      switch( validResponse )
      {
         case 'N':
            break;
         case 'M':
	    modify( gradplan );
            break;
         case 'V':
            view( gradplan );
            break;
         case 'P':
            break;
         case 'S':
            break;
         case 'C':
            break;
         case 'Q':
            break;
         default:
            cerr << "Invalid menu selection, please try again!"
                 << endl;
            break;
      }
   } while ( validResponse != 'Q' );

   return 0;
}

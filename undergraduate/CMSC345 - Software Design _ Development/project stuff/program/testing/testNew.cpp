/* testing New() Module 
 * needs all input files
 * needs New.o GraduationPlan.o Semester.o Course.o ProjAux.o View.o
 *
 */

#include <iostream>
#include "New.h"
#include "View.h"
#include "Course.h"
#include "Semester.h"
#include "GraduationPlan.h"
#include "Proj.h"

int main()
{
   system("clear");

   vector<Course> courseList;
   courseList = buildCourseInfo();

   GraduationPlan gradplan;

   cout << "Welcome, would you like to test buildPlan? (Y/N)" << endl;

   vector<char> yesNoChoices;
   yesNoChoices.push_back('Y');
   yesNoChoices.push_back('N');
   char gradplanChoice = GetMenuResponse( yesNoChoices );

   switch ( gradplanChoice )
   {
      case 'Y':
         gradplan = buildPlan( courseList );
         break;
      default:
	 cerr << "Somehow invalid" << endl;
	 break;
   }

   char validResponse = ' ';

   do
   {
      validResponse = displayMainMenu( );

      switch( validResponse )
      {
         case 'N':
            gradplan = newPlan( courseList );
            break;
         case 'V':
            view( gradplan );
            break;
         case 'Q':
            break;
         default:
            cerr << "Invalid menu selection, please try again!"
                 << endl;
            break;
      } 
   }while ( validResponse != 'Q' );

   return 0;
}

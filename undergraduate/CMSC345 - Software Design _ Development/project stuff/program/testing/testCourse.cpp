/* testing the Course class
 * Course.o must exist
 * Course.h should also exist
 * compile: g++ -Wall -ansi -o testCourse testCourse.cpp Course.o
 *
 */



#include <iostream>

#include "Course.h"

using namespace std;

int main()
{
   system("clear");
   
   // Course without prereqs
   Course temp1;

   cout << "\tCourse made with default constructor,"
	<< "\t without prereqs." << endl;

   cout << "Title: " << temp1.getTitle() << endl
	<< "Designator: " << temp1.getDesg() << endl
	<< "Number: " << temp1.getNumber() << endl
	<< "Grade: " << temp1.getGrade() << endl
	<< "Comments: " << temp1.getComments() << endl
	<< endl;

   vector<Course> temp1pre = temp1.getPrereqs();
   
   for ( unsigned int i = 0; i < temp1pre.size(); ++i )
   {
      cout << "Prereq: " << i << endl
	   << "Title: " << temp1pre.at(i).getTitle() << endl
	   << "Designator: " << temp1pre.at(i).getDesg() << endl
	   << "Number: " << temp1pre.at(i).getNumber() << endl
	   << "Grade: " << temp1pre.at(i).getGrade() << endl
	   << "Comments: " << temp1pre.at(i).getComments() << endl
	   << endl;
   }

   if ( static_cast<int>(temp1pre.size()) == 0 )
   {
      cout << "\tNo Prereqs in Course Object" << endl
	   << "\tCourse::getPreReqs() did not fail though" << endl;
   }

   cout << endl << endl;

   Course temppre("Prereq Title", 152, "CMSC");
   vector<Course> fakepre;
   fakepre.push_back(temppre);
   Course temp2("Title", 666, "CMSC", fakepre);

   cout << "\tCourse made with constructor,"
        << "\t with prereqs." << endl;

   cout << "Title: " << temp2.getTitle() << endl
        << "Designator: " << temp2.getDesg() << endl
        << "Number: " << temp2.getNumber() << endl
        << "Grade: " << temp2.getGrade() << endl
        << "Comments: " << temp2.getComments() << endl
        << endl;

   vector<Course> temp2pre = temp2.getPrereqs();

   for ( unsigned int j = 0; j < temp2pre.size(); ++j )
   {
      cout << "Prereq: " << j << endl
           << "Title: " << temp2pre.at(j).getTitle() << endl
           << "Designator: " << temp2pre.at(j).getDesg() << endl
           << "Number: " << temp2pre.at(j).getNumber() << endl
           << "Grade: " << temp2pre.at(j).getGrade() << endl
           << "Comments: " << temp2pre.at(j).getComments() << endl
           << endl;
   }

   if ( static_cast<int>(temp2pre.size()) == 0 )
   {
      cout << "\tNo Prereqs in Course Object" << endl
           << "\tCourse::getPreReqs() did not fail though" << endl;
   }

   cout << endl << endl;

   cout << "\tTesting assignment operator:" << endl << endl;

   Course temp3 = temp2;

   cout << "Temp Course 3 Title: " << temp3.getTitle() << endl
	<< "Designator: " << temp3.getDesg() << endl
	<< "Number: " << temp3.getNumber() << endl
	<< "Grade: " << temp3.getGrade() << endl
	<< "Comments: " << temp3.getComments() << endl
	<< endl;

   cout << "\tTesting equality operator:" << endl << endl;

   if ( temp3 == temp2 )
      cout << "Temp Course 3 == Temp Course 2" << endl << endl;
  
   else
      cout << "Equality Operator failed." << endl << endl;


   cout << "\tTesting Course::inputNewGrade()" << endl << endl;
   
   temp3.inputNewGrade('A');
   cout << "Input: A, New Grade: " << temp3.getGrade() << endl;
   temp3.inputNewGrade('a');
   cout << "Input: a, New Grade: " << temp3.getGrade() << endl
	<< "Should consider making all input grades uppercase"
	<< " if not already" << endl << endl;

   cout << "\tTesting Course::inputComments()" << endl << endl;
   
   temp3.inputComments("New Damn Comments");
   cout << "Input: New Damn Comments, New Comments: " << endl
	<< temp3.getComments() << endl << endl;

   temp3.inputComments("");
   cout << "Input: , New Comments: " << endl
	<< temp3.getComments() << endl << endl;

   cout << "\tTesting Course::appendComments()" << endl << endl;
  
   temp3.appendComments("Appendage");
   cout << "Input: Appendage, New Comments: " << endl
	<< temp3.getComments() << endl << endl;

   cout << endl << endl;

   cout << "\tTesting Course::addNewPrereq()" << endl << endl;
   Course temppre2("Not Blank", 154, "IS");

   cout << "Temp Course 1, Number Prereqs: "
	<< temp1pre.size() << endl;
   
   temp1.addNewPrereq(temppre2);

   temp1pre = temp1.getPrereqs();

   cout << "Temp Course 1, Number Prereqs: "
	<< temp1pre.size() << endl;

   cout << endl << endl;

   cout << "\tTesting Course::loadPrereqs()" << endl << endl;

   vector<Course> anotherprereq;
   vector<Course> anothertemp;
   Course temporary;
   Course temporary2;
   anotherprereq.push_back(temporary);
   anotherprereq.push_back(temporary2);

   temp1.loadPrereqs(anotherprereq);
   cout << "Temp Course 1, Number Prereqs: ";
   anothertemp = temp1.getPrereqs();
   cout << anothertemp.size() << endl << endl;

   cout << endl << "All members functions of class Course"
	<< " have been tested by this driver." << endl << endl;

   return 0;
}

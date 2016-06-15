/* test Driver for GraduationPlan class
 * must have GraduationPlan.o Semester.o Course.o
 * must have GraduationPlan.h Semester.h Course.h
 *
 * to compile:
 * g++ -Wall -ansi -o testGradPlan testGradPlan.cpp GraduationPlan.o Semester.o Course.o
 */

#include <iostream>

#include "GraduationPlan.h"

int main()
{

   system("clear");

   cout << "\tTesting the GraduationPlan class" << endl;

   cout << "\tTesting Constructor" << endl;

   Semester tempSem("FL", 2005);

   GraduationPlan tempPlan("John Doe", tempSem, "CMSC", "None");

   cout << "\tTesting GraduationPlan::getName, getMajor, getMinor, numSemesters" << endl;
   cout << "Name: " << tempPlan.getName() << endl
	<< "Major: " << tempPlan.getMajor() << endl
	<< "Minor: " << tempPlan.getMinor() << endl
	<< "NumSemesters: " << tempPlan.numSemesters() << endl
	<< endl;

   cout << "\tTesting GraduationPlan::listSemesters()" << endl << endl;
   tempPlan.listSemesters();

   cout << endl;

   cout << "\tTesting GraduationPlan::getSemester()" << endl << endl;
  
   Semester tempSem2 = tempPlan.getSemester(0);
   
   cout << "Designator: " << tempSem2.getDesg() << endl
	<< "Year: " << tempSem2.getYear() << endl
	<< endl;

   cout << "\tTesting GraduationPlan::addSemester()" << endl;
   bool pass = tempPlan.addSemester("FL", 2005);

   if ( pass == true )
      cout << "Semester added, duplicated, fail" << endl;
   else
      cout << "Semester not added, duplicated, pass" << endl;

   pass = tempPlan.addSemester("SP",2006);

   if ( pass == true )
      cout << "Semester added, non-duplicate, pass" << endl;
   else
      cout << "Semester not added, non-duplicate, fail" << endl;

   cout << endl << endl;

   cout << "\tItems not yet tested: " << endl
	<< "GraduationPlan::getFromRemaining()" << endl
	<< "GraduationPlan::checkPrereqs()" << endl
	<< "GraduationPlan::removeFromRemaining()" << endl
	<< "GraduationPlan::addToRemaining()" << endl
	<< "GraduationPlan::viewRemain()" << endl << endl;

   return 0;
}

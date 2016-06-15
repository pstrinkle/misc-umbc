/* testing Driver for Semester class
 * must have: Semester.o Course.o
 * must have: Semester.h Course.h
 *
 *
 * compile: g++ -Wall -ansi -o testSemester testSemester.cpp Semester.o Course.o
 */

#include <iostream>

#include "Course.h"
#include "Semester.h"

int main()
{

   system("clear");

   cout << "\tThis will test all methods of the Semester class" 
	<< endl << endl;


   cout << "Construct Semester without courses premade" << endl;
   Semester temp1("FL", 2005);

   cout << "Designator: " << temp1.getDesg() << endl
	<< "Year: " << temp1.getYear() << endl 
	<< "Number of Courses: " << temp1.numCourses() << endl
	<< endl;

   cout << "\tTesting Semester::addCourse()" << endl << endl;

   Course tempCourse;

   temp1.addCourse(tempCourse);
   
   cout << "Number of Courses: " << temp1.numCourses() << endl
	<< endl;

   cout << endl;

   cout << "\tTesting Semester::viewList()" << endl << endl;
   
   temp1.viewList();

   cout << endl << endl;

   cout << "\tTesting Semester::viewCourse()" << endl << endl;
   
   Course tempCourse2 = temp1.viewCourse(0);

   cout << "Course Info:" << endl
	<< "Title: " << tempCourse2.getTitle() << endl
	<< "Designator Number: " << tempCourse2.getDesg()
	<< " " << tempCourse2.getNumber() << endl
	<< endl;
/*
   Course tempCourse666 = temp1.viewCourse(-1);
   
   cout << "Course Info:" << endl
        << "Title: " << tempCourse666.getTitle() << endl
        << "Designator Number: " << tempCourse666.getDesg()
        << " " << tempCourse666.getNumber() << endl
        << endl;
*/

   cout << "\tTesting Semester::deleteCourse()" << endl << endl;

   cout << "\tTesting also if not in Semester" 
	<< "Failed!"
	<< endl << endl;

   Course tempCourse10("No Fun", 123, "CMSC");
/*
   temp1.deleteCourse(tempCourse10);

   cout << "Number of Courses shouldnt' change: " << temp1.numCourses() << endl
	<< endl;
*/
   temp1.deleteCourse(tempCourse);
   
   cout << "Number of Courses: " << temp1.numCourses() << endl
	<< endl;




   cout << "\tTesting Semester::operator<()" << endl 
	<< "\tTesting other constructor with premade Courses"
	<< endl << endl;
   cout << "Semester A, FL 2005" << endl
	<< "Semester B, SP 2006" << endl;

   vector<Course> preCourses;
   preCourses.push_back(tempCourse);
   preCourses.push_back(tempCourse2);

   Semester temp2("SP", 2006, preCourses);

   if ( temp1 < temp2 )
      cout << "Semester A comes first, pass" << endl;
   else
      cout << "Fail" << endl;

   cout << endl;

   cout << "\tTesting Semester::operator==()" << endl << endl;
   
   if ( temp1 == temp2 )
      cout << "Semester A == Semester B, fail" << endl;
   else
      cout << "Pass" << endl;

   cout << "\tThis Driver has tested every member function of the Semester class."
	<< endl << endl;

   return 0;
}

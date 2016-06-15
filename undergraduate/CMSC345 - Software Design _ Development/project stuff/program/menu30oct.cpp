
#include <vector>
#include <iostream>
#include <ctype.h>
using namespace std;

#define MENU_MIN 1
#define MENU_MAX 3

/********************************************************************
 ** PrintGreeting -
 **   This is a function that prints out the company greeting/ logo
 ** INPUT: there is not input
 ** OUTPUT: the company greeting is printed out
 *******************************************************************/
void PrintGreeting ( );

/********************************************************************
 ** DisplayMenu -
 **   This funcion prints out the menu, which includes the
 **  different options a user has, in this case: 1, 2, or 3
 ** INPUT: there is no input
 ** OUTPUT: the Main Menu, the with choices: 1, 2, 3
 ******************************************************************/
void DisplayMenu ( void );

/********************************************************************
 ** GetMenuResponse -
 **   This function gets the input that the user selects after
 **  reading the menu that is between min and max
 ** INPUT: 1. for donuts, 2. for muffins, 3. to quit
 ** OUTPUT: this function only sends out an output when the
 **      user inputs values that are greater then the max
 **      amount allowed or less then the max amount allowed.
 **      The function also returns the orderchoice to main.
 *******************************************************************/
char GetMenuResponse ( const vector<char> & theChoices );
bool validateSelection ( const char choice, const vector<char> & theChoices );
void newStudent ( void );
void modify ( void );
void addSemester ( void );
void modifySemester ( void );
void addCourse ( void );
void deleteCourse ( void );
void modifyCourse ( void );
void view ( void );
void print ( void );
void modifyGrade( void );
void modifyComments( void );
void viewRemainingGrad( void );
void viewCourseInfoMenu( void );
void viewCourseInfo( void );
void viewSemesterSelectionMenu ( void );
void viewSemester ( void );
void sentToPrinter ( void );
void getRange( void );

int main( )
{
   DisplayMenu( );
   return ( 0 );

}

/*******************************************************************
 ** PrintGreeting -
 **    This is a function that prints out the company greeting/ logo
 ** INPUT: there is not input
 ** OUTPUT: the company greeting is printed out
 *******************************************************************/
void PrintGreeting ( string title )
{
   cout << "*************************************************"
        << endl
        << "\t\t"
	<< title
	<< "\t\t"
        << endl
        << "*************************************************"
        << endl;
}

/********************************************************************
 ** DisplayMenu -
 **    This funcion prints out the menu, which includes the
 **    different options a user has, in this case: 1, 2, or 3
 ** INPUT: there is no input
 ** OUTPUT: the Main Menu, the function choices: 1, 2, 3
 *******************************************************************/
void DisplayMenu( void ) 
{
   
   system( "clear" );

   char menuChoice;
   vector<char> mainChoices;

   mainChoices.push_back( 'N' );
   mainChoices.push_back( 'M' );
   mainChoices.push_back( 'V' );
   mainChoices.push_back( 'P' );
   mainChoices.push_back( 'Q' );

   string screenTitle = "Quick Grad Planner";

   PrintGreeting( screenTitle );

   cout << "N - New"
	<< endl
        << "M - Modify"
	<< endl
        << "V - View"
	<< endl
        << "P - Print"
	<< endl
        << "Q - Quit"
	<< endl << endl;

   menuChoice = GetMenuResponse( mainChoices );

   system("clear");

   switch( menuChoice ) 
   {
      case 'N':
         newStudent( );
         break;
      case 'M':
         modify( );
         break;
      case 'V':
         view( );
         break;
      case 'P':
         print( );
         break;
      case 'Q':
         return;
         break;
      default:
         cout << "Invalid menu selection, please try again!"
              << endl;
         break;
   }

}

/********************************************************************
 ** GetMenuResponse -
 **    This function gets the input that the user selects after
 **    reading the menu that is between min and max
 ** INPUT: User can select 1. for donuts, 2. for muffins, or
 **     3. to quit
 ** OUTPUT: this function only sends out an output when the user
 **      inputs values that are greater then the max amount allowed
 **      or less then the max amount allowed. returns the value of
 **      orderchoice to main.
 *******************************************************************/
char GetMenuResponse ( const vector<char> & theChoices ) 
{
   char menuChoice;
   bool valid = false;

   do
   {
      cout << "Please enter your selection: ";
      cin >> menuChoice;

      menuChoice = toupper( menuChoice );

      if( validateSelection( menuChoice, theChoices ) )
      {
	 valid = true;
      }
      else
      {
	 cout << "Invalid Selection, please select again."
	      << endl;
      }
   } while( ! valid );
   
   return menuChoice;
}

/********************************************************************
 ** validateSelection -
 **    This function validates the users input from the choices given
 ** INPUT: User can select 1. for donuts, 2. for muffins, or
 **     3. to quit
 ** OUTPUT: this function only sends out an output when the user
 **      inputs values that are greater then the max amount allowed
 **      or less then the max amount allowed. returns the value of
 **      orderchoice to main.
 *******************************************************************/

bool validateSelection ( const char choice, const vector<char> & theChoices )
{

   bool exists = false;

   for( unsigned int i = 0; i < theChoices.size( ); i++ )
   {

      if ( theChoices.at( i ) == choice )
      {
         exists = true;
      }

   }

   return ( exists );
}


void newStudent(void) 
{

   string screenTitle = "New Student Information";
   PrintGreeting( screenTitle );

   string fname, lname, semester;
   int major, year;
   char correct;
   string Mjor;
   string minor = "N/A";

   cout << "Enter First Name : ";
   cin >> fname;
   cout << endl
	<< "Enter Last Name : ";
   cin >> lname;
   cout << endl
	<< "Enter beginning semester (FL/SP/SU/WI): ";
   cin >> semester;
   cout << endl
	<< "Enter beginning year (yyyy format): ";
   cin >> year;

   cout << endl
	<< "Pick a major from the following :"
	<< endl;

   cout << "  1. Computer Science"
	<< endl
        << "  2. Computer Science/Information Systems Double Major"
	<< endl
        << "  3. Information Systems"
	<< endl
        << "  4. Information Systems Major/ Computer Science Minor"
	<< endl;

   vector<char> mainChoices;
   mainChoices.push_back( '1' );
   mainChoices.push_back( '2' );
   mainChoices.push_back( '3' );
   mainChoices.push_back( '4' );

   major = GetMenuResponse( mainChoices );

   switch( major ) 
   {
      case '1':
         Mjor = "Computer Science";
         break;
      case '2':
         Mjor = "Computer Science/Information Systems Double Major";
         break;
      case '3':
         Mjor = "Information Systems";
         break;
      case '4':
         Mjor = "Information Systems";
         minor = "Computer Science";
         break;
      default:
	 cout << "incorrect?" << endl;
         break;
   }

   system( "clear" );

   cout << "********************"
	<< endl
	<< "Information Entered"
	<< endl
        << "********************"
	<< endl;

   cout << "Name : " << fname + " " + lname 
	<< endl
        << "Beginning semester : " 
	<< semester << " " << year
	<< endl
        << "Major : " << Mjor 
	<< endl
        << "Minor : " << minor 
	<< endl;

   cout << endl
	<< "Is the above information correct (Y/N)?"
	<< endl;
   
   vector<char> confirmChoices;
   confirmChoices.push_back( 'Y' );
   confirmChoices.push_back( 'N' );

   correct = GetMenuResponse( confirmChoices );

   system( "clear" );

   switch(correct)
   {
      case 'Y':
         DisplayMenu( );
         break;
      case 'N':
         newStudent( );
         break;
      default:
         break;
   }

   return;

}

void modify( void ) 
{

   system( "clear" );

   string screenTitle = "Modify Graduation Plan";
   PrintGreeting( screenTitle );

   char modifyChoice;
   cout << "A - Add Semester"
	<< endl
        << "M - Modify Semester"
	<< endl
        << "B - Back"
	<< endl;
   
   vector<char> mainChoices;
   mainChoices.push_back( 'A' );
   mainChoices.push_back( 'M' );
   mainChoices.push_back( 'B' );

   modifyChoice = GetMenuResponse( mainChoices );

   system( "clear" );

   switch( modifyChoice ) 
   {
      case 'A':
         addSemester( );
         break;
      case 'M':
         modifySemester( );
         break;
      case 'B':
         DisplayMenu( );
         break;
      default:
         break;
   }

}

void addSemester( void )
{

   string screenTitle = "Add New Semester";
   PrintGreeting( screenTitle );

   string designator;
   string year;

   cout << "Enter Semester Designator (FL/SP/SU/WI): ";
   cin >> designator;

   cout << "Enter year (yyyy format): ";
   cin >> year;

   system( "clear" );

   cout << "********************"
	<< endl
	<< "Information Entered"
	<< endl
        << "********************"
	<< endl;

   cout << "Semester Entered: " 
	<< designator + " " + year
	<< endl;

   cout << endl
	<< "Is the above information correct (Y/N)?"
	<< endl;
   
   vector<char> confirmChoices;
   confirmChoices.push_back( 'Y' );
   confirmChoices.push_back( 'N' );

   char correct = GetMenuResponse( confirmChoices );

   switch( correct )
   {
      case 'Y':
         modify( );
         break;
      case 'N':
         addSemester( );
         break;
      default:
         break;
   }

   return;
}

void modifySemester( void )
{
   system( "clear" );

   string screenTitle = "Modify Existing Semester";
   PrintGreeting( screenTitle );

   char choice;

   cout << "A - Add Course"
	<< endl
        << "D - Delete Course"
	<< endl
        << "M - Modify Course"
	<< endl
        << "B - Back"
	<< endl;

   vector<char> mainChoices;
   mainChoices.push_back( 'A' );
   mainChoices.push_back( 'D' );
   mainChoices.push_back( 'M' );
   mainChoices.push_back( 'B' );

   choice = GetMenuResponse( mainChoices );

   switch( choice ) 
   {
      case 'A':
         addCourse( );
         break;
      case 'D':
         deleteCourse( );
         break;
      case 'M':
	 modifyCourse( );
         break;
      case 'B':
         modify( );
         break;
      default:
         break;
   }

}

void addCourse( void )
{

   system( "clear" );

   string screenTitle = "Add New Course";
   PrintGreeting( screenTitle );

   cout << "Select a couse to add: "
	<< endl 
	<< "  1. Course a"
	<< endl
	<< "  2. Course b"
	<< endl
	<< "  3. Course c"
	<< endl
	<< "  ..."
	<< endl
	<< "  xx. Course xx"
	<< endl;

   vector<char> confirmChoices;
   confirmChoices.push_back( '1' );
   confirmChoices.push_back( '2' );
   confirmChoices.push_back( '3' );

   char menuResponse = GetMenuResponse( confirmChoices );

   cout << endl
	<< "Add Course "
	<< menuResponse
	<< " (Y/N) ? "
	<< endl;

   confirmChoices.clear( );
   confirmChoices.push_back( 'Y' );
   confirmChoices.push_back( 'N' );

   menuResponse = GetMenuResponse ( confirmChoices );
   
   switch( menuResponse )
   {
      case 'Y':
         modifySemester( );
         break;
      case 'N':
         addCourse( );
         break;
      default:
         break;
   }


}

void deleteCourse( void ) 
{

   system( "clear" );

   string screenTitle = "Delete Course";
   PrintGreeting( screenTitle );

   cout << "Select a course to delete: "
	<< endl
	<< "  1. Course a"
	<< endl
	<< "  2. Course b"
	<< endl
	<< "  3. Course c"
	<< endl
	<< "  ..."
	<< endl
	<< "  xx. Course xx"
	<< endl;

   vector<char> confirmChoices;
   confirmChoices.push_back( '1' );
   confirmChoices.push_back( '2' );
   confirmChoices.push_back( '3' );

   char menuResponse = GetMenuResponse( confirmChoices );

   cout << endl
	<< "Remove Course "
	<< menuResponse
	<< " (Y/N) ? "
	<< endl;

   confirmChoices.clear( );
   confirmChoices.push_back( 'Y' );
   confirmChoices.push_back( 'N' );

   menuResponse = GetMenuResponse ( confirmChoices );
   
   switch( menuResponse )
   {
      case 'Y':
         modifySemester( );
         break;
      case 'N':
         deleteCourse( );
         break;
      default:
         break;
   }

   return;
}

void modifyCourse( void )
{

   system( "clear" );

   string screenTitle = "Modify a Course";
   PrintGreeting( screenTitle );

   cout << "Select a course to modify: "
	<< endl 
	<< "  1. Course a"
	<< endl
	<< "  2. Course b"
	<< endl
	<< "  3. Course c"
	<< endl
	<< "  ..."
	<< endl
	<< "  xx. Course xx"
	<< endl;

   vector<char> menuChoices;
   menuChoices.push_back( '1' );
   menuChoices.push_back( '2' );
   menuChoices.push_back( '3' );

   char menuResponse = GetMenuResponse( menuChoices );

   cout << "Select the aspect of your course to modify: "
	<< endl;

   cout << "  1. Grade"
	<< endl
	<< "  2. Comments"
	<< endl;

   menuChoices.clear( );
   menuChoices.push_back( '1' );
   menuChoices.push_back( '2' );

   menuResponse = GetMenuResponse ( menuChoices );

   switch( menuResponse )
   {
      case '1':
         modifyGrade( );
         break;
      case '2':
         modifyComments( );
         break;
      default:
         break;
   }   

   return;
}

void modifyGrade( void )
{
   system( "clear" );

   string screenTitle = "Modify Course Grade";
   PrintGreeting( screenTitle );
   
   bool validGrade = false;
   char newGrade;

   do
   {

      cout << "Enter new grade (A-E): ";
      
      cin >> newGrade;
      
      newGrade = toupper( newGrade );
      
      if(  newGrade == 'A' || newGrade == 'B' ||  newGrade == 'C' || newGrade == 'D' ||  newGrade == 'E' )
      {
      
	 validGrade = true;
      }

   } while ( !validGrade );


   cout << endl
	<< "Change grade to "
	<< newGrade
	<< " (Y/N)?"
	<< endl;

   vector<char> confirmChoices;
   confirmChoices.clear( );
   confirmChoices.push_back( 'Y' );
   confirmChoices.push_back( 'N' );

   char menuResponse = GetMenuResponse ( confirmChoices );

   switch( menuResponse )
   {
      case 'Y':
         modifySemester( );
         break;
      case 'N':
         deleteCourse( );
         break;
      default:
         break;
   }
}


void modifyComments( void )
{
   system( "clear" );

   string screenTitle = "Modify Course Comments";
   PrintGreeting( screenTitle );
   
   string newComment;

   cout << "Enter new comment: "
	<< endl;

   cin.ignore( 100, '\n' );
   getline( cin, newComment);

   system( "clear" );

   cout << newComment
	<< endl
	<< "Add this comment (Y/N)?"
	<< endl;

   vector<char> confirmChoices;
   confirmChoices.clear( );
   confirmChoices.push_back( 'Y' );
   confirmChoices.push_back( 'N' );

   char menuResponse = GetMenuResponse ( confirmChoices );

   switch( menuResponse )
   {
      case 'Y':
         modifySemester( );
         break;
      case 'N':
         deleteCourse( );
         break;
      default:
         break;
   }

}


void view( void )
{

   system( "clear" );

   string screenTitle = "View Graduation Plan";
   PrintGreeting( screenTitle );

   char choice;

   cout << "R - View Remaining Graduation Requirements"
	<< endl
        << "S - View Selected Semester"
	<< endl
	<< "C - View Selected Course Information"
	<< endl
        << "B - Back"
	<< endl;

   vector<char> mainChoices;
   mainChoices.push_back( 'R' );
   mainChoices.push_back( 'S' );
   mainChoices.push_back( 'B' );
   mainChoices.push_back( 'C' );

   choice = GetMenuResponse( mainChoices );

   switch( choice ) 
   {
      case 'R':
         viewRemainingGrad( );
      case 'S':
         viewSemesterSelectionMenu( );
         break;
      case 'B':
         DisplayMenu( );
         break;
      case 'C':
	 viewCourseInfoMenu( );
      default:
	 break;
   }

   return;
}

void viewRemainingGrad ( void )
{

   system("clear");

   string screenTitle = "Remaining Graduation Requirements";
   PrintGreeting( screenTitle );

   cout << "1. CMSC345"
	<< endl
	<< "2. CMSC411"
	<< endl
	<< "3. CMSC421"
	<< endl;

   cout << "Return, type B" << endl;

   char choice;

   vector<char> mainChoices;
   mainChoices.push_back( 'B' );

   // does no checking
   choice = GetMenuResponse( mainChoices );

   // this is horrible!
   view();

   return;
}

void viewCourseInfoMenu( void )
{
   system("clear");

   // that's awful, i just made it up, don't kill me!
   string screenTitle = "Courses Available for Viewing";
   PrintGreeting( screenTitle );

   cout << "1. CMSC345"
	<< endl
	<< "2. CMSC411"
	<< endl
	<< "3. CMSC481"
	<< endl
	<< "4. CMSC421"
	<< endl
	<< endl;


   cout << "Choose a course to view information (i.e. 1)" << endl;

   int choice;
   // maybe should be an int, will fix before func proto

   cin >> choice;

   // should error check but it wasn't working right, just used for screenshot

   viewCourseInfo();


   // bad
   view();

   return;

}

void viewCourseInfo ( void )
{
   system("clear");

   string screenTitle = "Course X";
   PrintGreeting( screenTitle );

   cout << "Course: CMSC345"
	<< endl
	<< "Credits: 3"
	<< endl
	<< "Grade: A"
	<< endl
	<< "Comments: Generic"
	<< endl
	<< endl;

   cout << "Enter B to return" << endl;

   char choice;

   vector<char> mainChoices;
   mainChoices.push_back( 'B' );

   choice = GetMenuResponse( mainChoices );
   
   return;
}

void viewSemesterSelectionMenu ( void ) 
{
   system("clear");

   // that's awful, i just made it up, don't kill me!
   string screenTitle = "Semesters Available for Viewing";
   PrintGreeting( screenTitle );

   cout << "1. FL 2003"
        << endl
        << "2. SP 2004"
        << endl
        << "3. FL 2004"
        << endl
        << "4. SP 2005"
	<< endl
        << endl;

   cout << "Choose a semester to view courses (i.e. 1)" << endl;

   int choice;
   // maybe should be an int, will fix before func proto

   cin >> choice;

   // should error check
   // just using for screenshot


   viewSemester( );


   // bad
   view( );

   return;


}

void viewSemester ( void )
{
   system("clear");

   string screenTitle = "Semester X";
   PrintGreeting( screenTitle );

   cout << "CMSC345"
        << endl
        << "CMSC313"
        << endl
        << "CMSC481"
        << endl
        << "CMSC421"
	<< endl
        << endl;

   cout << "Enter B to return" << endl;

   char choice;

   vector<char> mainChoices;
   mainChoices.push_back( 'B' );

   choice = GetMenuResponse( mainChoices );

   return;

}

void print( void )
{

   system("clear");

   string screenTitle = "Print Graduation Plan";
   PrintGreeting( screenTitle );

   char choice;
   string sdrange, edrange;
   string syear, eyear;

   cout << "E - Print Entire Plan"
	<< endl
        << "R - Print Range of Semester"
	<< endl
        << "B - Back"
	<< endl;

   vector<char> mainChoices;
   mainChoices.push_back( 'E' );
   mainChoices.push_back( 'R' );
   mainChoices.push_back( 'B' );
   char subchoice;
   vector<char> subchoices;
   subchoices.push_back( 'B' );



   choice = GetMenuResponse( mainChoices );

   switch( choice )
   {
      case 'E':
         cout << "...printing entire plan..."
	      << endl;
	 // really bad idea

	 cout << "To return press B" << endl;
	 subchoice = GetMenuResponse( subchoices );
	 print();
         break;
      case 'R':
         cout << "Enter start range designator (FL/SP/SU/WI): ";
         cin >> sdrange;
         cout << "Enter start range year (yyyy format): ";
         cin >> syear;

         cout << "Enter end range designator (FL/SP/SU/WI): ";
         cin >> edrange;
         cout << "Enter end range yea (yyyy format): ";
         cin >> eyear;

	 system("clear");
	 cout << "Printing range: " 
	      << edrange << eyear 
	      << " -- " 
	      << sdrange << syear << endl;

	 cout << "To return press B" << endl;
         subchoice = GetMenuResponse( subchoices );
         print();
         break;
      case 'B':
         DisplayMenu( );
         break;
      default:
         break;
   }

   return;
}

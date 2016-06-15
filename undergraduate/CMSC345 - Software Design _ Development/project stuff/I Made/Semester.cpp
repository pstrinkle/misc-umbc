Semester.h/Semester.cpp

class Semester
{
   public:
      Course viewCourse(int id);
      string deleteCourse(int id);
      string addCourse(Course new);
      int getYear();
   private:
      vector<Course> courses;
      string designator;
      int year;
}

Course Semester::viewCourse(int id)
{
   return courses.at(id);
}
string Semester::deleteCourse(int id)
{
   // I think it's just .erase or something?
   
   Course oldCourse = courses.at(id);

   // delete it

   return oldCourse.getTitle();
}
string Semester::addCourse(Course new)
{
   courses.push_back(new);

   return new.getTitle();
}
int Semester::getYear()
{
   return year;
}
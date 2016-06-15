#include "Project2.h"
#include "Process.h"

using namespace std;

void Process::run()
{
   int trash, mem1, mem2, mem3;
   string cmd;
   mem1 = 0;
   mem2 = 0;
   mem3 = 0;

   ifstream in;
   in.open(m_filename.c_str());

   if ( !in )
   {
      cerr << "Could not open file - " << m_filename << endl;
   }
   else
   {
      in >> trash;

      while ( in >> cmd )
      {
	 if ( cmd == "print" )
	 {
	    in >> mem1;

	    int pageNum = getPage(mem1);
	    
	    if ( isValidPg(pageNum) )
	    {
	       int frame_id = getFrame(pageNum);
	       int offset = calcOffset(mem1);
	       int value = m_mem->getValue(frame_id, offset);
	       
	       cout << "Command: print " << mem1 << "; Result: Value in addr " 
		    << mem1 << " = " << value << endl;
	    }
	    else
	    {
	       cerr << "Invalid Memory Address " << mem1 << " specified for process id " << getPid() << endl;
	    }
	 }
	 else if ( cmd == "load" )
	 {
	    int input;
	    string comma;
	    in >> input >> comma >> mem1;

	    int pageNum = getPage(mem1);

	    if ( isValidPg(pageNum) )
	    {
	       int frame_id = getFrame(pageNum);
	       int offset = calcOffset(mem1);
	       m_mem->setValue(frame_id, offset, input);

	       cout << "Command: load " << input << ", " << mem1
		    << "; Result: Value of " << input << " is now stored in addr "
		    << mem1 << endl;
	    }
	    else
	    {
	       cerr << "Invalid Memory Address " << mem1 << " specified for process id " << getPid() << endl;
	    }
	 }
	 else if ( cmd == "add" )
	 {
	    string comma, comma2;
	    bool calculate = true;
	    in >> mem1 >> comma >> mem2 >> comma2 >> mem3;

	    int pageNum1 = getPage(mem1);
	    int pageNum2 = getPage(mem2);
	    int pageNum3 = getPage(mem3);

	    if ( !isValidPg(pageNum1) )
	    {
	       cerr << "Invalid Memory Address " << mem1 << " specified for process id " << getPid() << endl;
	       calculate = false;
	    }
	    else if ( !isValidPg(pageNum2) )
	    {
	       cerr << "Invalid Memory Address " << mem2 << " specified for process id " << getPid() << endl;
	       calculate = false;
	    }
	    else if ( !isValidPg(pageNum3) )
	    {
	       cerr << "Invalid Memory Address " << mem3 << " specified for process id " << getPid() << endl;
	       calculate = false;
	    }

	    if ( calculate )
	    {
	       int frame_id1 = getFrame(pageNum1);
	       int offset1 = calcOffset(mem1);
	       int x = m_mem->getValue(frame_id1, offset1);

	       int frame_id2 = getFrame(pageNum2);
               int offset2 = calcOffset(mem2);
               int y = m_mem->getValue(frame_id2, offset2);

	       int frame_id3 = getFrame(pageNum3);
               int offset3 = calcOffset(mem3);

	       int z = x + y;
	       m_mem->setValue(frame_id3, offset3, z);

	       cout << "Command: add " << mem1 << ", "
		    << mem2 << ", " << mem3 << "; Result: Value in addr x = "
		    << x << ", addr y = " << y << ", addr z = " << z << endl;
	    }
	 }
	 else if ( cmd == "sub" )
	 {
	    string comma, comma2;
            bool calculate = true;
            in >> mem1 >> comma >> mem2 >> comma2 >> mem3;

            int pageNum1 = getPage(mem1);
            int pageNum2 = getPage(mem2);
            int pageNum3 = getPage(mem3);

            if ( !isValidPg(pageNum1) )
            {
               cerr << "Invalid Memory Address " << mem1 << " specified for process id " << getPid() << endl;
               calculate = false;
            }
            else if ( !isValidPg(pageNum2) )
            {
               cerr << "Invalid Memory Address " << mem2 << " specified for process id " << getPid() << endl;
               calculate = false;
            }
            else if ( !isValidPg(pageNum3) )
            {
               cerr << "Invalid Memory Address " << mem3 << " specified for process id " << getPid() << endl;
               calculate = false;
            }

            if ( calculate )
            {
               // add mem1 & mem2, store in mem3
               int frame_id1 = getFrame(pageNum1);
               int offset1 = calcOffset(mem1);
               int x = m_mem->getValue(frame_id1, offset1);

               int frame_id2 = getFrame(pageNum2);
               int offset2 = calcOffset(mem2);
               int y = m_mem->getValue(frame_id2, offset2);

               int frame_id3 = getFrame(pageNum3);
               int offset3 = calcOffset(mem3);

               int z = x - y;
               m_mem->setValue(frame_id3, offset3, z);

               cout << "Command: sub " << mem1 << ", "
                    << mem2 << ", " << mem3 << "; Result: Value in addr x = "
                    << x << ", addr y = " << y << ", addr z = " << z << endl;
            }
	 }
	 else
	 {
	    cerr << "Invalid command - " << cmd << " - Process " << getPid() << endl;
	 }
      }
   }
}

#include "Project2.h"

#include "PidQueue.h"
#include "Process.h"
#include "Memory.h"

using namespace std;

int getIndex(vector<Process> them, int pid);
void removeProcess(vector<Process> & them, int pid);
void swapout(Process & process, Memory & memory);
void swapin(Process & process, Memory & memory);
void sortbyPid(PidQueue & unsorted);

int main(int argc, char * argv[])
{
   // M is in KB
   // V is in KB
   // P is in bytes
   int M = 0;
   int V = 0;
   int P = 0;

   if (argc != 7)
   {
      fprintf(stderr, "No enough cmds.\n");
      fprintf(stderr, "usage: proj2 -m <size in KB> -v <size in KB> -p <page size in bytes>\n");
      exit(-1);
   }

   int arg = 0;
   /* arg = 0 is the program file */
   for (arg = 1; arg < argc; ++arg)
   {
      if (strcasecmp(argv[arg], "-m") == 0)
      {
         M = atoi(argv[arg+1]);
         arg++;
      }
      else if (strcasecmp(argv[arg], "-v") == 0)
      {
         V = atoi(argv[arg+1]);
         arg++;
      }
      else if (strcasecmp(argv[arg], "-p") == 0)
      {
	 P = atoi(argv[arg+1]);
	 arg++;
      }
      else
      {
         exit(-2);
      }
   }

   int mainPages = (M * 1024) / P;
   int virtPages = (V * 1024) / P;

   PidQueue pids;
   int pidCtr = 0;
   vector<Process> processes;
   Memory mmu(P, mainPages, virtPages);

   string cmd;
   int pid;

   do
   {
      cout << "<Command Prompt>";
      
      cin >> cmd;

      if (cmd == "load")
      {
	 string inputs = " ";
	 char delims[] = " ";
	 vector<string> filelist;
	 char * file = NULL;
	 ifstream inputStream;

	 getline(cin, inputs);
	 
	 char * longstring = (char *)malloc(sizeof(char) * inputs.size() + 1);
	 memset(longstring, '\0', inputs.size() + 1);

	 for (unsigned int i = 0; i < inputs.size(); ++i)
	    longstring[i] = inputs[i];
	 
	 file = strtok(longstring, delims);

	 while( file != NULL )
	 {
	    filelist.push_back(string(file));
	    file = strtok( NULL, delims);
	 }
	 
	 for (unsigned int i = 0; i < filelist.size(); ++i)
	 {
	    inputStream.open(filelist[i].c_str());
	    int value;
	    int numPages;
	    int newPid;

	    if ( !inputStream )
	       cerr << filelist.at(i) << " could not be loaded - file does not exist" << endl;
	    else
	    {
	       inputStream >> value;
	       inputStream.close();

	       numPages = (value * 1024) / P;
	       
	       if ( mmu.isFreeMain() < numPages && mmu.isFreeVirtual() < numPages )
		  cerr << filelist.at(i) << " could not be loaded - not enough memory" << endl;
	       else
	       {
		  newPid = ++pidCtr;
		  vector<int> newtable;

		  if ( mmu.isFreeMain() >= numPages )
		  {
		     cout << filelist.at(i) << " is loaded in main memory and is" 
			  << " assigned process id " << newPid << endl;

		     for (int j = 0; j < numPages; ++j)
			newtable.push_back(mmu.allocateMFrame());

		     Process newprocess(numPages, pidCtr, mmu.getpgSize(), &mmu, filelist.at(i));
		     newprocess.nowInmain();
		     newprocess.importPgtbl(newtable);
		     processes.push_back(newprocess);
		  }
		  else if ( mmu.numPgsMain() < numPages )
		  {
		     cout << "file : " << filelist.at(i) << " can never fit into main memory." << endl;
		  }
		  else
		  {
		     cout << filelist.at(i) << " is loaded in virtual memory and is"
			  << " assigned process id " << newPid << endl;

		     for (int j = 0; j < numPages; ++j)
			newtable.push_back(mmu.allocateVFrame());

		     Process newprocess(numPages, pidCtr, mmu.getpgSize(), &mmu, filelist.at(i));
		     newprocess.nowInvirtual();
		     newprocess.importPgtbl(newtable);
		     processes.push_back(newprocess);
		  }

		  pids.push_back(pidCtr);
		  pids.move_to_front(pidCtr);
	       }
	    }
	 }
	 filelist.clear();
      }

      else if (cmd == "kill")
      {
	 cin >> pid;

	 vector<int> table;
	 int index = getIndex(processes, pid);

	 if ( index > -1)
	 {
	    table = processes.at(index).exportPgtbl();
	    
	    if (processes.at(index).inMain())
	    {
	       for (unsigned int i = 0; i < table.size(); ++i)
		  mmu.deallocateM(table.at(i));
	    }
	    else
	    {
	       for (unsigned int i = 0; i < table.size(); ++i)
		  mmu.deallocateV(table.at(i));
	    }

	    removeProcess(processes, pid);
	    pids.remove(pid);
	 }
	 else
	 {
	    cerr << "Invalid process id " << pid << endl;
	 }
      }

      else if (cmd == "run")
      {
	 cin >> pid;
	 
	 int index = getIndex(processes, pid);
	 
	 if ( index >= 0 )
	 {
	    if ( processes.at(index).inMain() )
	       processes.at(index).run();
	    else
	    {
	       cout << "Process id " << pid << " is in Virtual Memory" << endl;

	       // while it can't fit, swapout processes
	       while ( processes.at(index).getSize() > mmu.isFreeMain() )
               {
                  int backPid = pids.get_last();
                  int backIndex = getIndex(processes, backPid);

                  if ( processes.at(backIndex).inMain() )
                  {
		     if ( processes.at(backIndex).getSize() > mmu.isFreeVirtual() )
		     {
			cout << "Process id " << backPid << " cannot fit into virtual memory" << endl;
		     }
		     else
		     {
			swapout(processes.at(backIndex), mmu);
			cout << "Process id " << backPid << " has been moved into virtual memory" << endl;
		     }
                  }

                  // push pid to the front of the queue
                  pids.move_to_front(backPid);
               }
	       
	       // if the process can now fit, swap in
	       if ( processes.at(index).getSize() <= mmu.isFreeMain() )
               {
                  swapin(processes.at(index), mmu);
                  pids.move_to_front(pid);

                  cout << "Process id " << pid << " has been moved into main memory" << endl;
               }
	       
	       // process can never fit
               else
               {
                  cerr << "Process id " << pid << " cannot fit into main memory" << endl;
               }

	       processes.at(index).run();
	    }
	    
	    pids.move_to_front(pid);

	 }
	 else
	 {
	    cout << "Process id " << pid << " is invalid" << endl;
	 }
      }
      
      else if (cmd == "print")
      {
	 int beginaddress = 0;
	 int length = 0;
	 cin >> beginaddress >> length;

	 for (int i = beginaddress; i < beginaddress + length; ++i)
	 {
	    if ( i > M * 1024 )
	    {
	       cout << "Invalid Memory address " << i << endl;
	    }
	    else
	    {
	       int frame_id = i / mmu.getpgSize();
	       int offset = i % mmu.getpgSize();
	       int value = mmu.getValue(frame_id, offset);
	       cout << "Value of " << i << ": " << value << endl;
	    }
	 }
      }

      else if (cmd == "pteall")
      {
	 string filename;
	 cin >> filename;

	 ofstream outputStream;
	 outputStream.open(filename.c_str());

	 if ( !outputStream )
	 {
	    cerr << "Could not open " << filename << endl;
	 }
	 else
	 {
	    for (unsigned int i = 0; i < processes.size(); ++i)
	    {
	       outputStream << "Process id " << processes.at(i).getPid();

	       if (processes.at(i).inMain())
		  outputStream << " in Main Memory";
	       else
		  outputStream << " in Virtual Memory";

	       outputStream << endl;

	       vector<int> table = processes.at(i).exportPgtbl();

	       for (unsigned int i = 0; i < table.size(); ++i)
		  outputStream << "Page: " << i << " Frame: " << table.at(i) << endl;
	    }

	    outputStream.close();
	 }
      }

      else if (cmd == "pte")
      {
	 string filename;
	 int pid;
	 cin >> pid >> filename;

	 int index = getIndex(processes, pid);
	 
	 if ( index > -1 )
	 {
	    ofstream outputStream;
	    outputStream.open(filename.c_str(), ios::app);
	    
	    if ( !outputStream )
	    {
	       cerr << "Could not open " << filename << endl;
	    }
	    else
	    {
	       vector<int> table = processes.at(index).exportPgtbl();

	       if ( processes.at(index).inMain() )
	       {
		  outputStream << "Process id " << pid << " is in main memory" << endl;
	       }
	       else
	       {
		  outputStream << "Process id " << pid << " is in virtual memory" << endl;
	       }

	       for (unsigned int i = 0; i < table.size(); ++i)
	       {
		  outputStream << "Page: " << i << " Frame: " << table.at(i) << endl;
	       }

	       outputStream.close();
	    }
	 }
	 else
	 {
	    cerr << "Process id " << pid << " is invalid" << endl;
	 }
      }

      else if (cmd == "listpr")
      {
	 PidQueue mainpids;
	 PidQueue virtpids;
	 
	 for (int i = 0; i < pids.getSize(); ++i)
	 {
	    int pid = pids.getPid(i);
	    int index = getIndex(processes, pid);
	    
	    if ( processes.at(index).inMain() )
	    {
	       mainpids.push_back(pid);
	    }
	    else
	    {
	       virtpids.push_back(pid);
	    }
	 }

	 sortbyPid(mainpids);
	 sortbyPid(virtpids);

	 cout << "Processes in Main Memory" << endl;

	 for (int i = 0; i < mainpids.getSize(); ++i)
	    cout << "Process id " << mainpids.getPid(i) << endl;

	 cout << "Processes in Virtual Memory" << endl;

	 for (int i = 0; i < virtpids.getSize(); ++i)
	    cout << "Process id " << virtpids.getPid(i) << endl;
      }

      else if (cmd == "swapout")
      {
	 int pid;
	 cin >> pid;

	 int index = getIndex(processes, pid);
	 if ( index > -1 )
	 {
	    if (processes.at(index).inMain())
	    {
	       if ( processes.at(index).getSize() <= mmu.isFreeVirtual() )
	       {
		  swapout(processes.at(index), mmu);
	       }
	       else
	       {
		  cerr << "Not enough room in virtual memory" << endl;
	       }
	    }
	    else
	    {
	       cerr << "Process id " << pid << " is already in virtual memory" << endl;
	    }
	 }
	 else
	 {
	    cerr << "Invalid process id " << pid << endl;
	 }
      }

      else if (cmd == "swapin")
      {
	 int pid;
	 cin >> pid;

	 int index = getIndex(processes, pid);

	 if ( index > -1 )
	 {
	    if ( !processes.at(index).inMain() )
	    {
	       while ( processes.at(index).getSize() > mmu.isFreeMain() )
	       {
		  int backPid = pids.get_last();
		  int backIndex = getIndex(processes, backPid);
		  
		  if ( processes.at(backIndex).inMain() )
		  {
		     if ( processes.at(backIndex).getSize() > mmu.isFreeVirtual() )
		     {
			cout << "Process id " << backPid << " cannot fit into virtual memory" << endl;
		     }
		     else
		     {
			swapout(processes.at(backIndex), mmu);
			cout << "Process id " << backPid << " has been moved into virtual memory" << endl;
		     }
		  }
		  
		  // push pid to the front of the queue
		  pids.move_to_front(backPid);
	       }
	       
	       if ( processes.at(index).getSize() <= mmu.isFreeMain() )
	       {
		  swapin(processes.at(index), mmu);
		  pids.move_to_front(pid);
	       
		  cout << "Process id " << pid << " has been moved into main memory" << endl;
	       }
	       else
	       {
		  cerr << "Process id " << pid << " cannot fit into main memory" << endl;
	       }
	    }
	    else
	    {
	       cerr << "Process id " << pid << " is already in main memory" << endl;
	    }
	 }
	 else
	 {
	    cerr << "Invalid process id " << pid << endl;
	 }
      }
      else if ( cmd == "exit" )
      {
	 // do nothing
      }
      else
      {
	 cout << "Invalid command: " << cmd << endl;
      }
   }
   while( cmd != "exit" );

   mmu.purge();

   return 0;
}

int getIndex(vector<Process> them, int pid)
{
   for (unsigned int i = 0; i < them.size(); ++i)
      if (them.at(i).getPid() == pid)
	 return i;

   return -1;
}

void removeProcess(vector<Process> & them, int pid)
{
   vector<Process>::iterator iterator;

   for (iterator = them.begin(); iterator != them.end(); iterator++)
   {
      if ((*iterator).getPid() == pid)
      {
	 them.erase(iterator);
	 return;
      }
   }
}

void swapout(Process & process, Memory & memory)
{
   // check for space is already done
   cout << "Swapping out Process id " << process.getPid() << endl;

   vector<int> table = process.exportPgtbl();
   int newFrame = 0;
   bool swapped = true;
   vector<int> newtable;

   for (unsigned int i = 0; i < table.size(); ++i)
   {
      newFrame = memory.allocateVFrame();

      if ( newFrame != -1 )
      {
	 newtable.push_back(newFrame);
	 memory.cpMaintoVirt(table.at(i), newFrame);
	 memory.deallocateM(table.at(i));
      }
      else
      {
	 swapped = false;
      }
   }
   
   if ( swapped == true )
   {
      process.importPgtbl(newtable);
      process.nowInvirtual();
   }
}

void swapin(Process & process, Memory & memory)
{
   cout << "Swapping in process id " << process.getPid() << endl;
   // check for space is already done

   vector<int> table = process.exportPgtbl();
   int newFrame = 0;
   vector<int> newtable;
   bool swapped = true;

   for (unsigned int i = 0; i < table.size(); ++i)
   {
      newFrame = memory.allocateMFrame();

      if ( newFrame != -1 )
      {
	 newtable.push_back(newFrame);

	 memory.cpVirttoMain(newFrame, table.at(i));
	 memory.deallocateV(table.at(i));
      }
      else
      {
	 swapped = false;
      }
   }

   if ( swapped == true )
   {
      process.importPgtbl(newtable);
      process.nowInmain();
   }
}

void sortbyPid(PidQueue & unsorted)
{
   for (int j = 0; j < unsorted.getSize(); ++j)
   {
      for (int i = 0; i <= unsorted.getSize(); ++i)
      {
	 if ( i + 1 < unsorted.getSize() )
	 {
	    if ( unsorted.getPid(i) > unsorted.getPid(i + 1) )
	    {
	       unsorted.move_to_front(i + 1);
	    }
	 }
      }
   }
}

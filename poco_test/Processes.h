#include "Poco/Process.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"
#include <fstream>
using Poco::Process;
using Poco::ProcessHandle;

void testProcess()
{
	std::string cmd("c:\\Windows\\System32\\find.exe");
	std::vector<std::string> args;
	args.push_back("/?");

	Poco::Pipe outPipe;
	ProcessHandle ph = Process::launch(cmd, args, 0, &outPipe, 0);
	Poco::PipeInputStream istr(outPipe);

	std::ofstream ostr("processes.txt");
	Poco::StreamCopier::copyStream(istr, ostr);
}

#include "Poco/SharedMemory.h"
#include "Poco/File.h"
using Poco::SharedMemory;
using Poco::File;

void testFileSharedMemory()
{
	File f("MapIntoMemory.dat");
	SharedMemory mem(f, SharedMemory::AM_READ); // read-only access
	for (char* ptr = mem.begin(); ptr != mem.end(); ++ptr)
	{
		printf("%c ", *ptr);
	}
}

void testMemoryRegionSharedMemory()
{
	// Share a memory region of 1024 bytes
	SharedMemory mem("MySharedMemory", 1024, SharedMemory::AM_WRITE);
	for (char* ptr = mem.begin(); ptr != mem.end(); ++ptr)
	{
		*ptr = 0;
	}
}
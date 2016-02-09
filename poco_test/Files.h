#include "Poco/Path.h"

void testPath()
{
	Poco::Path p(true); // path will be absolute
	p.setNode("VMS001");
	p.setDevice("DSK001");
	p.pushDirectory("POCO");
	p.pushDirectory("INCLUDE");
	p.pushDirectory("POCO");
	p.setFileName("POCO.H");
	std::string s(p.toString(Poco::Path::PATH_VMS));
	// "VMS001::DSK001:[POCO.INCLUDE.POCO]POCO.H"
	p.clear(); // start over with a clean state
	p.pushDirectory("projects");
	p.pushDirectory("poco");
	s = p.toString(Poco::Path::PATH_WINDOWS); // "projects\poco\"
	s = p.toString(Poco::Path::PATH_UNIX); // "projects/poco/"
	s = p.toString(); // depends on your platform
}

using Poco::Path;

void testParsingPath()
{
	//creating a path will work independent of the OS
	Path p("C:\\Windows\\system32\\cmd.exe");
	Path p2("/bin/sh");
	p = "projects\\poco";
	p = "projects/poco";
	p = "c:\\여긴가\\거긴가\\어디.txt";
	p.parse("/usr/include/stdio.h", Path::PATH_UNIX);
	bool ok = p.tryParse("/usr/*/stdio.h");
	ok = p.tryParse("/usr/include/stdio.h", Path::PATH_UNIX);
	ok = p.tryParse("/usr/include/stdio.h", Path::PATH_WINDOWS);
	ok = p.tryParse("DSK$PROJ:[POCO]BUILD.COM", Path::PATH_GUESS);
}

void workingWithPath()
{
	Path p("c:\\projects\\poco\\build_vs80.cmd", Path::PATH_WINDOWS);

	std::string device(p.getDevice()); // "c"
	int n = p.depth(); // 2
	std::string dir1(p.directory(0)); // "projects"
	std::string dir2(p[1]); // "poco"
	std::string fileName(p[2]); // "build_vs80.cmd"

	fileName = p.getFileName();
	std::string baseName(p.getBaseName()); // "build_vs80"
	std::string extension(p.getExtension()); // "cmd"
	p.setBaseName("build_vs71");
	fileName = p.getFileName(); // "build_vs71.cmd"
}

void testPathOperation()
{
	Path p("/usr/include/stdio.h", Path::PATH_UNIX);
	Path parent(p.parent());

	std::string s(parent.toString(Path::PATH_UNIX)); // "/usr/include/"
	Path p1("stdlib.h");

	Path p2("/opt/Poco/include/Poco.h", Path::PATH_UNIX);
	p.resolve(p1);
	s = p.toString(Path::PATH_UNIX); // "/usr/include/stdlib.h"
	p.resolve(p2);
	s = p.toString(Path::PATH_UNIX); // "/opt/Poco/include/Poco.h"
}

void systemSpecificDir()
{
	std::cout
		<< "cwd: " << Path::current() << std::endl
		<< "home: " << Path::home() << std::endl
		<< "temp: " << Path::temp() << std::endl
		<< "null: " << Path::null() << std::endl;
}

void pathAndEnvironmentVar()
{
	std::string config("%HOMEDRIVE%%HOMEPATH%\\config.ini");
	// std::string config("$HOME/config.ini");
	std::string expConfig(Path::expand(config));
}

#include "Poco/Path.h"
#include "Poco/Environment.h"
using Poco::Path;
using Poco::Environment;

void findFile()
{
	std::string shellName("cmd.exe"); // Windows
	// std::string shellName("sh"); // Unix

	std::string path(Environment::get("PATH"));
	Path shellPath;
	bool found = Path::find(path, shellName, shellPath);
	std::string s(shellPath.toString());
}

#include "Poco/File.h"
#include "Poco/Path.h"
#include <iostream>
using Poco::File;
using Poco::Path;

void testFileOperation()
{
	Path tmpPath(Path::temp());
	tmpPath.pushDirectory("PocoFileSample");
	File tmpDir(tmpPath);
	tmpDir.createDirectories();
	bool exists = tmpDir.exists();
	bool isFile = tmpDir.isFile();
	bool isDir = tmpDir.isDirectory();
	bool canRead = tmpDir.canRead();
	bool canWrite = tmpDir.canWrite();

	File tmpFile(Path(tmpPath, std::string("PocoFileSample.dat")));
	if (tmpFile.createFile())
	{
		tmpFile.setSize(10000);
		File tmpFile2(Path(tmpPath, std::string("PocoFileSample2.dat")));
		tmpFile.copyTo(tmpFile2.path());
		Poco::Timestamp now;
		tmpFile.setLastModified(now);
		tmpFile.setReadOnly();
		canWrite = tmpFile.canWrite();
		tmpFile.setWriteable();
		canWrite = tmpFile.canWrite();
	}

	std::vector<std::string> files;
	tmpDir.list(files);
	std::vector<std::string>::iterator it = files.begin();
	for (; it != files.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	tmpDir.remove(true);
}

#include "Poco/DirectoryIterator.h"
#include <iostream>
using Poco::DirectoryIterator;
using Poco::Path;

void testDirectoryIterator()
{
	std::string cwd(Path::current());
	DirectoryIterator it(cwd);
	DirectoryIterator end;
	while (it != end)
	{
		std::cout << it.name() << " ";
		if (it->isFile())
			std::cout << it->getSize();
		std::cout << std::endl;
		Path p(it.path());
		++it;
	}
}

#include "Poco/Glob.h"
#include <iostream>
using Poco::Glob;

void testGlob()
{
	std::set<std::string> files;
	
	Glob::glob("%WINDIR%\\System32\\*.exe", files);
	// Glob::glob("/usr/include/*/*.h", files);
	std::set<std::string>::iterator it = files.begin();
	for (; it != files.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}

#include "Poco/TemporaryFile.h"
#include <fstream>
using Poco::TemporaryFile;

void testTemporaryFile()
{
	TemporaryFile tmp;
	std::ofstream ostr(tmp.path().c_str());
	ostr << "Hello, world!" << std::endl;
	ostr.close();
}
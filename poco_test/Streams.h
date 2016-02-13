#include "Poco/Base64Encoder.h"
#include <iostream>
using Poco::Base64Encoder;

void testBase64Encoder()
{
	Base64Encoder encoder(std::cout);
	encoder << "Hello, world!";
}

#include "Poco/DeflatingStream.h"
#include <fstream>
using Poco::DeflatingOutputStream;
using Poco::DeflatingStreamBuf;

void testDeflatingStream()
{
	std::ofstream ostr("test.gz", std::ios::binary);
	DeflatingOutputStream deflater(ostr, DeflatingStreamBuf::STREAM_GZIP);
	deflater << "¾È³çÇÏ¼¼¿ä?";

	// ensure buffers get flushed before connected stream is closed
	deflater.close();
	ostr.close();
}

#include "Poco/TeeStream.h"
#include <iostream>
#include <fstream>
using Poco::TeeOutputStream;

void testTeeStream()
{
	TeeOutputStream tee(std::cout);
	std::ofstream fstr("output.txt");
	std::ofstream fstr2("output-2.txt");

	tee.addStream(fstr);
	tee.addStream(fstr2);
	tee << "Hello, world!" << std::endl;
}

void testOfstream()
{
	std::ofstream fo("testOfstream.txt");
	fo << "¾È³çÇÏ¼¼¿ä???" << std::endl;
}


#include "Poco/BinaryWriter.h"
#include <fstream>
using Poco::BinaryWriter;

void testBinaryWriter()
{
	std::ofstream ostr("binary.dat", std::ios::binary);
	BinaryWriter writer(ostr);

	writer.writeBOM();
	writer << "Hello, world!" << 42;
	writer.write7BitEncoded((Poco::UInt64)123);
	writer << true;
}

#include "Poco/BinaryReader.h"
#include <fstream>
using Poco::BinaryReader;

void testBinaryReader()
{
	std::ifstream istr("binary.dat", std::ios::binary);
	BinaryReader reader(istr);

	reader.readBOM();

	std::string hello;
	Poco::UInt64 i;
	bool b;

	reader >> hello >> i;
	reader.read7BitEncoded(i);
	reader >> b;
}

#include "Poco/UnbufferedStreamBuf.h"
#include <ostream>
#include <cctype>
using Poco::UnbufferedStreamBuf;

class UpperStreamBuf : public UnbufferedStreamBuf
{
public:
	UpperStreamBuf(std::ostream& ostr): _ostr(ostr)
	{}
protected:
	int writeToDevice(char c)
	{
		_ostr.put(toupper(c));
		return charToInt(c);
	}
private:
	std::ostream& _ostr;
};

class UpperIOS: public virtual std::ios
{
public:
	UpperIOS(std::ostream& ostr): _buf(ostr)
	{
		poco_ios_init(&_buf);
	}
protected:
	UpperStreamBuf _buf;
};

class UpperOutputStream: public UpperIOS, public std::ostream
{
public:
	UpperOutputStream(std::ostream& ostr): UpperIOS(ostr), std::ostream(&_buf)
	  {}
};

void testUnbufferedStreamBuf()
{
	UpperOutputStream upper(std::cout);
	upper << std::endl << "Hello, world!" << std::endl;
}

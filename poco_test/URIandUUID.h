#include "Poco/URI.h"
#include <iostream>

void testURI()
{
	Poco::URI uri1("http://www.appinf.com:88/sample?example-query#frag");
	std::string scheme(uri1.getScheme()); // "http"
	std::string auth(uri1.getAuthority()); // "www.appinf.com:88"
	std::string host(uri1.getHost()); // "www.appinf.com"
	unsigned short port = uri1.getPort(); // 88
	std::string path(uri1.getPath()); // "/sample"
	std::string query(uri1.getQuery()); // "example-query"
	std::string frag(uri1.getFragment()); // "frag"
	std::string pathEtc(uri1.getPathEtc()); // "/sample?examplequery#frag"
	
	Poco::URI uri2;
	uri2.setScheme("https");
	uri2.setAuthority("www.appinf.com");
	uri2.setPath("/another sample");
	std::string s(uri2.toString());	// "https://www.appinf.com/another%20sample"
	
	//std::string uri3("http://www.appinf.com");
	Poco::URI uri3("http://www.appinf.com");
	uri3.resolve("/poco/info/index.html");
	s = uri3.toString(); // "http://www.appinf.com/poco/info/index.html"
	uri3.resolve("support.html");
	s = uri3.toString(); // "http://www.appinf.com/poco/info/support.html"
	uri3.resolve("http://sourceforge.net/projects/poco");
	s = uri3.toString(); // "http://sourceforge.net/projects/poco"
}

#include "Poco/URIStreamOpener.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/FTPStreamFactory.h"
#include <memory>

void testURIStreamOpener()
{
	Poco::Net::HTTPStreamFactory::registerFactory();
	Poco::Net::FTPStreamFactory::registerFactory();

	Poco::URIStreamOpener& opener =	Poco::URIStreamOpener::defaultOpener();
	std::auto_ptr<std::istream> istr1(opener.open("http://www.appinf.com/index.html"));
	//std::auto_ptr<std::istream> istr2(opener.open("ftp://ftp.appinf.com/pub/poco/poco-1.2.5.tar.gz"));
	std::auto_ptr<std::istream> istr3(opener.open("file://c:/dev/c/play/poco-logger.txt"));
}

#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include <iostream>
using Poco::UUID;
using Poco::UUIDGenerator;

void testUUID()
{
	UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
	UUID uuid1(generator.create()); // time based
	UUID uuid2(generator.createRandom());
	UUID uuid3(generator.createFromName(UUID::uri(), "http://appinf.com"));

	std::cout << uuid1.toString() << std::endl;
	std::cout << uuid2.toString() << std::endl;
	std::cout << uuid3.toString() << std::endl;
}
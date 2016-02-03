#include "Poco/Random.h"
#include "Poco/RandomStream.h"
#include <iostream>
using Poco::Random;
using Poco::RandomInputStream;

void testRandom()
{
	Random rnd;
	rnd.seed();

	std::cout << "Random integer: " << rnd.next() << std::endl;
	std::cout << "Random digit: " << rnd.next(10) << std::endl;
	std::cout << "Random char: " << rnd.nextChar() << std::endl;
	std::cout << "Random bool: " << rnd.nextBool() << std::endl;
	std::cout << "Random double: " << rnd.nextDouble() << std::endl;

	RandomInputStream ri;
	std::string rs;
	ri >> rs;
}

#include "Poco/HMACEngine.h"
#include "Poco/SHA1Engine.h"
using Poco::DigestEngine;
using Poco::HMACEngine;
using Poco::SHA1Engine;

void testDigestEngine()
{
	std::string message1("This is a top-secret message.");
	std::string message2("Don't tell anyone!");
	std::string passphrase("s3cr3t"); // HMAC needs a passphrase

	HMACEngine<SHA1Engine> hmac(passphrase); // we'll compute a HMAC-SHA1
	hmac.update(message1);
	hmac.update(message2);

	const DigestEngine::Digest& digest = hmac.digest();	// finish HMAC computation and obtain digest

	std::string digestString(DigestEngine::digestToHex(digest)); // convert to a string of hexadecimal numbers
}

#include "Poco/DigestStream.h"
#include "Poco/MD5Engine.h"
using Poco::DigestOutputStream;
using Poco::DigestEngine;
using Poco::MD5Engine;

void testDigestStream()
{
	MD5Engine md5;
	DigestOutputStream ostr(md5);

	ostr << "This is some text";
	ostr.flush(); // Ensure everything gets passed to the digest engine
	
	const DigestEngine::Digest& digest = md5.digest(); // obtain result
	std::string result = DigestEngine::digestToHex(digest);
}
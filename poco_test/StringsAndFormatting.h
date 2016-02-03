
#include <Poco/String.h>
using Poco::trim;
using Poco::trimLeft;
using Poco::trimRight;
using Poco::trimRightInPlace;

void testString()
{
	std::string hello(" Hello, world! ");
	std::string s1(trimLeft(hello)); // "Hello, world! "
	trimRightInPlace(s1); // "Hello, world!"
	std::string s2(trim(hello)); // "Hello, world!"
}

using Poco::toUpper;
using Poco::toLower;
using Poco::toLowerInPlace;
using Poco::icompare;

void testCaseInsensitiveComparison()
{
	std::string hello("Hello, world!");
	std::string s1(toUpper(hello)); // "HELLO, WORLD!"
	toLowerInPlace(s1); // "hello, world!"
	int rc = icompare(hello, s1); // 0
	rc = icompare(hello, "Hello, Universe!"); // 1
}

using Poco::translateInPlace;

void testTranslate()
{
	std::string s("Eiffel Tower");
	translateInPlace(s, "Eelo", "3310"); // "3iff31 T0w3r"
}

using Poco::replace;

void testReplace()
{
	std::string s("aabbcc");

	std::string r(replace(s, "aa", "AA")); // "AAbbcc"
	r = replace(s, "bb", "xxx"); // "aaxxxcc"
	r = replace(s, "bbcc", ""); // "aa"
}

#include <vector>
using Poco::cat;

void testConcatenate()
{
	std::vector<std::string> colors;
	colors.push_back("red");
	colors.push_back("green");
	colors.push_back("blue");
	std::string s;
	s = cat(std::string(", "), colors.begin(), colors.end());
	// "red, green, blue"
}

#include "Poco/NumberFormatter.h"
using Poco::NumberFormatter;

void testNumberFormatter()
{
	std::string s;
	s = NumberFormatter::format(123); // "123"
	s = NumberFormatter::format(123, 5); // " 123"
	s = NumberFormatter::format(-123, 5); // " -123"
	s = NumberFormatter::format(12345, 3); // "12345"

	s = NumberFormatter::format0(123, 5); // "00123"

	s = NumberFormatter::formatHex(123); // "7B"
	s = NumberFormatter::formatHex(123, 4); // "007B"

	s = NumberFormatter::format(1.5); // "1.5"
	s = NumberFormatter::format(1.5, 2); // "1.50"
	s = NumberFormatter::format(1.5, 5, 2); // " 1.50"

	s = NumberFormatter::format(&s); // "00235F7D"
}

#include "Poco/Format.h"
using Poco::format;

void testFormat()
{
	int n = 42;
	std::string s;
	format(s, "The answer to life, the universe and everything is %d", n);

	s = format("%d + %d = %d", 2, 2, 4); // "2 + 2 = 4"
	s = format("%4d", 42); // " 42"
	s = format("%-4d", 42); // "42 "
	
	format(s, "%d", std::string("foo")); // "[ERRFMT]"
}

#include "Poco/StringTokenizer.h"
using Poco::StringTokenizer;
using Poco::cat;

void testStringTokenizer()
{
	StringTokenizer t1("red, green, blue", ",");
	// "red", " green", " blue" (note the whitespace)
	StringTokenizer t2("red,green,,blue", ",");
	// "red", "green", "", "blue"
	StringTokenizer t3("red; green, blue", ",;", StringTokenizer::TOK_TRIM);
	// "red", "green", "blue"
	StringTokenizer t4("red; green,, blue", ",;", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
	// "red", "green", "blue"
	std::string s(cat(std::string("; "), t4.begin(), t4.end()));
	// "red; green; blue"
}

#include "Poco/RegularExpression.h"
#include <vector>
using Poco::RegularExpression;

void testRegularExpression()
{
	RegularExpression re1("[0-9]+");
	bool match = re1.match("123"); // true
	match = re1.match("abc"); // false
	match = re1.match("abc123", 3); // true

	RegularExpression::Match pos;
	re1.match("123", 0, pos); // pos.offset == 0, pos.length == 3
	re1.match("ab12de", 0, pos); // pos.offset == 2, pos.length == 2
	re1.match("abcd", 0, pos); // pos.offset == std::string::npos

	RegularExpression re2("([0-9]+) ([0-9]+)");
	RegularExpression::MatchVec posVec;
	re2.match("123 456", 0, posVec);
	// posVec[0].offset == 0, posVec[0].length == 7
	// posVec[1].offset == 0, posVec[1].length == 3
	// posVec[2].offset == 4, posVec[2].length == 3

	std::string s;
	int n = re1.extract("123", s); // n == 1, s == "123"
	n = re1.extract("ab12de", 0, s); // n == 1, s == "12"
	n = re1.extract("abcd", 0, s); // n == 0, s == ""

	std::vector<std::string> vec;
	re2.split("123 456", 0, vec);
	// vec[0] == "123"
	// vec[1] == "456"
	s = "123";
	re1.subst(s, "ABC"); // s == "ABC"
	s = "123 456";
	re2.subst(s, "$2 $1"); // s == "456 123"
	RegularExpression re3("ABC");
	RegularExpression re4("ABC", RegularExpression::RE_CASELESS);
	match = re3.match("abc", 0); // false
	match = re4.match("abc", 0); // true
}

#include "Poco/TextConverter.h"
#include "Poco/Latin1Encoding.h"
#include "Poco/UTF8Encoding.h"
#include <iostream>
using Poco::TextConverter;
using Poco::Latin1Encoding;
using Poco::UTF8Encoding;

void testTextConverterOfEncodings()
{
	std::string latin1String("This is Latin-1 encoded text.");
	std::string utf8String;

	Latin1Encoding latin1;
	UTF8Encoding utf8;

	TextConverter converter(latin1, utf8);
	converter.convert(latin1String, utf8String);

	std::cout << utf8String << std::endl;
}

#include "Poco/StreamConverter.h"
#include "Poco/Latin1Encoding.h"
#include "Poco/UTF8Encoding.h"
#include <iostream>
using Poco::OutputStreamConverter;
using Poco::Latin1Encoding;
using Poco::UTF8Encoding;

void testStreamConverter()
{
	std::string latin1String("This is Latin-1 encoded text.");

	Latin1Encoding latin1;
	UTF8Encoding utf8;
	OutputStreamConverter converter(std::cout, latin1, utf8);

	converter << latin1String << std::endl; // console output will be UTF-8
}

#include "Poco/TextIterator.h"
#include "Poco/UTF8Encoding.h"
using Poco::TextIterator;
using Poco::UTF8Encoding;

void testTextIterator_UnicodeChar()
{
	std::string utf8String("This is UTF-8 encoded text.");

	UTF8Encoding utf8;
	TextIterator it(utf8String, utf8);
	TextIterator end(utf8String);
	
	for (; it != end; ++it)
	{
		int unicode = *it;
	}
}
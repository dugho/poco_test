#include "Poco/Timestamp.h"
#include <ctime>
using Poco::Timestamp;

void testTimeStamp()
{
	Timestamp now; // the current date and time
	std::time_t t1 = now.epochTime(); // convert to time_t ...
	Timestamp ts1(Timestamp::fromEpochTime(t1)); // ... and back again

	for (int i = 0; i < 10000000; ++i) ; // wait a bit
	Timestamp::TimeDiff diff = now.elapsed(); // how long did it take?
	Timestamp start(now); // save start time
	now.update(); // update with current time
	diff = now - start; // again, how long?
}


#include "Poco/DateTime.h"
using Poco::DateTime;

void testDateTime()
{
	DateTime now; // the current date and time in UTC
	int year = now.year();
	int month = now.month();
	int day = now.day();
	int dow = now.dayOfWeek();
	int doy = now.dayOfYear();
	int hour = now.hour();
	int hour12 = now.hourAMPM();
	int min = now.minute();
	int sec = now.second();
	int ms = now.millisecond();
	int us = now.microsecond();

	double jd = now.julianDay();
	Poco::Timestamp ts = now.timestamp();
	DateTime xmas(2016, 12, 25); // 2006-12-25 00:00:00
	Poco::Timespan timeToXmas = xmas - now;
	DateTime dt(1973, 9, 12, 2, 30, 45); // 1973-09-12 02:30:45
	dt.assign(2006, 10, 13, 13, 45, 12, 345); // 2006-10-13 12:45:12.345
	bool isAM = dt.isAM(); // false
	bool isPM = dt.isPM(); // true
	bool isLeap = DateTime::isLeapYear(2006); // false
	int days = DateTime::daysOfMonth(2006, 2); // 28
	bool isValid = DateTime::isValid(2006, 02, 29); // false
	dt.assign(2006, DateTime::OCTOBER, 22); // 2006-10-22 00:00:00
	if (dt.dayOfWeek() == DateTime::SUNDAY)
	{
		// ...
	}
}


#include "Poco/LocalDateTime.h"
using Poco::LocalDateTime;

void testLocalDateTime()
{
	LocalDateTime now; // the current date and local time
	int year = now.year();
	int month = now.month();
	int day = now.day();
	int dow = now.dayOfWeek();
	int doy = now.dayOfYear();
	int hour = now.hour();
	int hour12 = now.hourAMPM();
	int min = now.minute();
	int sec = now.second();
	int ms = now.millisecond();
	int us = now.microsecond();
	int tzd = now.tzd();
	double jd = now.julianDay();
	Poco::Timestamp ts = now.timestamp();

	LocalDateTime dt1(1973, 9, 12, 2, 30, 45); // 1973-09-12 02:30:45
	dt1.assign(2006, 10, 13, 13, 45, 12, 345); // 2006-10-13 12:45:12.345
	LocalDateTime dt2(3600, 1973, 9, 12, 2, 30, 45, 0, 0); // UTC +1 hour
	dt2.assign(3600, 2006, 10, 13, 13, 45, 12, 345, 0);
	Poco::Timestamp nowTS;
	LocalDateTime dt3(3600, nowTS); // construct from Timestamp
}

#include "Poco/Timespan.h"
using Poco::Timespan;

void testTimespan()
{
	Timespan ts1(1, 11, 45, 22, 123433); // 1d 11h 45m 22.123433s
	Timespan ts2(33*Timespan::SECONDS); // 33s
	Timespan ts3(2*Timespan::DAYS + 33*Timespan::HOURS); // 3d 33h
	int days = ts1.days(); // 1
	int hours = ts1.hours(); // 11
	int totalHours = ts1.totalHours(); // 35
	int minutes = ts1.minutes(); // 45
	int totalMins = ts1.totalMinutes(); // 2145
	int seconds = ts1.seconds(); // 22
	int totalSecs = ts1.totalSeconds(); // 128722
}

void testTimeCalculstion()
{
	// what is my age?
	DateTime birthdate(1972, 9, 11, 06, 30); // 1973-09-12 02:30:00
	DateTime now;
	Timespan age = now - birthdate;
	int days = age.days(); // in days
	int hours = age.totalHours(); // in hours
	int secs = age.totalSeconds(); // in seconds
	// when was I 10000 days old?
	Timespan span(20000*Timespan::DAYS);
	DateTime dt = birthdate + span;
}

#include "Poco/Timezone.h"
using Poco::Timezone;

void testTimezone()
{
	int utcOffset = Timezone::utcOffset();
	int dst = Timezone::dst();
	bool isDst = Timezone::isDst(Timestamp());
	int tzd = Timezone::tzd();
	std::string name = Timezone::name();
	std::string stdName = Timezone::standardName();
	std::string dstName = Timezone::dstName();
}

#include "Poco/DateTime.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;

void testDateTimeFormat()
{
	Poco::DateTime dt(2006, 10, 22, 15, 22, 34);
	std::string s(DateTimeFormatter::format(dt, "%e %b %Y %H:%M"));	// "22 Oct 2006 15:22"
	Poco::Timestamp now;
	s = DateTimeFormatter::format(now, DateTimeFormat::SORTABLE_FORMAT);	// "2006-10-30 09:27:44"
	Poco::Timespan span(5, 11, 33, 0, 0);
	s = DateTimeFormatter::format(span, "%d days, %H hours, %M minutes");	// "5 days, 11 hours, 33 minutes"
}

#include "Poco/DateTimeParser.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/LocalDateTime.h"
#include "Poco/Timestamp.h"
using Poco::DateTimeParser;
using Poco::DateTimeFormat;
using Poco::DateTime;

void testDateTimeParser()
{
	std::string s("Sat, 1 Jan 2005 12:00:00 GMT");
	int tzd;
	DateTime dt;
	DateTimeParser::parse(DateTimeFormat::RFC1123_FORMAT, s, dt, tzd);
	Poco::Timestamp ts = dt.timestamp();
	Poco::LocalDateTime ldt(tzd, dt);
	bool ok = DateTimeParser::tryParse("2006-10-22", dt, tzd);
	ok = DateTimeParser::tryParse("%e.%n.%Y", "22.10.2006", dt, tzd);
}
#include "Poco/Net/DNS.h"
#include <iostream>
using Poco::Net::DNS;
using Poco::Net::IPAddress;
using Poco::Net::HostEntry;

void testDNS_IPAddress_HostEntry()
{
	const HostEntry& entry = DNS::hostByName("www.google.com");
	std::cout << "Canonical Name: " << entry.name() << std::endl;

	const HostEntry::AliasList& aliases = entry.aliases();
	HostEntry::AliasList::const_iterator it = aliases.begin();
	for (; it != aliases.end(); ++it)
		std::cout << "Alias: " << *it << std::endl;

	const HostEntry::AddressList& addrs = entry.addresses();
	HostEntry::AddressList::const_iterator it2 = addrs.begin();
	for (; it2 != addrs.end(); ++it2)
		std::cout << "Address: " << it2->toString() << std::endl;
}

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"
#include <iostream>

void testStreamSocket()
{
	Poco::Net::SocketAddress sa("www.appinf.com", 80);
	//Poco::Net::SocketAddress sa("192.168.0.10", 5000);
	Poco::Net::StreamSocket socket(sa);
	Poco::Net::SocketStream str(socket);

	str << "GET / HTTP/1.1\r\n"
		"Host: www.appinf.com\r\n"
		"\r\n";
	str.flush();
	Poco::StreamCopier::copyStream(str, std::cout);
}

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/SocketAddress.h"

void testServerSocket()
{
	Poco::Net::ServerSocket srv(8080); // does bind + listen
// 	for (;;)
// 	{
		Poco::Net::StreamSocket ss = srv.acceptConnection();
		Poco::Net::SocketStream str(ss);
		str << "HTTP/1.0 200 OK\r\n"
			"Content-Type: text/html\r\n"
			"\r\n"
			"<html><head><title>My 1st Web Server</title></head>"
			"<body><h1>Hello, world!</h1></body></html>"
			<< std::flush;
//	}
}

#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"

void testUDPSocketClient()
{
	Poco::Net::SocketAddress sa("192.168.0.10", 5001);
	Poco::Net::DatagramSocket dgs;
	dgs.connect(sa);
	Poco::Timestamp now;
	std::string msg = Poco::DateTimeFormatter::format(now,
		"<14>%w %f %H:%M:%S Hello, world!");
	dgs.sendBytes(msg.data(), msg.size());
}

#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include <iostream>

void testUDPSocketServer()
{
	Poco::Net::SocketAddress sa(Poco::Net::IPAddress(), 5002);
	Poco::Net::DatagramSocket dgs(sa);
	char buffer[1024];

// 	for (;;)
// 	{
		Poco::Net::SocketAddress sender;
		int n = dgs.receiveFrom(buffer, sizeof(buffer)-1, sender);
		buffer[n] = '\0';
		std::cout << sender.toString() << ": " << buffer << std::endl;
//	}
}

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/MulticastSocket.h"

void testMulticastSocketClient()
{
	Poco::Net::SocketAddress address("239.255.255.250", 1900);
	Poco::Net::MulticastSocket socket(
		Poco::Net::SocketAddress(
		Poco::Net::IPAddress(), address.port()
		)
		);
	// to receive any data you must join
	socket.joinGroup(address.host());
	Poco::Net::SocketAddress sender;
	char buffer[512];
	int n = socket.receiveFrom(buffer, sizeof(buffer), sender);
	socket.sendTo(buffer, n, sender);
}
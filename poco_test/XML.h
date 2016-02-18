#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/DOM/NodeList.h"

void testDOM()
{
	std::ifstream in("books.xml");
	Poco::XML::InputSource src(in);

	Poco::XML::DOMParser parser;
	Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&src);

	Poco::XML::NodeIterator it(pDoc, Poco::XML::NodeFilter::SHOW_ELEMENT);
	Poco::XML::Node* pNode = it.nextNode();
	while (pNode)
	{
		Poco::XML::NodeList* nl = pNode->childNodes();
		if (nl->length() == 1) 
			if(nl->item(0)->nodeType() == Poco::XML::Node::TEXT_NODE)
			{
				std::cout << pNode->nodeName() << ":" << pNode->nodeValue() << ":" << pNode->innerText() << std::endl;
			}
		pNode = it.nextNode();
	}

	//Poco::XML::XMLString path("/catalog/book/author");
	Poco::XML::XMLString path("/catalog/book[@id='bk103']/author");
	pNode = it.root();
	Poco::XML::Node* searchedNode = pNode->getNodeByPath(path);
	if (searchedNode)
	{
		std::cout << "Searched Node Text = " << searchedNode->innerText() << std::endl;
	}
}

#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/AutoPtr.h" //typedef to Poco::AutoPtr
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"
using namespace Poco::XML;

void createXMLWithDOM()
{
	AutoPtr<Document> pDoc = new Document;
	AutoPtr<Element> pRoot = pDoc->createElement("root");
	pDoc->appendChild(pRoot);

	AutoPtr<Element> pChild1 = pDoc->createElement("child1");
	AutoPtr<Text> pText1 = pDoc->createTextNode("text1");
	pChild1->appendChild(pText1);
	pRoot->appendChild(pChild1);

	AutoPtr<Element> pChild2 = pDoc->createElement("child2");
	AutoPtr<Text> pText2 = pDoc->createTextNode("text2");
	pChild2->appendChild(pText2);
	pRoot->appendChild(pChild2);

	DOMWriter writer;
	writer.setNewLine("\n");
	writer.setOptions(XMLWriter::PRETTY_PRINT);
	writer.writeNode(std::cout, pDoc);
}

#include "Poco/XML/XMLWriter.h"
#include "Poco/SAX/AttributesImpl.h"

void createXMLWithXMLWriter()
{
	std::ofstream str("test.xml");
	XMLWriter writer(str, XMLWriter::WRITE_XML_DECLARATION | XMLWriter::PRETTY_PRINT);
	writer.setNewLine("\n");
	writer.startDocument();
	AttributesImpl attrs;
	//std::string ns("urn:mynamespace");
	std::string ns("");
	attrs.addAttribute("", "", "a1", "", "v1");
	attrs.addAttribute("", "", "a2", "", "v2");
	writer.startElement(ns, "root", "", attrs);
	writer.startElement("", "", "sub");
	writer.characters("characters of sub");
	writer.endElement("", "", "sub");
	writer.endElement(ns, "root", "");
	writer.endDocument();
}
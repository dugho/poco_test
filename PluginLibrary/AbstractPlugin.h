// AbstractPlugin.h
//
// This is used both by the class library and by the application.
#ifndef AbstractPlugin_INCLUDED
#define AbstractPlugin_INCLUDED

#include <string>

class AbstractPlugin
{
public:
	AbstractPlugin();
	virtual ~AbstractPlugin();
	virtual std::string name() const = 0;
};
#endif // AbstractPlugin_INCLUDED.h
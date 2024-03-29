#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;

class Currency : public SmartNode
{
public:
	virtual LocalizedString* getString() = 0;
	virtual LocalizedString* getStringPlural() = 0;
	virtual const std::string& getIconResource() = 0;
	virtual const std::string& getIdentifier() = 0;

	void setCount(int count);
	int getCount();

protected:
	Currency();
	virtual ~Currency();

private:
	typedef SmartNode super;

	int count = 0;
};

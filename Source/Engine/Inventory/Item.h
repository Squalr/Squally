#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class LocalizedString;

class Item : public SmartNode
{
public:
	LocalizedString* cloneName();
	std::string getIconResource();

	virtual std::string getSerializationKey() = 0;
	virtual cocos2d::ValueMap serialize();

protected:
	Item(LocalizedString* name, std::string iconResource);
	virtual ~Item();
	void onEnter() override;
	void initializeListeners() override;

	LocalizedString* name;
	std::string iconResource;

private:
	typedef SmartNode super;
};

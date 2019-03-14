#pragma once

#include "Engine/Maps/SerializableObject.h"

using namespace cocos2d;

class Chest : public SerializableObject
{
public:
	static Chest* create(cocos2d::ValueMap& initProperties);

	virtual void open();
	virtual void close();

	static const std::string MapKeyChest;

protected:
	Chest(cocos2d::ValueMap& initProperties);
	virtual ~Chest();

	cocos2d::Node* chestOpen;
	cocos2d::Node* chestClosed;

private:
	typedef SerializableObject super;
};

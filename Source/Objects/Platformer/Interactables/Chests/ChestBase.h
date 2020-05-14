#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

using namespace cocos2d;

class MinMaxPool;

class ChestBase : public InteractObject
{
public:

protected:
	ChestBase(cocos2d::ValueMap& properties, cocos2d::Size interactSize);
	virtual ~ChestBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	virtual bool tryOpen();
	virtual void unlockAndGiveItems();

	cocos2d::Node* chestOpen;
	cocos2d::Node* chestClosed;

	MinMaxPool* chestPool;

private:
	typedef InteractObject super;

	void open(bool doSave);
	void close();

	std::string chestOpenArgs;

	static const std::string PropertyRewardPool;
	static const std::string SaveKeyIsOpen;
};

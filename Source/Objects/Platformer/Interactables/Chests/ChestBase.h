#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

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
	void open(bool doSave);
	void close();

	cocos2d::Node* chestOpen;
	cocos2d::Node* chestClosed;

	MinMaxPool* chestPool;

private:
	typedef InteractObject super;

	std::string chestOpenArgs;

	static const std::string PropertyRewardPool;
	static const std::string SaveKeyIsOpen;
};

#pragma once

#include "Objects/Platformer/Chests/ChestBase.h"

using namespace cocos2d;

class CipherPuzzleData;
class CollisionObject;
class InteractMenu;

class CipherChest : public ChestBase
{
public:
	static CipherChest* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCipherChest;

protected:
	CipherChest(cocos2d::ValueMap& properties);
	virtual ~CipherChest();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract() override;

private:
	typedef ChestBase super;
	
	CipherPuzzleData* buildPuzzleData();
	CipherPuzzleData* cipherPuzzleData;

	static const std::string MapKeyPropertyInputs;
	static const std::string MapKeyPropertyRule;
	static const std::string MapKeyPropertyTokens;
	static const std::string MapKeyPropertyDataType;
	static const std::string MapKeyPropertyTutorial;
};

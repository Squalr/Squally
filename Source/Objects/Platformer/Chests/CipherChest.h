#pragma once

#include "Objects/Platformer/Chests/Chest.h"

using namespace cocos2d;

class CipherPuzzleData;
class CollisionObject;
class InteractMenu;

class CipherChest : public Chest
{
public:
	static CipherChest* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyCipherChest;

protected:
	void onInteract() override;

private:
	typedef Chest super;
	CipherChest(cocos2d::ValueMap& properties);
	virtual ~CipherChest();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	CipherPuzzleData* buildPuzzleData();

	CipherPuzzleData* cipherPuzzleData;

	static const std::string MapKeyPropertyInputs;
	static const std::string MapKeyPropertyRule;
	static const std::string MapKeyPropertyTokens;
	static const std::string MapKeyPropertyDataType;
	static const std::string MapKeyPropertyTutorial;
};

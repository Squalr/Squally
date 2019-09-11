#pragma once

#include "Objects/Platformer/Collectables/Chest.h"

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
	~CipherChest();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	CipherPuzzleData* buildPuzzleData();

	CipherPuzzleData* cipherPuzzleData;

	static const std::string MapKeyPropertyInputsEasy;
	static const std::string MapKeyPropertyInputsHard;
	static const std::string MapKeyPropertyRuleEasy;
	static const std::string MapKeyPropertyRuleHard;
	static const std::string MapKeyPropertyRewards;
	static const std::string MapKeyPropertyBonusRewards;
};

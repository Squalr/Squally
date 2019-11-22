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
	~CipherChest();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	CipherPuzzleData* buildPuzzleData();
	void onUnlock(CipherPuzzleData* puzzleData, bool isHardModeEnabled);

	CipherPuzzleData* cipherPuzzleData;

	static const std::string MapKeyPropertyInputsEasy;
	static const std::string MapKeyPropertyInputsHard;
	static const std::string MapKeyPropertyRuleEasy;
	static const std::string MapKeyPropertyRuleHard;
	static const std::string MapKeyPropertyBonusReward;
	static const std::string MapKeyPropertyTokensEasy;
	static const std::string MapKeyPropertyTokensHard;
	static const std::string MapKeyPropertyTutorial;
};

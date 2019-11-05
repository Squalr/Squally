#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class LocalizedString;
class PlatformerEntity;

class HexusBehaviorBase : public AttachedBehavior
{
public:

protected:
	HexusBehaviorBase(GameObject* owner, LocalizedString* dialogueChoiceOverride = nullptr);
	~HexusBehaviorBase();

	virtual std::vector<CardData*> generateDeck() = 0;
	virtual MinMaxPool* generateReward() = 0;
	virtual std::string getWinLossSaveKey() = 0;
	virtual std::string getBackgroundResource() = 0;
	
	void onLoad() override;
	void onWin();
	void onLoss();
	void onDraw();

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;

	HexusOpponentData* createOpponentData();

	LocalizedString* dialogueChoiceOverride;
	MinMaxPool* rewardPool;
};

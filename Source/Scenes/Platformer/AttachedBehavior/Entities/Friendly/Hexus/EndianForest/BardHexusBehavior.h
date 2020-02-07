#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class PlatformerEntity;

class BardHexusBehavior : public HexusBehaviorBase
{
public:
	static BardHexusBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	BardHexusBehavior(GameObject* owner);
	virtual ~BardHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};

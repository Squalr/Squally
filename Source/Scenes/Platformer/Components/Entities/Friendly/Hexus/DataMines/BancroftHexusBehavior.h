#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class BancroftHexusBehavior : public HexusBehaviorBase
{
public:
	static BancroftHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	BancroftHexusBehavior(GameObject* owner);
	virtual ~BancroftHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};

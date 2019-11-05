#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class LocalizedString;
class PlatformerEntity;
class StateOverride;

class HexusBehaviorBase : public AttachedBehavior
{
public:
	void registerWinCallback(std::function<void()> winCallback);
	void registerLossCallback(std::function<void()> lossCallback);
	void registerDrawCallback(std::function<void()> drawCallback);

protected:
	HexusBehaviorBase(GameObject* owner, LocalizedString* dialogueChoiceOverride = nullptr);
	~HexusBehaviorBase();

	virtual MinMaxPool* generateReward() = 0;
	virtual std::string getWinLossSaveKey() = 0;
	virtual std::string getBackgroundResource() = 0;
	virtual std::vector<CardData*> generateDeck() = 0;
	virtual StateOverride* getStateOverride() = 0;
	
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

	std::vector<std::function<void()>> winCallbacks;
	std::vector<std::function<void()>> lossCallbacks;
	std::vector<std::function<void()>> drawCallbacks;
};

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

#include "Engine/SmartNode.h"
#include "Events/HexusEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPreview : public SmartNode
{
public:
	static HexusOpponentPreview * create(HexusOpponentData* opponentData, std::function<void(HexusEvents::HexusGameResultEventArgs)> onGameEndCallback);

	void disableInteraction();
	void enableInteraction();

	HexusOpponentData* hexusOpponentData;

protected:
	HexusOpponentPreview(HexusOpponentData* opponentData, std::function<void(HexusEvents::HexusGameResultEventArgs)> onGameEndCallback);
	~HexusOpponentPreview();

private:
	void initializePositions() override;
	void onOpponentClick(MenuSprite* HexusOpponentPreview);

	std::function<void(HexusOpponentPreview*)> onMouseOverEvent;
	std::function<void(HexusEvents::HexusGameResultEventArgs)> onGameEndCallback;

	AnimationNode* opponentSprite;
	LayerColor* disabledLayer;
	ClippingNode* frameClip;
	SpriterEngine::EntityInstance* opponentEntity;
	MenuSprite* frame;
};

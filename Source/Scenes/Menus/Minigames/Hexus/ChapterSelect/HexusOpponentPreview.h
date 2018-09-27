#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/SmartNode.h"
#include "Events/HexusEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPreview : public SmartNode
{
public:
	static HexusOpponentPreview * create(HexusOpponentData* opponentData, std::function<void(HexusEvents::HexusGameResultEventArgs)> onGameEndCallback, std::string backgroundResource);

	void disableInteraction();
	void enableInteraction();

protected:
	HexusOpponentPreview(HexusOpponentData* opponentData, std::function<void(HexusEvents::HexusGameResultEventArgs)> onGameEndCallback, std::string backgroundResource);
	~HexusOpponentPreview();

private:
	void initializePositions() override;
	void onOpponentClick(MenuSprite* HexusOpponentPreview);

	std::function<void(HexusOpponentPreview*)> onMouseOverEvent;
	HexusOpponentData* hexusOpponentData;
	std::function<void(HexusEvents::HexusGameResultEventArgs)> onGameEndCallback;

	AnimationNode* opponentSprite;
	LayerColor* disabledLayer;
	ClippingNode* frameClip;
	SpriterEngine::EntityInstance* opponentEntity;
	MenuSprite* frame;
};

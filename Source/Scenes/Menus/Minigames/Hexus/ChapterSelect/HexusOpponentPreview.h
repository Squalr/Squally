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
	static HexusOpponentPreview * create(HexusOpponentData* opponentData);

protected:
	HexusOpponentPreview(HexusOpponentData* opponentData);
	~HexusOpponentPreview();

private:
	void initializePositions() override;
	void onOpponentClick(MenuSprite* HexusOpponentPreview);

	std::function<void(HexusOpponentPreview*)> onMouseOverEvent;
	HexusOpponentData* hexusOpponentData;
	
	AnimationNode* opponentSprite;
	ClippingNode* frameClip;
	SpriterEngine::EntityInstance* opponentEntity;
	MenuSprite* frame;
};

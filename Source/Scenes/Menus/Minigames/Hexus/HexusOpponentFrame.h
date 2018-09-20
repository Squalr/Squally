#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/SmartNode.h"
#include "Events/HexusEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentFrame : public SmartNode
{
public:
	static HexusOpponentFrame * create(HexusOpponentData* opponentData, std::function<void(HexusOpponentFrame*)> onMouseOver);

protected:
	HexusOpponentFrame(HexusOpponentData* opponentData, std::function<void(HexusOpponentFrame*)> onMouseOver);
	~HexusOpponentFrame();

private:
	void initializePositions() override;
	void onOpponentClick(MenuSprite* HexusOpponentFrame);
	void onOpponentMouseOver(MenuSprite* HexusOpponentFrame);

	std::function<void(HexusOpponentFrame*)> onMouseOverEvent;
	HexusOpponentData* hexusOpponentData;
	
	AnimationNode* opponentSprite;
	ClippingNode* frameClip;
	SpriterEngine::EntityInstance* opponentEntity;
	MenuSprite* frame;
};

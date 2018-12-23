#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingNode;
	class LayerColor;
}

class HexusOpponentData;
class MenuSprite;
class SmartAnimationNode;

class HexusOpponentPreview : public SmartNode
{
public:
	static HexusOpponentPreview* create(HexusOpponentData* opponentData);

	void disableInteraction();
	void enableInteraction();

	HexusOpponentData* hexusOpponentData;

protected:
	HexusOpponentPreview(HexusOpponentData* opponentData);
	~HexusOpponentPreview();

private:
	void initializePositions() override;
	void onOpponentClick(MenuSprite* HexusOpponentPreview);

	std::function<void(HexusOpponentPreview*)> onMouseOverEvent;

	SmartAnimationNode* opponentSprite;
	cocos2d::LayerColor* disabledLayer;
	cocos2d::ClippingNode* frameClip;
	MenuSprite* frame;
};

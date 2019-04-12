#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingNode;
	class LayerColor;
	class Sprite;
}

class HexusOpponentData;
class ClickableNode;
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
	typedef SmartNode super;
	void initializePositions() override;
	void onOpponentClick();

	std::function<void(HexusOpponentPreview*)> onMouseOverEvent;

	SmartAnimationNode* opponentSprite;
	cocos2d::LayerColor* disabledLayer;
	cocos2d::ClippingNode* frameClip;
	cocos2d::Sprite* lockedSprite;
	ClickableNode* frame;
};

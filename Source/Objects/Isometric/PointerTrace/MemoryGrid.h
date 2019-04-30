#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class LocalizedLabel;
class UIBoundObject;

class MemoryGrid : public HackableObject
{
public:
	static MemoryGrid* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyMemoryGrid;

protected:
	MemoryGrid(cocos2d::ValueMap& initProperties);
	~MemoryGrid();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef HackableObject super;

	std::vector<ClickableNode*> gridHitBoxes;
	std::vector<LocalizedLabel*> addresses;
	std::vector<UIBoundObject*> bindings;

	cocos2d::Sprite* eaxMarker;
	cocos2d::Sprite* ebxMarker;
	cocos2d::Sprite* ecxMarker;
	cocos2d::Sprite* edxMarker;
	cocos2d::Sprite* ediMarker;
	cocos2d::Sprite* esiMarker;
	cocos2d::Sprite* ebpMarker;
	cocos2d::Sprite* espMarker;
	cocos2d::Node* addressesNode;
	cocos2d::Node* gridHitBoxesNode;
	cocos2d::Sprite* selector;

	int gridWidth;
	int gridHeight;
};

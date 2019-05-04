#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class LocalizedLabel;
class RegisterMarker;
class UIBoundObject;

class MemoryGrid : public HackableObject
{
public:
	static MemoryGrid* create(const cocos2d::ValueMap& properties);

	static const std::string MapKeyMemoryGrid;

	int getMaxIndex();
	int getGridWidth();
	int getGridHeight();
	int relativeCoordsToGridIndex(cocos2d::Vec2 relativeCoordinates);
	cocos2d::Vec2 gridIndexToRelativePosition(int gridIndex);
	int worldCoordsToGridIndex(cocos2d::Vec2 worldCoordinates);
	cocos2d::Vec2 gridIndexToWorldPosition(int gridIndex);

protected:
	MemoryGrid(const cocos2d::ValueMap& properties);
	~MemoryGrid();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef HackableObject super;

	void positionRegisterMarkers();

	std::vector<ClickableNode*> gridHitBoxes;
	std::vector<LocalizedLabel*> addresses;
	std::vector<UIBoundObject*> bindings;

	RegisterMarker* eaxMarker;
	RegisterMarker* ebxMarker;
	RegisterMarker* ecxMarker;
	RegisterMarker* edxMarker;
	RegisterMarker* ediMarker;
	RegisterMarker* esiMarker;
	RegisterMarker* ebpMarker;
	RegisterMarker* espMarker;
	cocos2d::Node* addressesNode;
	cocos2d::Node* gridHitBoxesNode;
	cocos2d::Sprite* selector;

	std::vector<RegisterMarker*> markers;

	int gridWidth;
	int gridHeight;
};

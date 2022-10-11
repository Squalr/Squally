#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class DrawNode;
	class Sprite;
}

class ClickableNode;
class ConstantString;
class LocalizedLabel;
class RegisterMarker;

class MemoryGrid : public HackableObject
{
public:
	static MemoryGrid* create(const cocos2d::ValueMap& properties);

	void setInitialState();
	void resetState();
	int getMaxIndex();
	int getGridWidth();
	int getGridHeight();
	int relativeCoordsToGridIndex(cocos2d::Vec2 relativeCoordinates);
	cocos2d::Vec2 gridIndexToRelativePosition(int gridIndex);
	int worldCoordsToGridIndex(cocos2d::Vec2 worldCoordinates);
	cocos2d::Vec2 gridIndexToWorldPosition(int gridIndex);

	static const std::string MapKey;

protected:
	MemoryGrid(const cocos2d::ValueMap& properties);
	virtual ~MemoryGrid();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HackableObject super;

	void positionRegisterMarkers();
	void buildValueLabels();

	std::vector<ClickableNode*> gridHitBoxes;
	std::vector<int> initialValues;
	std::vector<int> values;
	std::vector<ConstantString*> valueStrings;
	std::vector<LocalizedLabel*> valueLabels;
	std::vector<LocalizedLabel*> addresses;

	cocos2d::DrawNode* gridLines = nullptr;
	RegisterMarker* eaxMarker = nullptr;
	RegisterMarker* ebxMarker = nullptr;
	RegisterMarker* ecxMarker = nullptr;
	RegisterMarker* edxMarker = nullptr;
	RegisterMarker* ediMarker = nullptr;
	RegisterMarker* esiMarker = nullptr;
	RegisterMarker* ebpMarker = nullptr;
	RegisterMarker* espMarker = nullptr;
	cocos2d::Node* labelsNode = nullptr;
	cocos2d::Node* gridHitBoxesNode = nullptr;
	cocos2d::Sprite* selector = nullptr;

	std::vector<RegisterMarker*> markers;

	bool isValueFocused = false;
	bool isAddressFocused = false;
	int gridWidth = 0;
	int gridHeight = 0;

	int initialEax = 0;
	int initialEbx = 0;
	int initialEcx = 0;
	int initialEdx = 0;
	int initialEdi = 0;
	int initialEsi = 0;
	int initialEbp = 0;
	int initialEsp = 0;

	static const cocos2d::Color4B GridColor;
};

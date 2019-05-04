#include "MemoryGrid.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PointerTraceEvents.h"
#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarker.h"
#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarkerEax.h"
#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarkerEbp.h"
#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarkerEbx.h"
#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarkerEcx.h"
#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarkerEdi.h"
#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarkerEdx.h"
#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarkerEsi.h"
#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarkerEsp.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string MemoryGrid::MapKeyMemoryGrid = "memory-grid";

MemoryGrid* MemoryGrid::create(const ValueMap& properties)
{
	MemoryGrid* instance = new MemoryGrid(properties);

	instance->autorelease();

	return instance;
}

MemoryGrid::MemoryGrid(const ValueMap& properties) : HackableObject(properties)
{
	this->addresses = std::vector<LocalizedLabel*>();
	this->gridHitBoxes = std::vector<ClickableNode*>();
	this->eaxMarker = RegisterMarkerEax::create();
	this->ebxMarker = RegisterMarkerEbx::create();
	this->ecxMarker = RegisterMarkerEcx::create();
	this->edxMarker = RegisterMarkerEdx::create();
	this->ediMarker = RegisterMarkerEdi::create();
	this->esiMarker = RegisterMarkerEsi::create();
	this->ebpMarker = RegisterMarkerEbp::create();
	this->espMarker = RegisterMarkerEsp::create();
	this->addressesNode = Node::create();
	this->gridHitBoxesNode = Node::create();
	this->selector = Sprite::create(IsometricObjectResources::PointerTrace_Selector);
	this->markers = std::vector<RegisterMarker*>();

	this->markers.push_back(this->eaxMarker);
	this->markers.push_back(this->ebxMarker);
	this->markers.push_back(this->ecxMarker);
	this->markers.push_back(this->edxMarker);
	this->markers.push_back(this->ediMarker);
	this->markers.push_back(this->esiMarker);
	this->markers.push_back(this->ebpMarker);
	this->markers.push_back(this->espMarker);

	float width = this->properties[super::MapKeyWidth].asFloat();
	float height = this->properties[super::MapKeyWidth].asFloat();

	this->gridWidth = std::round(width / 128.0f);
	this->gridHeight = std::round(height / 128.0f);

	for (int x = 0; x < this->gridWidth; x++)
	{
		for (int y = 0; y < this->gridHeight; y++)
		{
			int gridIndex = y + x * this->gridWidth;
			std::string indexString = std::to_string(gridIndex);

			LocalizedLabel* indexLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, ConstantString::create(indexString));
			
			indexLabel->enableOutline(Color4B::BLACK, 2);
			
			this->addresses.push_back(indexLabel);

			ClickableNode* gridHitBox = ClickableNode::create();

			gridHitBox->setContentSize(Size(128.0f, 64.0f));

			this->gridHitBoxes.push_back(gridHitBox);
		}	
	}

	for (auto it = this->addresses.begin(); it != this->addresses.end(); it++)
	{
		this->addressesNode->addChild(*it);
	}

	for (auto it = this->gridHitBoxes.begin(); it != this->gridHitBoxes.end(); it++)
	{
		this->gridHitBoxesNode->addChild(*it);
	}

	this->addChild(this->eaxMarker);
	this->addChild(this->ebxMarker);
	this->addChild(this->ecxMarker);
	this->addChild(this->edxMarker);
	this->addChild(this->ediMarker);
	this->addChild(this->esiMarker);
	this->addChild(this->ebpMarker);
	this->addChild(this->espMarker);
	this->addChild(this->addressesNode);
	this->addChild(this->gridHitBoxesNode);
	this->addChild(this->selector);
}

MemoryGrid::~MemoryGrid()
{
}

void MemoryGrid::onEnter()
{
	super::onEnter();

	this->selector->setOpacity(0);

	for (auto it = this->addresses.begin(); it != this->addresses.end(); it++)
	{
		(*it)->setOpacity(0);
	}

	// This is a shitty hack to ensure the grid has a Z index below all isometric objects
	this->setLocalZOrder(-12345678);
}

void MemoryGrid::initializePositions()
{
	super::initializePositions();

	int index = 0;

	for (auto it = this->addresses.begin(); it != this->addresses.end(); index++, it++)
	{
		Vec2 realCoords = this->gridIndexToRelativePosition(index);

		(*it)->setPosition(realCoords);
		this->gridHitBoxes[index]->setPosition(realCoords);
	}
}

void MemoryGrid::initializeListeners()
{
	super::initializeListeners();

	int index = 0;

	for (auto it = this->gridHitBoxes.begin(); it != this->gridHitBoxes.end(); index++, it++)
	{
		(*it)->setMouseOverCallback([=](MouseEvents::MouseEventArgs* args)
		{
			this->selector->setPosition((*it)->getPosition());
			this->selector->setOpacity(255);
			this->addresses[index]->setOpacity(255);
		});

		(*it)->setMouseOutCallback([=](MouseEvents::MouseEventArgs* args)
		{
			this->addresses[index]->setOpacity(0);
		});

		(*it)->setIntersectFunction([=](Vec2 mousePos)
		{
			return GameUtils::intersectsIsometric(*it, mousePos);
		});
	}

	this->addEventListener(EventListenerCustom::create(PointerTraceEvents::EventUpdateRegister, [=](EventCustom* eventCustom)
	{
		this->positionRegisterMarkers();
	}));
}

void MemoryGrid::update(float dt)
{
	super::update(dt);
}

int MemoryGrid::relativeCoordsToGridIndex(cocos2d::Vec2 relativeCoordinates)
{
	float y = (relativeCoordinates.x - 128.0f + float(this->getGridWidth()) * 128.0f) / 2.0f - relativeCoordinates.y;
	float x = relativeCoordinates.y * 2.0f + y;

	int gridX = std::round(x / 128.0f);
	int gridY = std::round(y / 128.0f);
	int gridIndex = gridX + this->getGridWidth() * gridY;

	return gridIndex;
}

cocos2d::Vec2 MemoryGrid::gridIndexToRelativePosition(int gridIndex)
{
	float x = float(gridIndex % this->gridWidth) * 128.0f;
	float y = float(gridIndex / this->gridWidth) * 128.0f;

	float realX = (x + y) + 128.0f - (this->gridWidth) * 128.0f;
	float realY = (x - y) / 2.0f;

	return Vec2(realX, realY);
}

int MemoryGrid::worldCoordsToGridIndex(cocos2d::Vec2 worldCoordinates)
{
	return this->relativeCoordsToGridIndex(this->convertToNodeSpace(worldCoordinates));
}

cocos2d::Vec2 MemoryGrid::gridIndexToWorldPosition(int gridIndex)
{
	return this->convertToWorldSpace(this->gridIndexToRelativePosition(gridIndex));
}

int MemoryGrid::getMaxIndex()
{
	return this->getGridWidth() * this->getGridHeight();
}

int MemoryGrid::getGridWidth()
{
	return this->gridWidth;
}

int MemoryGrid::getGridHeight()
{
	return this->gridHeight;
}

void MemoryGrid::positionRegisterMarkers()
{
	for (auto it = this->markers.begin(); it != this->markers.end(); it++)
	{
		(*it)->moveToRegister(this);
	}
}

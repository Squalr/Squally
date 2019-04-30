#include "MemoryGrid.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

const std::string MemoryGrid::MapKeyMemoryGrid = "memory-grid";

MemoryGrid* MemoryGrid::create(ValueMap& initProperties)
{
	MemoryGrid* instance = new MemoryGrid(initProperties);

	instance->autorelease();

	return instance;
}

MemoryGrid::MemoryGrid(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->addresses = std::vector<LocalizedLabel*>();
	this->eaxMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EaxMarker);
	this->ebxMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbxMarker);
	this->ecxMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EcxMarker);
	this->edxMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdxMarker);
	this->ediMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdiMarker);
	this->esiMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EsiMarker);
	this->ebpMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbpMarker);
	this->espMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EspMarker);
	this->addressesNode = Node::create();

	float width = initProperties[super::MapKeyWidth].asFloat();
	float height = initProperties[super::MapKeyWidth].asFloat();

	this->gridWidth = std::round(width / 128.0f);
	this->gridHeight = std::round(height / 128.0f);

	for (int x = 0; x < this->gridWidth; x++)
	{
		for (int y = 0; y < this->gridHeight; y++)
		{
			int realIndex = x + y * this->gridWidth;
			std::string indexString = std::to_string(realIndex);

			LocalizedLabel* indexLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, ConstantString::create(indexString));
			
			indexLabel->enableOutline(Color4B::BLACK, 2);
			
			this->addresses.push_back(indexLabel);
			this->addressesNode->addChild(indexLabel);
		}	
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
}

MemoryGrid::~MemoryGrid()
{
}

void MemoryGrid::onEnter()
{
	super::onEnter();
}

void MemoryGrid::initializePositions()
{
	super::initializePositions();

	int index = 0;

	for (auto it = this->addresses.begin(); it != this->addresses.end(); index++, it++)
	{
		float x = float(index % this->gridWidth) * 128.0f;
		float y = float(index / this->gridWidth) * 128.0f;

		float realX = (x + y) + 128.0f - (this->gridWidth) * 128.0f;
		float realY = (y - x) / 2.0f;

		(*it)->setPosition(Vec2(realX, realY));
	}
}

#include "MemoryGrid.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"

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
	this->gridHitBoxes = std::vector<ClickableNode*>();
	this->eaxMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EaxMarker);
	this->ebxMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbxMarker);
	this->ecxMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EcxMarker);
	this->edxMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdxMarker);
	this->ediMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdiMarker);
	this->esiMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EsiMarker);
	this->ebpMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EbpMarker);
	this->espMarker = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EspMarker);
	this->addressesNode = Node::create();
	this->gridHitBoxesNode = Node::create();
	this->selector = Sprite::create(IsometricObjectResources::PointerTrace_Selector);

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

	this->eaxMarker->setOpacity(0);
	this->ebxMarker->setOpacity(0);
	this->ecxMarker->setOpacity(0);
	this->edxMarker->setOpacity(0);
	this->ediMarker->setOpacity(0);
	this->esiMarker->setOpacity(0);
	this->ebpMarker->setOpacity(0);
	this->espMarker->setOpacity(0);
	this->selector->setOpacity(0);

	for (auto it = this->addresses.begin(); it != this->addresses.end(); it++)
	{
		(*it)->setOpacity(0);
	}
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
		this->gridHitBoxes[index]->setPosition(Vec2(realX, realY));
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
}

void MemoryGrid::update(float dt)
{
	super::update(dt);
}

int MemoryGrid::getGridWidth()
{
	return this->gridWidth;
}

int MemoryGrid::getGridHeight()
{
	return this->gridHeight;
}


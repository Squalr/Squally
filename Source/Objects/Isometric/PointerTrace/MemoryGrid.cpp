#include "MemoryGrid.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Events/ObjectEvents.h"
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
const Color4B MemoryGrid::GridColor = Color4B(0, 0, 0, 128);

MemoryGrid* MemoryGrid::create(const ValueMap& properties)
{
	MemoryGrid* instance = new MemoryGrid(properties);

	instance->autorelease();

	return instance;
}

MemoryGrid::MemoryGrid(const ValueMap& properties) : HackableObject(properties)
{
	this->addresses = std::vector<LocalizedLabel*>();
	this->values = std::vector<int>();
	this->initialValues = std::vector<int>();
	this->valueStrings = std::vector<ConstantString*>();
	this->valueLabels = std::vector<LocalizedLabel*>();
	this->gridHitBoxes = std::vector<ClickableNode*>();
	this->gridLines = DrawNode::create();
	this->eaxMarker = RegisterMarkerEax::create();
	this->ebxMarker = RegisterMarkerEbx::create();
	this->ecxMarker = RegisterMarkerEcx::create();
	this->edxMarker = RegisterMarkerEdx::create();
	this->ediMarker = RegisterMarkerEdi::create();
	this->esiMarker = RegisterMarkerEsi::create();
	this->ebpMarker = RegisterMarkerEbp::create();
	this->espMarker = RegisterMarkerEsp::create();
	this->labelsNode = Node::create();
	this->gridHitBoxesNode = Node::create();
	this->selector = Sprite::create(IsometricObjectResources::PointerTrace_Selector);
	this->markers = std::vector<RegisterMarker*>();
	this->isAddressFocused = false;
	this->isValueFocused = false;
	this->initialEax = 0;
	this->initialEbx = 0;
	this->initialEcx = 0;
	this->initialEdx = 0;
	this->initialEdi = 0;
	this->initialEsi = 0;
	this->initialEbp = 0;
	this->initialEsp = 0;

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
			ConstantString* valueString = ConstantString::create(std::to_string(0));
			LocalizedLabel* valueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::M3, valueString);
			ClickableNode* gridHitBox = ClickableNode::create();

			indexLabel->setTextColor(Color4B(224, 224, 224, 255));
			valueLabel->setTextColor(Color4B(224, 224, 224, 255));

			indexLabel->enableOutline(Color4B::BLACK, 4);
			valueLabel->enableOutline(Color4B::BLACK, 4);
			gridHitBox->setContentSize(Size(128.0f, 64.0f));
			
			this->addresses.push_back(indexLabel);
			this->values.push_back(0);
			this->initialValues.push_back(0);
			this->valueStrings.push_back(valueString);
			this->valueLabels.push_back(valueLabel);
			this->gridHitBoxes.push_back(gridHitBox);
		}	
	}
	
	float totalWidth = float(this->gridWidth) * 128.0f;
	float totalHeight = float(this->gridHeight) * 128.0f;

	for (int y = 0; y <= this->gridWidth; y++)
	{
		int gridIndex = y * this->gridWidth;

		Vec2 source = this->gridIndexToRelativePosition(gridIndex) - Vec2(128.0f, 0.0f);
		Vec2 dest = source + Vec2(totalWidth, totalHeight / 2.0f);
		Vec2 dropDest = source - Vec2(0.0f, 128.0f);

		this->gridLines->drawSegment(source, dest, 3.0f, Color4F(MemoryGrid::GridColor));
		this->gridLines->drawSegment(source, dropDest, 3.0f, Color4F(MemoryGrid::GridColor));
	}

	Vec2 source = this->gridIndexToRelativePosition(0) - Vec2(128.0f, 0.0f);

	for (int x = 0; x <= this->gridWidth; x++)
	{
		int gridIndex = x;

		Vec2 dest = source + Vec2(totalWidth, - totalHeight / 2.0f);
		Vec2 dropDest = dest - Vec2(0.0f, 128.0f);

		this->gridLines->drawSegment(source, dest, 3.0f, Color4F(MemoryGrid::GridColor));
		this->gridLines->drawSegment(dest, dropDest, 3.0f, Color4F(MemoryGrid::GridColor));

		source += Vec2(128.0f, 64.0f);
	}

	for (auto it = this->addresses.begin(); it != this->addresses.end(); it++)
	{
		this->labelsNode->addChild(*it);
	}

	for (auto it = this->valueLabels.begin(); it != this->valueLabels.end(); it++)
	{
		this->labelsNode->addChild(*it);
	}

	for (auto it = this->gridHitBoxes.begin(); it != this->gridHitBoxes.end(); it++)
	{
		this->gridHitBoxesNode->addChild(*it);
	}

	this->addChild(this->gridLines);
	this->addChild(this->eaxMarker);
	this->addChild(this->ebxMarker);
	this->addChild(this->ecxMarker);
	this->addChild(this->edxMarker);
	this->addChild(this->ediMarker);
	this->addChild(this->esiMarker);
	this->addChild(this->ebpMarker);
	this->addChild(this->espMarker);
	this->addChild(this->labelsNode);
	this->addChild(this->gridHitBoxesNode);
	this->addChild(this->selector);
}

MemoryGrid::~MemoryGrid()
{
	for (auto it = this->addresses.begin(); it != this->addresses.end(); it++)
	{
		ObjectEvents::TriggerUnbindObject(*it);
	}

	for (auto it = this->valueLabels.begin(); it != this->valueLabels.end(); it++)
	{
		ObjectEvents::TriggerUnbindObject(*it);
	}
}

void MemoryGrid::onEnter()
{
	super::onEnter();

	this->selector->setOpacity(0);

	for (auto it = this->addresses.begin(); it != this->addresses.end(); it++)
	{
		ObjectEvents::TriggerMoveObjectToTopLayer(ObjectEvents::RelocateObjectArgs(*it));
		(*it)->setOpacity(0);
	}

	for (auto it = this->valueLabels.begin(); it != this->valueLabels.end(); it++)
	{
		ObjectEvents::TriggerMoveObjectToTopLayer(ObjectEvents::RelocateObjectArgs(*it));
		(*it)->setOpacity(0);
	}

	RegisterState::setRegisterMax(this->values.size() - 1);

	// This is a shitty hack to ensure the grid has a Z index below all isometric objects
	this->setLocalZOrder(-123456789);
}

void MemoryGrid::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->positionRegisterMarkers();
}

void MemoryGrid::initializePositions()
{
	super::initializePositions();

	int index = 0;

	for (auto it = this->addresses.begin(); it != this->addresses.end(); index++, it++)
	{
		Vec2 realCoords = this->gridIndexToRelativePosition(index);

		(*it)->setPosition(realCoords + Vec2(0.0f, 48.0f));
		this->gridHitBoxes[index]->setPosition(realCoords);
		this->valueLabels[index]->setPosition(realCoords - Vec2(0.0f, 16.0f));
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

			this->valueLabels[index]->setOpacity(255);
			this->addresses[index]->setOpacity(255);
		});

		(*it)->setMouseOutCallback([=](MouseEvents::MouseEventArgs* args)
		{
			if (!this->isAddressFocused)
			{
				this->addresses[index]->setOpacity(0);
			}

			if (!this->isValueFocused)
			{
				this->valueLabels[index]->setOpacity(0);
			}
		});

		(*it)->setIntersectFunction([=](Vec2 mousePos)
		{
			return GameUtils::intersectsIsometric(*it, mousePos);
		});
	}

	this->addEventListener(EventListenerCustom::create(PointerTraceEvents::EventWriteValue, [=](EventCustom* eventCustom)
	{
		PointerTraceEvents::PointerTraceWriteArgs* args = static_cast<PointerTraceEvents::PointerTraceWriteArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			if (args->address > 0 && args->address < this->values.size())
			{
				this->values[args->address] = args->value;

				this->valueStrings[args->address]->setString(std::to_string(args->value));
			}
		}
	}));

	this->addEventListener(EventListenerCustom::create(PointerTraceEvents::EventReadValue, [=](EventCustom* eventCustom)
	{
		PointerTraceEvents::PointerTraceReadArgs* args = static_cast<PointerTraceEvents::PointerTraceReadArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			if (args->address > 0 && args->address < this->values.size())
			{
				if (args->onReadCallback != nullptr)
				{
					args->onReadCallback(this->values[args->address]);
				}
			}
		}
	}));

	this->addEventListener(EventListenerCustom::create(PointerTraceEvents::EventUpdateRegister, [=](EventCustom* eventCustom)
	{
		this->positionRegisterMarkers();
	}));
}

void MemoryGrid::update(float dt)
{
	super::update(dt);

	if (Input::isKeyJustPressed(EventKeyboard::KeyCode::KEY_TAB))
	{
		this->isAddressFocused = true;

		for (auto it = this->addresses.begin(); it != this->addresses.end(); it++)
		{
			(*it)->setOpacity(255);
		}
	}

	if (Input::isKeyJustPressed(EventKeyboard::KeyCode::KEY_SHIFT))
	{
		this->isValueFocused = true;

		for (auto it = this->valueLabels.begin(); it != this->valueLabels.end(); it++)
		{
			(*it)->setOpacity(255);
		}
	}

	if (Input::isKeyJustReleased(EventKeyboard::KeyCode::KEY_TAB))
	{
		this->isAddressFocused = false;
		
		for (auto it = this->addresses.begin(); it != this->addresses.end(); it++)
		{
			(*it)->setOpacity(0);
		}

		MouseEvents::TriggerMouseRefresh(MouseEvents::MouseEventArgs(MouseState::getMouseState()));
	}

	if (Input::isKeyJustReleased(EventKeyboard::KeyCode::KEY_SHIFT))
	{
		this->isValueFocused = false;
		
		for (auto it = this->valueLabels.begin(); it != this->valueLabels.end(); it++)
		{
			(*it)->setOpacity(0);
		}

		MouseEvents::TriggerMouseRefresh(MouseEvents::MouseEventArgs(MouseState::getMouseState()));
	}
}

void MemoryGrid::setInitialState()
{
	this->initialValues = this->values;
	this->initialEax = RegisterState::getRegisterEax();
	this->initialEbx = RegisterState::getRegisterEbx();
	this->initialEcx = RegisterState::getRegisterEcx();
	this->initialEdx = RegisterState::getRegisterEdx();
	this->initialEdi = RegisterState::getRegisterEdi();
	this->initialEsi = RegisterState::getRegisterEsi();
	this->initialEbp = RegisterState::getRegisterEbp();
	this->initialEsp = RegisterState::getRegisterEsp();

	this->buildValueLabels();
}

void MemoryGrid::resetState()
{
	this->values = this->initialValues;

	RegisterState::setRegisterEax(this->initialEax);
	RegisterState::setRegisterEbx(this->initialEbx);
	RegisterState::setRegisterEcx(this->initialEcx);
	RegisterState::setRegisterEdx(this->initialEdx);
	RegisterState::setRegisterEdi(this->initialEdi);
	RegisterState::setRegisterEsi(this->initialEsi);
	RegisterState::setRegisterEbp(this->initialEbp);
	RegisterState::setRegisterEsp(this->initialEsp);

	this->buildValueLabels();
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

void MemoryGrid::buildValueLabels()
{
	for (int x = 0; x < this->gridWidth; x++)
	{
		for (int y = 0; y < this->gridHeight; y++)
		{
			int gridIndex = y + x * this->gridWidth;
			int value = this->values[gridIndex];

			this->valueStrings[gridIndex]->setString(std::to_string(value));
			this->valueLabels[gridIndex]->setTextColor(value == 0 ? Color4B::GRAY : Color4B::WHITE);
		}
	}
}

void MemoryGrid::positionRegisterMarkers()
{
	for (auto it = this->markers.begin(); it != this->markers.end(); it++)
	{
		(*it)->moveToRegister(this);
	}
}

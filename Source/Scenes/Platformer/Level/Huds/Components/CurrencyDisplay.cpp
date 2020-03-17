#include "CurrencyDisplay.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

using namespace cocos2d;

const int CurrencyDisplay::CacheCipher = 0x6942069;

CurrencyDisplay* CurrencyDisplay::create()
{
	CurrencyDisplay* instance = new CurrencyDisplay();

	instance->autorelease();

	return instance;
}

CurrencyDisplay::CurrencyDisplay()
{
	this->emblem = Sprite::create(ItemResources::Collectables_Currency_IOU);
	this->value = ConstantString::create("0");
	this->label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->value);
	this->inventory = nullptr;

	this->emblem->setScale(0.4f);
	this->label->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->label->enableOutline(Color4B::BLACK, 2);

	this->cachedCurrency = (0 ^ CurrencyDisplay::CacheCipher);

	this->addChild(this->emblem);
	this->addChild(this->label);
}

CurrencyDisplay::~CurrencyDisplay()
{
}

void CurrencyDisplay::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CurrencyDisplay::initializePositions()
{
	super::initializePositions();

	this->label->setPosition(Vec2(20.0f, 0.0f));
}

void CurrencyDisplay::initializeListeners()
{
	super::initializeListeners();
}

void CurrencyDisplay::update(float dt)
{
	super::update(dt);

	if (this->inventory == nullptr)
	{
		return;
	}

	int iouCount = this->inventory->getCurrencyCount(IOU::getIOUIdentifier());

	if (iouCount != (this->cachedCurrency ^ CurrencyDisplay::CacheCipher))
	{
		this->cachedCurrency = (iouCount ^ CurrencyDisplay::CacheCipher);

		this->value->setString(std::to_string(iouCount));
	}
}

void CurrencyDisplay::setCurrencyInventory(CurrencyInventory* inventory)
{
	this->value->setString("0");
	this->cachedCurrency = (0 ^ CurrencyDisplay::CacheCipher);
	
	this->inventory = inventory;
}

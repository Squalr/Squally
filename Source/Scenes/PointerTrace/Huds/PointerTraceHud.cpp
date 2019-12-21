#include "PointerTraceHud.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Events/PointerTraceEvents.h"
#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/PointerTraceResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

PointerTraceHud* PointerTraceHud::create()
{
	PointerTraceHud* instance = new PointerTraceHud();

	instance->autorelease();

	return instance;
}

PointerTraceHud::PointerTraceHud()
{
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 196), 160, 334);

	if (sizeof(void*) == 4)
	{
		this->eaxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterEax::create());
		this->ebxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterEbx::create());
		this->ecxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterEcx::create());
		this->edxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterEdx::create());
		this->ediLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterEdi::create());
		this->esiLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterEsi::create());
		this->ebpLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterEbp::create());
		this->espLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterEsp::create());
		this->eipLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterEip::create());
	}
	else
	{
		this->eaxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterRax::create());
		this->ebxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterRbx::create());
		this->ecxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterRcx::create());
		this->edxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterRdx::create());
		this->ediLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterRdi::create());
		this->esiLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterRsi::create());
		this->ebpLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterRbp::create());
		this->espLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterRsp::create());
		this->eipLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, Strings::PointerTrace_Hud_RegisterRip::create());
	}

	this->addressHintLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::PointerTrace_TabHint::create());
	this->valueHintLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::PointerTrace_ShiftHint::create());
	this->movementHelp = Sprite::create(PointerTraceResources::MovementHelp);

	LocalizedLabel* wLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, ConstantString::create("w"));
	LocalizedLabel* aLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, ConstantString::create("a"));
	LocalizedLabel* sLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, ConstantString::create("s"));
	LocalizedLabel* dLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, ConstantString::create("d"));

	this->movementHelp->setVisible(false);

	this->eaxValue = ConstantString::create("0");
	this->ebxValue = ConstantString::create("0");
	this->ecxValue = ConstantString::create("0");
	this->edxValue = ConstantString::create("0");
	this->ediValue = ConstantString::create("0");
	this->esiValue = ConstantString::create("0");
	this->ebpValue = ConstantString::create("0");
	this->espValue = ConstantString::create("0");
	this->eipValue = ConstantString::create("0");

	this->eaxLabel->setStringReplacementVariables(this->eaxValue);
	this->ebxLabel->setStringReplacementVariables(this->ebxValue);
	this->ecxLabel->setStringReplacementVariables(this->ecxValue);
	this->edxLabel->setStringReplacementVariables(this->edxValue);
	this->ediLabel->setStringReplacementVariables(this->ediValue);
	this->esiLabel->setStringReplacementVariables(this->esiValue);
	this->ebpLabel->setStringReplacementVariables(this->ebpValue);
	this->espLabel->setStringReplacementVariables(this->espValue);
	this->eipLabel->setStringReplacementVariables(this->eipValue);

	this->backdrop->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->eaxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->ebxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->ecxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->edxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->ediLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->esiLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->ebpLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->espLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->eipLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->addressHintLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->valueHintLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->eaxLabel->enableOutline(Color4B::BLACK, 2);
	this->ebxLabel->enableOutline(Color4B::BLACK, 2);
	this->ecxLabel->enableOutline(Color4B::BLACK, 2);
	this->edxLabel->enableOutline(Color4B::BLACK, 2);
	this->ediLabel->enableOutline(Color4B::BLACK, 2);
	this->esiLabel->enableOutline(Color4B::BLACK, 2);
	this->ebpLabel->enableOutline(Color4B::BLACK, 2);
	this->espLabel->enableOutline(Color4B::BLACK, 2);
	this->eipLabel->enableOutline(Color4B::BLACK, 2);
	this->addressHintLabel->enableOutline(Color4B::BLACK, 2);
	this->valueHintLabel->enableOutline(Color4B::BLACK, 2);
	wLabel->enableOutline(Color4B::BLACK, 2);
	aLabel->enableOutline(Color4B::BLACK, 2);
	sLabel->enableOutline(Color4B::BLACK, 2);
	dLabel->enableOutline(Color4B::BLACK, 2);

	wLabel->setPosition(Vec2(0.0f, 64.0f));
	aLabel->setPosition(Vec2(-64.0f, 0.0f));
	sLabel->setPosition(Vec2(0.0f, -64.0f));
	dLabel->setPosition(Vec2(64.0f, 0.0f));

	this->movementHelp->addChild(wLabel);
	this->movementHelp->addChild(aLabel);
	this->movementHelp->addChild(sLabel);
	this->movementHelp->addChild(dLabel);
	this->addChild(this->backdrop);
	this->addChild(this->eaxLabel);
	this->addChild(this->ebxLabel);
	this->addChild(this->ecxLabel);
	this->addChild(this->edxLabel);
	this->addChild(this->ediLabel);
	this->addChild(this->esiLabel);
	this->addChild(this->ebpLabel);
	this->addChild(this->espLabel);
	this->addChild(this->eipLabel);
	this->addChild(this->addressHintLabel);
	this->addChild(this->valueHintLabel);
	this->addChild(this->movementHelp);
}

PointerTraceHud::~PointerTraceHud()
{
}

void PointerTraceHud::onEnter()
{
	super::onEnter();
	
	this->updateRegisters();
	this->scheduleUpdate();
}

void PointerTraceHud::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->backdrop->setPosition(8.0f, visibleSize.height - 340.0f);
	this->eaxLabel->setPosition(24.0f, visibleSize.height - 36.0f * 0.0f - 24.0f);
	this->ebxLabel->setPosition(24.0f, visibleSize.height - 36.0f * 1.0f - 24.0f);
	this->ecxLabel->setPosition(24.0f, visibleSize.height - 36.0f * 2.0f - 24.0f);
	this->edxLabel->setPosition(24.0f, visibleSize.height - 36.0f * 3.0f - 24.0f);
	this->ediLabel->setPosition(24.0f, visibleSize.height - 36.0f * 4.0f - 24.0f);
	this->esiLabel->setPosition(24.0f, visibleSize.height - 36.0f * 5.0f - 24.0f);
	this->ebpLabel->setPosition(24.0f, visibleSize.height - 36.0f * 6.0f - 24.0f);
	this->espLabel->setPosition(24.0f, visibleSize.height - 36.0f * 7.0f - 24.0f);
	this->eipLabel->setPosition(24.0f, visibleSize.height - 36.0f * 8.0f - 24.0f);
	this->valueHintLabel->setPosition(24.0f, 0.0f + 36.0f * 0.0f + 24.0f);
	this->addressHintLabel->setPosition(24.0f, 0.0f + 36.0f * 1.0f + 24.0f);
	this->movementHelp->setPosition(visibleSize.width - 320.0f, visibleSize.height - 340.0f);
}

void PointerTraceHud::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(PointerTraceEvents::EventUpdateRegister, [=](EventCustom* eventCustom)
	{
		this->updateRegisters();
	}));
}

void PointerTraceHud::updateRegisters()
{
	this->eaxValue->setString(std::to_string(RegisterState::getRegisterEax()));
	this->ebxValue->setString(std::to_string(RegisterState::getRegisterEbx()));
	this->ecxValue->setString(std::to_string(RegisterState::getRegisterEcx()));
	this->edxValue->setString(std::to_string(RegisterState::getRegisterEdx()));
	this->ediValue->setString(std::to_string(RegisterState::getRegisterEdi()));
	this->esiValue->setString(std::to_string(RegisterState::getRegisterEsi()));
	this->ebpValue->setString(std::to_string(RegisterState::getRegisterEbp()));
	this->espValue->setString(std::to_string(RegisterState::getRegisterEsp()));
	this->eipValue->setString(std::to_string(RegisterState::getRegisterEip()));
}

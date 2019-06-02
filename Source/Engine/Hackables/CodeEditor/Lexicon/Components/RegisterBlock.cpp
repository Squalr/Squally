#include "RegisterBlock.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Registers/RegisterEax.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterEbx.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterEcx.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterEdx.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterEdi.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterEsi.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterEbp.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterEsp.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterEip.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterRax.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterRbx.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterRcx.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterRdx.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterRdi.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterRsi.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterRbp.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterRsp.h"
#include "Strings/Hacking/Lexicon/Registers/RegisterRip.h"

using namespace cocos2d;

RegisterBlock* RegisterBlock::create()
{
    RegisterBlock* instance = new RegisterBlock();

    instance->autorelease();

    return instance;
}

RegisterBlock::RegisterBlock()
{
    this->eax = 0;
    this->ebx = 0;
    this->ecx = 0;
    this->edx = 0;
    this->edi = 0;
    this->esi = 0;
    this->ebp = 0;
    this->esp = 0;
    this->eip = 0;
    this->eaxString = ConstantString::create(std::to_string(this->eax));
    this->ebxString = ConstantString::create(std::to_string(this->ebx));
    this->ecxString = ConstantString::create(std::to_string(this->ecx));
    this->edxString = ConstantString::create(std::to_string(this->edx));
    this->ediString = ConstantString::create(std::to_string(this->edi));
    this->esiString = ConstantString::create(std::to_string(this->esi));
    this->ebpString = ConstantString::create(std::to_string(this->ebp));
    this->espString = ConstantString::create(std::to_string(this->esp));
    this->eipString = ConstantString::create(std::to_string(this->eip));
    this->registerBlock = Sprite::create(UIResources::Menus_LexiconMenu_RegisterBlock);

    if (sizeof(void*) == 4)
    {
        this->eaxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterEax::create());
        this->ebxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterEbx::create());
        this->ecxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterEcx::create());
        this->edxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterEdx::create());
        this->ediLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterEdi::create());
        this->esiLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterEsi::create());
        this->ebpLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterEbp::create());
        this->espLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterEsp::create());
        this->eipLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterEip::create());
    }
    else
    {
        this->eaxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterRax::create());
        this->ebxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterRbx::create());
        this->ecxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterRcx::create());
        this->edxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterRdx::create());
        this->ediLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterRdi::create());
        this->esiLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterRsi::create());
        this->ebpLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterRbp::create());
        this->espLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterRsp::create());
        this->eipLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Hacking_Lexicon_Registers_RegisterRip::create());
    }

    this->eaxLabel->setTextColor(LexiconPage::TextColor);
    this->ebxLabel->setTextColor(LexiconPage::TextColor);
    this->ecxLabel->setTextColor(LexiconPage::TextColor);
    this->edxLabel->setTextColor(LexiconPage::TextColor);
    this->ediLabel->setTextColor(LexiconPage::TextColor);
    this->esiLabel->setTextColor(LexiconPage::TextColor);
    this->ebpLabel->setTextColor(LexiconPage::TextColor);
    this->espLabel->setTextColor(LexiconPage::TextColor);
    this->eipLabel->setTextColor(LexiconPage::TextColor);

    this->eaxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->ebxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->ecxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->edxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->ediLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->esiLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->ebpLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->espLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->eipLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

    this->eaxLabel->setStringReplacementVariables(this->eaxString);
    this->ebxLabel->setStringReplacementVariables(this->ebxString);
    this->ecxLabel->setStringReplacementVariables(this->ecxString);
    this->edxLabel->setStringReplacementVariables(this->edxString);
    this->ediLabel->setStringReplacementVariables(this->ediString);
    this->esiLabel->setStringReplacementVariables(this->esiString);
    this->ebpLabel->setStringReplacementVariables(this->ebpString);
    this->espLabel->setStringReplacementVariables(this->espString);
    this->eipLabel->setStringReplacementVariables(this->eipString);
    
    this->addChild(this->registerBlock);
    this->addChild(this->eaxLabel);
    this->addChild(this->ebxLabel);
    this->addChild(this->ecxLabel);
    this->addChild(this->edxLabel);
    this->addChild(this->ediLabel);
    this->addChild(this->esiLabel);
    this->addChild(this->ebpLabel);
    this->addChild(this->espLabel);
    this->addChild(this->eipLabel);
}

RegisterBlock::~RegisterBlock()
{
}

void RegisterBlock::onEnter()
{
    super::onEnter();
}

void RegisterBlock::initializePositions()
{
	super::initializePositions();

    const float Spacing = 28.0f;
    const float Offset = (Spacing * 8.0f) / 2.0f;

	this->eaxLabel->setPosition(Vec2(-72.0f, Offset - Spacing * 0.0f));
	this->ebxLabel->setPosition(Vec2(-72.0f, Offset - Spacing * 1.0f));
	this->ecxLabel->setPosition(Vec2(-72.0f, Offset - Spacing * 2.0f));
	this->edxLabel->setPosition(Vec2(-72.0f, Offset - Spacing * 3.0f));
	this->ediLabel->setPosition(Vec2(-72.0f, Offset - Spacing * 4.0f));
	this->esiLabel->setPosition(Vec2(-72.0f, Offset - Spacing * 5.0f));
	this->ebpLabel->setPosition(Vec2(-72.0f, Offset - Spacing * 6.0f));
	this->espLabel->setPosition(Vec2(-72.0f, Offset - Spacing * 7.0f));
	this->eipLabel->setPosition(Vec2(-72.0f, Offset - Spacing * 8.0f));
}

void RegisterBlock::initializeListeners()
{
    super::initializeListeners();
}

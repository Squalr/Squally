#include "RegisterBlockSigned.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float RegisterBlockSigned::RegisterPtrSpacing  = -32.0f;
const Vec2 RegisterBlockSigned::SelectorRegOffset = Vec2(-20.0f, 0.0f);

RegisterBlockSigned* RegisterBlockSigned::create()
{
    RegisterBlockSigned* instance = new RegisterBlockSigned();

    instance->autorelease();

    return instance;
}

RegisterBlockSigned::RegisterBlockSigned()
{
    this->eax = Register();
    this->ebx = Register();
    this->ecx = Register();
    this->edx = Register();
    this->edi = Register();
    this->esi = Register();
    this->ebp = Register();
    this->esp = Register();
    this->eip = Register();
	this->eaxPtrLabels = std::vector<LocalizedLabel*>();
	this->ebxPtrLabels = std::vector<LocalizedLabel*>();
	this->ecxPtrLabels = std::vector<LocalizedLabel*>();
	this->edxPtrLabels = std::vector<LocalizedLabel*>();
	this->ediPtrLabels = std::vector<LocalizedLabel*>();
	this->esiPtrLabels = std::vector<LocalizedLabel*>();
	this->ebpPtrLabels = std::vector<LocalizedLabel*>();
	this->espPtrLabels = std::vector<LocalizedLabel*>();
	this->eipPtrLabels = std::vector<LocalizedLabel*>();
	this->eaxPtrStrings = std::vector<ConstantString*>();
	this->ebxPtrStrings = std::vector<ConstantString*>();
	this->ecxPtrStrings = std::vector<ConstantString*>();
	this->edxPtrStrings = std::vector<ConstantString*>();
	this->ediPtrStrings = std::vector<ConstantString*>();
	this->esiPtrStrings = std::vector<ConstantString*>();
	this->ebpPtrStrings = std::vector<ConstantString*>();
	this->espPtrStrings = std::vector<ConstantString*>();
	this->eipPtrStrings = std::vector<ConstantString*>();
    this->eaxString = ConstantString::create(std::to_string(this->eax.currentValue));
    this->ebxString = ConstantString::create(std::to_string(this->ebx.currentValue));
    this->ecxString = ConstantString::create(std::to_string(this->ecx.currentValue));
    this->edxString = ConstantString::create(std::to_string(this->edx.currentValue));
    this->ediString = ConstantString::create(std::to_string(this->edi.currentValue));
    this->esiString = ConstantString::create(std::to_string(this->esi.currentValue));
    this->ebpString = ConstantString::create(std::to_string(this->ebp.currentValue));
    this->espString = ConstantString::create(std::to_string(this->esp.currentValue));
    this->eipString = ConstantString::create(std::to_string(this->eip.currentValue));
    this->registerBlock = Sprite::create(UIResources::Menus_LexiconMenu_RegisterBlock);
    this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Hacking_Lexicon_Registers::create());
    this->memoryTitleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Hacking_Lexicon_Memory::create());

    if (sizeof(void*) == 4)
    {
        this->eaxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterEax::create());
        this->ebxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterEbx::create());
        this->ecxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterEcx::create());
        this->edxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterEdx::create());
        this->ediLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterEdi::create());
        this->esiLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterEsi::create());
        this->ebpLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterEbp::create());
        this->espLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterEsp::create());
        this->eipLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterEip::create());
    }
    else
    {
        this->eaxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterRax::create());
        this->ebxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterRbx::create());
        this->ecxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterRcx::create());
        this->edxLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterRdx::create());
        this->ediLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterRdi::create());
        this->esiLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterRsi::create());
        this->ebpLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterRbp::create());
        this->espLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterRsp::create());
        this->eipLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Registers_RegisterRip::create());
    }
	this->eaxPtrNode = Node::create();
	this->ebxPtrNode = Node::create();
	this->ecxPtrNode = Node::create();
	this->edxPtrNode = Node::create();
	this->ediPtrNode = Node::create();
	this->esiPtrNode = Node::create();
	this->ebpPtrNode = Node::create();
	this->espPtrNode = Node::create();
	this->eipPtrNode = Node::create();
    this->srcSelector = Sprite::create(UIResources::Menus_LexiconMenu_SourceSelector);
    this->destSelector = Sprite::create(UIResources::Menus_LexiconMenu_DestSelector);
    
    this->titleLabel->setTextColor(LexiconPage::TextColor);
    this->memoryTitleLabel->setTextColor(LexiconPage::TextColor);
    this->eaxLabel->setTextColor(LexiconPage::TextColor);
    this->ebxLabel->setTextColor(LexiconPage::TextColor);
    this->ecxLabel->setTextColor(LexiconPage::TextColor);
    this->edxLabel->setTextColor(LexiconPage::TextColor);
    this->ediLabel->setTextColor(LexiconPage::TextColor);
    this->esiLabel->setTextColor(LexiconPage::TextColor);
    this->ebpLabel->setTextColor(LexiconPage::TextColor);
    this->espLabel->setTextColor(LexiconPage::TextColor);
    this->eipLabel->setTextColor(LexiconPage::TextColor);

    this->titleLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->memoryTitleLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->eaxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->ebxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->ecxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->edxLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->ediLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->esiLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->ebpLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->espLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->eipLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->srcSelector->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->destSelector->setAnchorPoint(Vec2(0.0f, 0.5f));

    this->eaxLabel->setStringReplacementVariables(this->eaxString);
    this->ebxLabel->setStringReplacementVariables(this->ebxString);
    this->ecxLabel->setStringReplacementVariables(this->ecxString);
    this->edxLabel->setStringReplacementVariables(this->edxString);
    this->ediLabel->setStringReplacementVariables(this->ediString);
    this->esiLabel->setStringReplacementVariables(this->esiString);
    this->ebpLabel->setStringReplacementVariables(this->ebpString);
    this->espLabel->setStringReplacementVariables(this->espString);
    this->eipLabel->setStringReplacementVariables(this->eipString);

    this->srcSelector->setOpacity(0);
    this->destSelector->setOpacity(0);
    
    this->addChild(this->registerBlock);
    this->addChild(this->titleLabel);
    this->addChild(this->memoryTitleLabel);
    this->addChild(this->eaxLabel);
    this->addChild(this->ebxLabel);
    this->addChild(this->ecxLabel);
    this->addChild(this->edxLabel);
    this->addChild(this->ediLabel);
    this->addChild(this->esiLabel);
    this->addChild(this->ebpLabel);
    this->addChild(this->espLabel);
    this->addChild(this->eipLabel);
    this->addChild(this->eaxPtrNode);
    this->addChild(this->ebxPtrNode);
    this->addChild(this->ecxPtrNode);
    this->addChild(this->edxPtrNode);
    this->addChild(this->ediPtrNode);
    this->addChild(this->esiPtrNode);
    this->addChild(this->ebpPtrNode);
    this->addChild(this->espPtrNode);
    this->addChild(this->eipPtrNode);
    this->addChild(this->srcSelector);
    this->addChild(this->destSelector);
}

RegisterBlockSigned::~RegisterBlockSigned()
{
}

void RegisterBlockSigned::onEnter()
{
    super::onEnter();
}

void RegisterBlockSigned::initializePositions()
{
	super::initializePositions();

    const float Spacing = 28.0f;
    const float Offset = (Spacing * 8.0f) / 2.0f;

	this->titleLabel->setPosition(Vec2(-88.0f - 12.0f, Offset + 48.0f));
	this->memoryTitleLabel->setPosition(Vec2(232.0f - 12.0f, Offset + 48.0f));
	this->eaxLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 0.0f));
	this->ebxLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 1.0f));
	this->ecxLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 2.0f));
	this->edxLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 3.0f));
	this->ediLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 4.0f));
	this->esiLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 5.0f));
	this->ebpLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 6.0f));
	this->espLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 7.0f));
	this->eipLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 8.0f));

	this->eaxPtrNode->setPosition(Vec2(208.0f, Offset - Spacing * 0.0f));
	this->ebxPtrNode->setPosition(Vec2(208.0f, Offset - Spacing * 1.0f));
	this->ecxPtrNode->setPosition(Vec2(208.0f, Offset - Spacing * 2.0f));
	this->edxPtrNode->setPosition(Vec2(208.0f, Offset - Spacing * 3.0f));
	this->ediPtrNode->setPosition(Vec2(208.0f, Offset - Spacing * 4.0f));
	this->esiPtrNode->setPosition(Vec2(208.0f, Offset - Spacing * 5.0f));
	this->ebpPtrNode->setPosition(Vec2(208.0f, Offset - Spacing * 6.0f));
	this->espPtrNode->setPosition(Vec2(208.0f, Offset - Spacing * 7.0f));
	this->eipPtrNode->setPosition(Vec2(208.0f, Offset - Spacing * 8.0f));
}

void RegisterBlockSigned::initializeListeners()
{
    super::initializeListeners();
}

void RegisterBlockSigned::clearHighlights()
{
    this->srcSelector->setOpacity(0);
    this->destSelector->setOpacity(0);
}

void RegisterBlockSigned::highlightSource(Vec2 position)
{
    this->srcSelector->setOpacity(255);
    this->srcSelector->setPosition(position);
}

void RegisterBlockSigned::highlightDest(Vec2 position)
{
    this->destSelector->setOpacity(255);
    this->destSelector->setPosition(position);
}

void RegisterBlockSigned::highlightEax(bool isDest)
{
    if (!isDest)
    {
        this->highlightSource(this->eaxLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
    else
    {
        this->highlightDest(this->eaxLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
}

void RegisterBlockSigned::highlightEbx(bool isDest)
{
    if (!isDest)
    {
        this->highlightSource(this->ebxLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
    else
    {
        this->highlightDest(this->ebxLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
}

void RegisterBlockSigned::highlightEcx(bool isDest)
{
    if (!isDest)
    {
        this->highlightSource(this->ecxLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
    else
    {
        this->highlightDest(this->ecxLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
}

void RegisterBlockSigned::highlightEdx(bool isDest)
{
    if (!isDest)
    {
        this->highlightSource(this->edxLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
    else
    {
        this->highlightDest(this->edxLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
}

void RegisterBlockSigned::highlightEdi(bool isDest)
{
    if (!isDest)
    {
        this->highlightSource(this->ediLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
    else
    {
        this->highlightDest(this->ediLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
}

void RegisterBlockSigned::highlightEsi(bool isDest)
{
    if (!isDest)
    {
        this->highlightSource(this->esiLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
    else
    {
        this->highlightDest(this->esiLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
}

void RegisterBlockSigned::highlightEbp(bool isDest)
{
    if (!isDest)
    {
        this->highlightSource(this->ebpLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
    else
    {
        this->highlightDest(this->ebpLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
}

void RegisterBlockSigned::highlightEsp(bool isDest)
{
    if (!isDest)
    {
        this->highlightSource(this->espLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
    else
    {
        this->highlightDest(this->espLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
}

void RegisterBlockSigned::highlightEip(bool isDest)
{
    if (!isDest)
    {
        this->highlightSource(this->eipLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
    else
    {
        this->highlightDest(this->eipLabel->getPosition() + RegisterBlockSigned::SelectorRegOffset);
    }
}

void RegisterBlockSigned::highlightEaxPtr(bool isDest, int offset)
{
    if (!isDest)
    {
        this->highlightSource(this->eaxPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
    else
    {
        this->highlightDest(this->eaxPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
}

void RegisterBlockSigned::highlightEbxPtr(bool isDest, int offset)
{
    if (!isDest)
    {
        this->highlightSource(this->ebxPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
    else
    {
        this->highlightDest(this->ebxPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
}

void RegisterBlockSigned::highlightEcxPtr(bool isDest, int offset)
{
    if (!isDest)
    {
        this->highlightSource(this->ecxPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
    else
    {
        this->highlightDest(this->ecxPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
}

void RegisterBlockSigned::highlightEdxPtr(bool isDest, int offset)
{
    if (!isDest)
    {
        this->highlightSource(this->edxPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
    else
    {
        this->highlightDest(this->edxPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
}

void RegisterBlockSigned::highlightEdiPtr(bool isDest, int offset)
{
    if (!isDest)
    {
        this->highlightSource(this->ediPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
    else
    {
        this->highlightDest(this->ediPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
}

void RegisterBlockSigned::highlightEsiPtr(bool isDest, int offset)
{
    if (!isDest)
    {
        this->highlightSource(this->esiPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
    else
    {
        this->highlightDest(this->esiPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
}

void RegisterBlockSigned::highlightEbpPtr(bool isDest, int offset)
{
    if (!isDest)
    {
        this->highlightSource(this->ebpPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
    else
    {
        this->highlightDest(this->ebpPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
}

void RegisterBlockSigned::highlightEspPtr(bool isDest, int offset)
{
    if (!isDest)
    {
        this->highlightSource(this->espPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
    else
    {
        this->highlightDest(this->espPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
}

void RegisterBlockSigned::highlightEipPtr(bool isDest, int offset)
{
    if (!isDest)
    {
        this->highlightSource(this->eipPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
    else
    {
        this->highlightDest(this->eipPtrNode->getPosition() + Vec2(0.0f, float(offset) * RegisterBlockSigned::RegisterPtrSpacing));
    }
}

void RegisterBlockSigned::initEax(long long eax, std::vector<long long> values)
{
    if (!this->eax.initialized)
    {
        this->eax = Register(eax, eax, values, values);
        
        for (int index = 0; index < int(values.size()); index++)
        {
            this->addToData(values[index], index, this->eaxPtrNode, &this->eaxPtrStrings, &this->eaxPtrLabels);
        }
    }

    this->setEax(eax);

    for (int index = 0; index < int(values.size()); index++)
    {
        this->setEaxPtr(values[index], index);
    }
}

void RegisterBlockSigned::initEbx(long long ebx, std::vector<long long> values)
{
    if (!this->ebx.initialized)
    {
        this->ebx = Register(ebx, ebx, values, values);
        
        for (int index = 0; index < int(values.size()); index++)
        {
            this->addToData(values[index], index, this->ebxPtrNode, &this->ebxPtrStrings, &this->ebxPtrLabels);
        }
    }

    this->setEbx(ebx);

    for (int index = 0; index < int(values.size()); index++)
    {
        this->setEbxPtr(values[index], index);
    }
}

void RegisterBlockSigned::initEcx(long long ecx, std::vector<long long> values)
{
    if (!this->ecx.initialized)
    {
        this->ecx = Register(ecx, ecx, values, values);
        
        for (int index = 0; index < int(values.size()); index++)
        {
            this->addToData(values[index], index, this->ecxPtrNode, &this->ecxPtrStrings, &this->ecxPtrLabels);
        }
    }

    this->setEcx(ecx);

    for (int index = 0; index < int(values.size()); index++)
    {
        this->setEcxPtr(values[index], index);
    }
}

void RegisterBlockSigned::initEdx(long long edx, std::vector<long long> values)
{
    if (!this->edx.initialized)
    {
        this->edx = Register(edx, edx, values, values);
        
        for (int index = 0; index < int(values.size()); index++)
        {
            this->addToData(values[index], index, this->edxPtrNode, &this->edxPtrStrings, &this->edxPtrLabels);
        }
    }

    this->setEdx(edx);

    for (int index = 0; index < int(values.size()); index++)
    {
        this->setEdxPtr(values[index], index);
    }
}

void RegisterBlockSigned::initEdi(long long edi, std::vector<long long> values)
{
    if (!this->edi.initialized)
    {
        this->edi = Register(edi, edi, values, values);
        
        for (int index = 0; index < int(values.size()); index++)
        {
            this->addToData(values[index], index, this->ediPtrNode, &this->ediPtrStrings, &this->ediPtrLabels);
        }
    }

    this->setEdi(edi);

    for (int index = 0; index < int(values.size()); index++)
    {
        this->setEdiPtr(values[index], index);
    }
}

void RegisterBlockSigned::initEsi(long long esi, std::vector<long long> values)
{
    if (!this->esi.initialized)
    {
        this->esi = Register(esi, esi, values, values);
        
        for (int index = 0; index < int(values.size()); index++)
        {
            this->addToData(values[index], index, this->esiPtrNode, &this->esiPtrStrings, &this->esiPtrLabels);
        }
    }

    this->setEsi(esi);

    for (int index = 0; index < int(values.size()); index++)
    {
        this->setEsiPtr(values[index], index);
    }
}

void RegisterBlockSigned::initEbp(long long ebp, std::vector<long long> values)
{
    if (!this->ebp.initialized)
    {
        this->ebp = Register(ebp, ebp, values, values);
        
        for (int index = 0; index < int(values.size()); index++)
        {
            this->addToData(values[index], index, this->ebpPtrNode, &this->ebpPtrStrings, &this->ebpPtrLabels);
        }
    }

    this->setEbp(ebp);

    for (int index = 0; index < int(values.size()); index++)
    {
        this->setEbpPtr(values[index], index);
    }
}

void RegisterBlockSigned::initEsp(long long esp, std::vector<long long> values)
{
    if (!this->esp.initialized)
    {
        this->esp = Register(esp, esp, values, values);
        
        for (int index = 0; index < int(values.size()); index++)
        {
            this->addToData(values[index], index, this->espPtrNode, &this->espPtrStrings, &this->espPtrLabels);
        }
    }

    this->setEsp(esp);

    for (int index = 0; index < int(values.size()); index++)
    {
        this->setEspPtr(values[index], index);
    }
}

void RegisterBlockSigned::initEip(long long eip, std::vector<long long> values)
{
    if (!this->eip.initialized)
    {
        this->eip = Register(eip, eip, values, values);
        
        for (int index = 0; index < int(values.size()); index++)
        {
            this->addToData(values[index], index, this->eipPtrNode, &this->eipPtrStrings, &this->eipPtrLabels);
        }
    }

    this->setEip(eip);

    for (int index = 0; index < int(values.size()); index++)
    {
        this->setEipPtr(values[index], index);
    }
}

void RegisterBlockSigned::setEaxPtr(long long value, int offset)
{
    this->eax.currentValues[offset] = value;
    this->eaxPtrStrings[offset]->setString(std::to_string(this->eax.currentValues[offset]));
    this->eaxPtrLabels[offset]->setTextColor((this->eax.currentValues[offset] == this->eax.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEbxPtr(long long value, int offset)
{
    this->ebx.currentValues[offset] = value;
    this->ebxPtrStrings[offset]->setString(std::to_string(this->ebx.currentValues[offset]));
    this->ebxPtrLabels[offset]->setTextColor((this->ebx.currentValues[offset] == this->ebx.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEcxPtr(long long value, int offset)
{
    this->ecx.currentValues[offset] = value;
    this->ecxPtrStrings[offset]->setString(std::to_string(this->ecx.currentValues[offset]));
    this->ecxPtrLabels[offset]->setTextColor((this->ecx.currentValues[offset] == this->ecx.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEdxPtr(long long value, int offset)
{
    this->edx.currentValues[offset] = value;
    this->edxPtrStrings[offset]->setString(std::to_string(this->edx.currentValues[offset]));
    this->edxPtrLabels[offset]->setTextColor((this->edx.currentValues[offset] == this->edx.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEdiPtr(long long value, int offset)
{
    this->edi.currentValues[offset] = value;
    this->ediPtrStrings[offset]->setString(std::to_string(this->edi.currentValues[offset]));
    this->ediPtrLabels[offset]->setTextColor((this->edi.currentValues[offset] == this->edi.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEsiPtr(long long value, int offset)
{
    this->esi.currentValues[offset] = value;
    this->esiPtrStrings[offset]->setString(std::to_string(this->esi.currentValues[offset]));
    this->esiPtrLabels[offset]->setTextColor((this->esi.currentValues[offset] == this->esi.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEbpPtr(long long value, int offset)
{
    this->ebp.currentValues[offset] = value;
    this->ebpPtrStrings[offset]->setString(std::to_string(this->ebp.currentValues[offset]));
    this->ebpPtrLabels[offset]->setTextColor((this->ebp.currentValues[offset] == this->ebp.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEspPtr(long long value, int offset)
{
    this->esp.currentValues[offset] = value;
    this->espPtrStrings[offset]->setString(std::to_string(this->esp.currentValues[offset]));
    this->espPtrLabels[offset]->setTextColor((this->esp.currentValues[offset] == this->esp.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEipPtr(long long value, int offset)
{
    this->eip.currentValues[offset] = value;
    this->eipPtrStrings[offset]->setString(std::to_string(this->eip.currentValues[offset]));
    this->eipPtrLabels[offset]->setTextColor((this->eip.currentValues[offset] == this->eip.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEax(long long eax)
{
    this->eax.currentValue = eax;
    this->eaxString->setString(std::to_string(this->eax.currentValue));
    this->eaxLabel->setTextColor((this->eax.currentValue == this->eax.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEbx(long long ebx)
{
    this->ebx.currentValue = ebx;
    this->ebxString->setString(std::to_string(this->ebx.currentValue));
    this->ebxLabel->setTextColor((this->ebx.currentValue == this->ebx.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEcx(long long ecx)
{
    this->ecx.currentValue = ecx;
    this->ecxString->setString(std::to_string(this->ecx.currentValue));
    this->ecxLabel->setTextColor((this->ecx.currentValue == this->ecx.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEdx(long long edx)
{
    this->edx.currentValue = edx;
    this->edxString->setString(std::to_string(this->edx.currentValue));
    this->edxLabel->setTextColor((this->edx.currentValue == this->edx.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEdi(long long edi)
{
    this->edi.currentValue = edi;
    this->ediString->setString(std::to_string(this->edi.currentValue));
    this->ediLabel->setTextColor((this->edi.currentValue == this->edi.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEsi(long long esi)
{
    this->esi.currentValue = esi;
    this->esiString->setString(std::to_string(this->esi.currentValue));
    this->esiLabel->setTextColor((this->esi.currentValue == this->esi.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEbp(long long ebp)
{
    this->ebp.currentValue = ebp;
    this->ebpString->setString(std::to_string(this->ebp.currentValue));
    this->ebpLabel->setTextColor((this->ebp.currentValue == this->ebp.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEsp(long long esp)
{
    this->esp.currentValue = esp;
    this->espString->setString(std::to_string(this->esp.currentValue));
    this->espLabel->setTextColor((this->esp.currentValue == this->esp.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlockSigned::setEip(long long eip)
{
    this->eip.currentValue = eip;
    this->eipString->setString(std::to_string(this->eip.currentValue));
    this->eipLabel->setTextColor((this->eip.currentValue == this->eip.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

long long RegisterBlockSigned::getEax()
{
    return this->eax.currentValue;
}

long long RegisterBlockSigned::getEbx()
{
    return this->ebx.currentValue;
}

long long RegisterBlockSigned::getEcx()
{
    return this->ecx.currentValue;
}

long long RegisterBlockSigned::getEdx()
{
    return this->edx.currentValue;
}

long long RegisterBlockSigned::getEdi()
{
    return this->edi.currentValue;
}

long long RegisterBlockSigned::getEsi()
{
    return this->esi.currentValue;
}

long long RegisterBlockSigned::getEbp()
{
    return this->ebp.currentValue;
}

long long RegisterBlockSigned::getEsp()
{
    return this->esp.currentValue;
}

long long RegisterBlockSigned::getEip()
{
    return this->eip.currentValue;
}

long long RegisterBlockSigned::getEaxPtr(int offset)
{
    return this->eax.currentValues[offset];
}

long long RegisterBlockSigned::getEbxPtr(int offset)
{
    return this->ebx.currentValues[offset];
}

long long RegisterBlockSigned::getEcxPtr(int offset)
{
    return this->ecx.currentValues[offset];
}

long long RegisterBlockSigned::getEdxPtr(int offset)
{
    return this->edx.currentValues[offset];
}

long long RegisterBlockSigned::getEdiPtr(int offset)
{
    return this->edi.currentValues[offset];
}

long long RegisterBlockSigned::getEsiPtr(int offset)
{
    return this->esi.currentValues[offset];
}

long long RegisterBlockSigned::getEbpPtr(int offset)
{
    return this->ebp.currentValues[offset];
}

long long RegisterBlockSigned::getEspPtr(int offset)
{
    return this->esp.currentValues[offset];
}

long long RegisterBlockSigned::getEipPtr(int offset)
{
    return this->eip.currentValues[offset];
}

void RegisterBlockSigned::addToData(long long value, int index, Node* node, std::vector<ConstantString*>* strings, std::vector<LocalizedLabel*>* labels)
{
    ConstantString* str = ConstantString::create(std::to_string(value));
    LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, str);
    Sprite* frame = Sprite::create(UIResources::Menus_LexiconMenu_DataFrame);

    if (index == 0)
    {
        Sprite* arrow = Sprite::create(UIResources::Menus_LexiconMenu_Arrow);

        arrow->setPosition(Vec2(-124.0f, RegisterBlockSigned::RegisterPtrSpacing * index));
        arrow->setAnchorPoint(Vec2(0.0f, 0.5f));
        
        node->addChild(arrow);
    }

    label->setPosition(Vec2(8.0f, RegisterBlockSigned::RegisterPtrSpacing * index));
    frame->setPosition(Vec2(0.0f, RegisterBlockSigned::RegisterPtrSpacing * index));
    label->setAnchorPoint(Vec2(0.0f, 0.5f));
    frame->setAnchorPoint(Vec2(0.0f, 0.5f));

    node->addChild(frame);
    node->addChild(label);
    strings->push_back(str);
    labels->push_back(label);
}

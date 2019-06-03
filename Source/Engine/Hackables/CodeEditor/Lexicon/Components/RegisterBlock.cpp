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

#include "Strings/Hacking/Lexicon/Registers.h"
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

const float RegisterBlock::RegisterPtrSpacing  = -28.0f;

RegisterBlock* RegisterBlock::create()
{
    RegisterBlock* instance = new RegisterBlock();

    instance->autorelease();

    return instance;
}

RegisterBlock::RegisterBlock()
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
    this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_Lexicon_Registers::create());

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
	this->eaxPtrNode = Node::create();
	this->ebxPtrNode = Node::create();
	this->ecxPtrNode = Node::create();
	this->edxPtrNode = Node::create();
	this->ediPtrNode = Node::create();
	this->esiPtrNode = Node::create();
	this->ebpPtrNode = Node::create();
	this->espPtrNode = Node::create();
	this->eipPtrNode = Node::create();

    this->titleLabel->setTextColor(LexiconPage::TextColor);
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
    this->addChild(this->titleLabel);
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

	this->titleLabel->setPosition(Vec2(-88.0f - 12.0f, Offset + 48.0f));
	this->eaxLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 0.0f));
	this->ebxLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 1.0f));
	this->ecxLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 2.0f));
	this->edxLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 3.0f));
	this->ediLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 4.0f));
	this->esiLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 5.0f));
	this->ebpLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 6.0f));
	this->espLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 7.0f));
	this->eipLabel->setPosition(Vec2(-88.0f, Offset - Spacing * 8.0f));

	this->eaxPtrNode->setPosition(Vec2(128.0f, Offset - Spacing * 0.0f));
	this->ebxPtrNode->setPosition(Vec2(128.0f, Offset - Spacing * 1.0f));
	this->ecxPtrNode->setPosition(Vec2(128.0f, Offset - Spacing * 2.0f));
	this->edxPtrNode->setPosition(Vec2(128.0f, Offset - Spacing * 3.0f));
	this->ediPtrNode->setPosition(Vec2(128.0f, Offset - Spacing * 4.0f));
	this->esiPtrNode->setPosition(Vec2(128.0f, Offset - Spacing * 5.0f));
	this->ebpPtrNode->setPosition(Vec2(128.0f, Offset - Spacing * 6.0f));
	this->espPtrNode->setPosition(Vec2(128.0f, Offset - Spacing * 7.0f));
	this->eipPtrNode->setPosition(Vec2(128.0f, Offset - Spacing * 8.0f));
}

void RegisterBlock::initializeListeners()
{
    super::initializeListeners();
}

void RegisterBlock::initEax(unsigned long eax, std::vector<unsigned long> values)
{
    if (!this->eax.initialized)
    {
        this->eax = Register(eax, eax, values, values);
        
        for (int index = 0; index < values.size(); index++)
        {
            ConstantString* str = ConstantString::create(std::to_string(values[index]));
            LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, str);

            label->setPosition(Vec2(0.0f, RegisterBlock::RegisterPtrSpacing  * index));

            this->eaxPtrNode->addChild(label);
            this->eaxPtrStrings.push_back(str);
            this->eaxPtrLabels.push_back(label);
        }
    }

    this->setEax(eax);

    for (int index = 0; index < values.size(); index++)
    {
        this->setEaxPtr(values[index], index);
    }
}

void RegisterBlock::initEbx(unsigned long ebx, std::vector<unsigned long> values)
{
    if (!this->ebx.initialized)
    {
        this->ebx = Register(ebx, ebx, values, values);
        
        for (int index = 0; index < values.size(); index++)
        {
            ConstantString* str = ConstantString::create(std::to_string(values[index]));
            LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, str);

            label->setPosition(Vec2(0.0f, RegisterBlock::RegisterPtrSpacing  * index));

            this->ebxPtrNode->addChild(label);
            this->ebxPtrStrings.push_back(str);
            this->ebxPtrLabels.push_back(label);
        }
    }

    this->setEbx(ebx);

    for (int index = 0; index < values.size(); index++)
    {
        this->setEbxPtr(values[index], index);
    }
}

void RegisterBlock::initEcx(unsigned long ecx, std::vector<unsigned long> values)
{
    if (!this->ecx.initialized)
    {
        this->ecx = Register(ecx, ecx, values, values);
        
        for (int index = 0; index < values.size(); index++)
        {
            ConstantString* str = ConstantString::create(std::to_string(values[index]));
            LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, str);

            label->setPosition(Vec2(0.0f, RegisterBlock::RegisterPtrSpacing  * index));

            this->ecxPtrNode->addChild(label);
            this->ecxPtrStrings.push_back(str);
            this->ecxPtrLabels.push_back(label);
        }
    }

    this->setEcx(ecx);

    for (int index = 0; index < values.size(); index++)
    {
        this->setEcxPtr(values[index], index);
    }
}

void RegisterBlock::initEdx(unsigned long edx, std::vector<unsigned long> values)
{
    if (!this->edx.initialized)
    {
        this->edx = Register(edx, edx, values, values);
        
        for (int index = 0; index < values.size(); index++)
        {
            ConstantString* str = ConstantString::create(std::to_string(values[index]));
            LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, str);

            label->setPosition(Vec2(0.0f, RegisterBlock::RegisterPtrSpacing  * index));

            this->edxPtrNode->addChild(label);
            this->edxPtrStrings.push_back(str);
            this->edxPtrLabels.push_back(label);
        }
    }

    this->setEdx(edx);

    for (int index = 0; index < values.size(); index++)
    {
        this->setEdxPtr(values[index], index);
    }
}

void RegisterBlock::initEdi(unsigned long edi, std::vector<unsigned long> values)
{
    if (!this->edi.initialized)
    {
        this->edi = Register(edi, edi, values, values);
        
        for (int index = 0; index < values.size(); index++)
        {
            ConstantString* str = ConstantString::create(std::to_string(values[index]));
            LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, str);

            label->setPosition(Vec2(0.0f, RegisterBlock::RegisterPtrSpacing  * index));

            this->ediPtrNode->addChild(label);
            this->ediPtrStrings.push_back(str);
            this->ediPtrLabels.push_back(label);
        }
    }

    this->setEdi(edi);

    for (int index = 0; index < values.size(); index++)
    {
        this->setEdiPtr(values[index], index);
    }
}

void RegisterBlock::initEsi(unsigned long esi, std::vector<unsigned long> values)
{
    if (!this->esi.initialized)
    {
        this->esi = Register(esi, esi, values, values);
        
        for (int index = 0; index < values.size(); index++)
        {
            ConstantString* str = ConstantString::create(std::to_string(values[index]));
            LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, str);

            label->setPosition(Vec2(0.0f, RegisterBlock::RegisterPtrSpacing  * index));

            this->esiPtrNode->addChild(label);
            this->esiPtrStrings.push_back(str);
            this->esiPtrLabels.push_back(label);
        }
    }

    this->setEsi(esi);

    for (int index = 0; index < values.size(); index++)
    {
        this->setEsiPtr(values[index], index);
    }
}

void RegisterBlock::initEbp(unsigned long ebp, std::vector<unsigned long> values)
{
    if (!this->ebp.initialized)
    {
        this->ebp = Register(ebp, ebp, values, values);
        
        for (int index = 0; index < values.size(); index++)
        {
            ConstantString* str = ConstantString::create(std::to_string(values[index]));
            LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, str);

            label->setPosition(Vec2(0.0f, RegisterBlock::RegisterPtrSpacing  * index));

            this->ebpPtrNode->addChild(label);
            this->ebpPtrStrings.push_back(str);
            this->ebpPtrLabels.push_back(label);
        }
    }

    this->setEbp(ebp);

    for (int index = 0; index < values.size(); index++)
    {
        this->setEbpPtr(values[index], index);
    }
}

void RegisterBlock::initEsp(unsigned long esp, std::vector<unsigned long> values)
{
    if (!this->esp.initialized)
    {
        this->esp = Register(esp, esp, values, values);
        
        for (int index = 0; index < values.size(); index++)
        {
            ConstantString* str = ConstantString::create(std::to_string(values[index]));
            LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, str);

            label->setPosition(Vec2(0.0f, RegisterBlock::RegisterPtrSpacing  * index));

            this->espPtrNode->addChild(label);
            this->espPtrStrings.push_back(str);
            this->espPtrLabels.push_back(label);
        }
    }

    this->setEsp(esp);

    for (int index = 0; index < values.size(); index++)
    {
        this->setEspPtr(values[index], index);
    }
}

void RegisterBlock::initEip(unsigned long eip, std::vector<unsigned long> values)
{
    if (!this->eip.initialized)
    {
        this->eip = Register(eip, eip, values, values);
        
        for (int index = 0; index < values.size(); index++)
        {
            ConstantString* str = ConstantString::create(std::to_string(values[index]));
            LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, str);

            label->setPosition(Vec2(0.0f, RegisterBlock::RegisterPtrSpacing  * index));

            this->eipPtrNode->addChild(label);
            this->eipPtrStrings.push_back(str);
            this->eipPtrLabels.push_back(label);
        }
    }

    this->setEip(eip);

    for (int index = 0; index < values.size(); index++)
    {
        this->setEipPtr(values[index], index);
    }
}

void RegisterBlock::setEaxPtr(unsigned long value, int offset)
{
    this->eax.currentValues[offset] = value;
    this->eaxPtrStrings[offset]->setString(std::to_string(this->eax.currentValues[offset]));
    this->eaxPtrLabels[offset]->setTextColor((this->eax.currentValues[offset] == this->eax.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEbxPtr(unsigned long value, int offset)
{
    this->ebx.currentValues[offset] = value;
    this->ebxPtrStrings[offset]->setString(std::to_string(this->ebx.currentValues[offset]));
    this->ebxPtrLabels[offset]->setTextColor((this->ebx.currentValues[offset] == this->ebx.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEcxPtr(unsigned long value, int offset)
{
    this->ecx.currentValues[offset] = value;
    this->ecxPtrStrings[offset]->setString(std::to_string(this->ecx.currentValues[offset]));
    this->ecxPtrLabels[offset]->setTextColor((this->ecx.currentValues[offset] == this->ecx.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEdxPtr(unsigned long value, int offset)
{
    this->edx.currentValues[offset] = value;
    this->edxPtrStrings[offset]->setString(std::to_string(this->edx.currentValues[offset]));
    this->edxPtrLabels[offset]->setTextColor((this->edx.currentValues[offset] == this->edx.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEdiPtr(unsigned long value, int offset)
{
    this->edi.currentValues[offset] = value;
    this->ediPtrStrings[offset]->setString(std::to_string(this->edi.currentValues[offset]));
    this->ediPtrLabels[offset]->setTextColor((this->edi.currentValues[offset] == this->edi.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEsiPtr(unsigned long value, int offset)
{
    this->esi.currentValues[offset] = value;
    this->esiPtrStrings[offset]->setString(std::to_string(this->esi.currentValues[offset]));
    this->esiPtrLabels[offset]->setTextColor((this->esi.currentValues[offset] == this->esi.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEbpPtr(unsigned long value, int offset)
{
    this->ebp.currentValues[offset] = value;
    this->ebpPtrStrings[offset]->setString(std::to_string(this->ebp.currentValues[offset]));
    this->ebpPtrLabels[offset]->setTextColor((this->ebp.currentValues[offset] == this->ebp.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEspPtr(unsigned long value, int offset)
{
    this->esp.currentValues[offset] = value;
    this->espPtrStrings[offset]->setString(std::to_string(this->esp.currentValues[offset]));
    this->espPtrLabels[offset]->setTextColor((this->esp.currentValues[offset] == this->esp.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEipPtr(unsigned long value, int offset)
{
    this->eip.currentValues[offset] = value;
    this->eipPtrStrings[offset]->setString(std::to_string(this->eip.currentValues[offset]));
    this->eipPtrLabels[offset]->setTextColor((this->eip.currentValues[offset] == this->eip.initialValues[offset]) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEax(unsigned long eax)
{
    this->eax.currentValue = eax;
    this->eaxString->setString(std::to_string(this->eax.currentValue));
    this->eaxLabel->setTextColor((this->eax.currentValue == this->eax.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEbx(unsigned long ebx)
{
    this->ebx.currentValue = ebx;
    this->ebxString->setString(std::to_string(this->ebx.currentValue));
    this->ebxLabel->setTextColor((this->ebx.currentValue == this->ebx.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEcx(unsigned long ecx)
{
    this->ecx.currentValue = ecx;
    this->ecxString->setString(std::to_string(this->ecx.currentValue));
    this->ecxLabel->setTextColor((this->ecx.currentValue == this->ecx.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEdx(unsigned long edx)
{
    this->edx.currentValue = edx;
    this->edxString->setString(std::to_string(this->edx.currentValue));
    this->edxLabel->setTextColor((this->edx.currentValue == this->edx.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEdi(unsigned long edi)
{
    this->edi.currentValue = edi;
    this->ediString->setString(std::to_string(this->edi.currentValue));
    this->ediLabel->setTextColor((this->edi.currentValue == this->edi.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEsi(unsigned long esi)
{
    this->esi.currentValue = esi;
    this->esiString->setString(std::to_string(this->esi.currentValue));
    this->esiLabel->setTextColor((this->esi.currentValue == this->esi.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEbp(unsigned long ebp)
{
    this->ebp.currentValue = ebp;
    this->ebpString->setString(std::to_string(this->ebp.currentValue));
    this->ebpLabel->setTextColor((this->ebp.currentValue == this->ebp.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEsp(unsigned long esp)
{
    this->esp.currentValue = esp;
    this->espString->setString(std::to_string(this->esp.currentValue));
    this->espLabel->setTextColor((this->esp.currentValue == this->esp.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

void RegisterBlock::setEip(unsigned long eip)
{
    this->eip.currentValue = eip;
    this->eipString->setString(std::to_string(this->eip.currentValue));
    this->eipLabel->setTextColor((this->eip.currentValue == this->eip.initialValue) ? LexiconPage::TextColor : LexiconPage::TextColorChanged);
}

unsigned long RegisterBlock::getEax()
{
    return this->eax.currentValue;
}

unsigned long RegisterBlock::getEbx()
{
    return this->ebx.currentValue;
}

unsigned long RegisterBlock::getEcx()
{
    return this->ecx.currentValue;
}

unsigned long RegisterBlock::getEdx()
{
    return this->edx.currentValue;
}

unsigned long RegisterBlock::getEdi()
{
    return this->edi.currentValue;
}

unsigned long RegisterBlock::getEsi()
{
    return this->esi.currentValue;
}

unsigned long RegisterBlock::getEbp()
{
    return this->ebp.currentValue;
}

unsigned long RegisterBlock::getEsp()
{
    return this->esp.currentValue;
}

unsigned long RegisterBlock::getEip()
{
    return this->eip.currentValue;
}

unsigned long RegisterBlock::getEaxPtr(int offset)
{
    return this->eax.currentValues[offset];
}

unsigned long RegisterBlock::getEbxPtr(int offset)
{
    return this->ebx.currentValues[offset];
}

unsigned long RegisterBlock::getEcxPtr(int offset)
{
    return this->ecx.currentValues[offset];
}

unsigned long RegisterBlock::getEdxPtr(int offset)
{
    return this->edx.currentValues[offset];
}

unsigned long RegisterBlock::getEdiPtr(int offset)
{
    return this->edi.currentValues[offset];
}

unsigned long RegisterBlock::getEsiPtr(int offset)
{
    return this->esi.currentValues[offset];
}

unsigned long RegisterBlock::getEbpPtr(int offset)
{
    return this->ebp.currentValues[offset];
}

unsigned long RegisterBlock::getEspPtr(int offset)
{
    return this->esp.currentValues[offset];
}

unsigned long RegisterBlock::getEipPtr(int offset)
{
    return this->eip.currentValues[offset];
}

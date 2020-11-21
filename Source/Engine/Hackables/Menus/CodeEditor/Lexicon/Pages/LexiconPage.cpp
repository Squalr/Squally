#include "LexiconPage.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const Size LexiconPage::TotalPageSize = Size(580.0f, 832.0f);
const Size LexiconPage::PageMargin = Size(32.0f, 32.0f);
const Size LexiconPage::PageSize = LexiconPage::TotalPageSize - LexiconPage::PageMargin * 2.0f;
const Vec2 LexiconPage::PageOffset = Vec2(324.0f, 36.0f);
const Vec2 LexiconPage::FullPageSecondOffset = Vec2(LexiconPage::PageOffset.x * 2.0f, 0.0f);
const Vec2 LexiconPage::ChapterMarkerLocation = Vec2(-LexiconPage::PageSize.width / 2.0f + 64.0f, LexiconPage::PageSize.height / 2.0f - 192.0f);
const Vec2 LexiconPage::ChapterLocation = Vec2(-96.0f, LexiconPage::PageSize.height / 2.0f);
const Vec2 LexiconPage::IntroLocation = LexiconPage::ChapterLocation + Vec2(0.0f, -48.0f);
const Vec2 LexiconPage::BackButtonLocation = Vec2(-PageSize.width / 2.0f + 32.0f, -PageSize.height / 2.0f + 32.0f);
const Color4B LexiconPage::TextColor = Color4B(62, 45, 32, 255);
const Color4B LexiconPage::TextColorChanged = Color4B(160, 45, 32, 255);

LexiconPage::LexiconPage(std::string pageIdentifier, PageType pageType)
{
    this->pageType = pageType;
    this->pageIdentifier = pageIdentifier;
    this->debugDrawNode = DrawNode::create();
    this->backButton = ClickableNode::create(UIResources::Menus_LexiconMenu_BackButton, UIResources::Menus_LexiconMenu_BackButtonSelected);

    this->debugDrawNode->setVisible(false);
    this->backButton->setVisible(false);
    this->setVisible(false);

    this->debugDrawNode->drawSolidRect(-Vec2(LexiconPage::TotalPageSize / 2.0f), LexiconPage::TotalPageSize / 2.0f, Color4F(Color4B(255, 0, 0, 128)));
    this->debugDrawNode->drawSolidRect(-Vec2(LexiconPage::PageSize / 2.0f), LexiconPage::PageSize / 2.0f, Color4F(Color4B(0, 255, 0, 128)));

    this->addChild(this->debugDrawNode);
    this->addChild(this->backButton);
}

LexiconPage::~LexiconPage()
{
}

void LexiconPage::onEnter()
{
    super::onEnter();
}

void LexiconPage::initializePositions()
{
	super::initializePositions();

	this->backButton->setPosition(LexiconPage::BackButtonLocation);
}

void LexiconPage::initializeListeners()
{
    super::initializeListeners();

    this->addEventListener(EventListenerCustom::create(HackableEvents::EventCloseLeftLexiconPage, [=](EventCustom* eventCustom)
    {
        switch (this->pageType)
        {
            case PageType::Full:
            case PageType::Left:
            {
                this->setVisible(false);
                break;
            }
            default:
            {
                break;
            }
        }
    }));

    this->addEventListener(EventListenerCustom::create(HackableEvents::EventCloseRightLexiconPage, [=](EventCustom* eventCustom)
    {
        switch (this->pageType)
        {
            case PageType::Full:
            case PageType::Right:
            {
                this->setVisible(false);
                break;
            }
            default:
            {
                break;
            }
        }
    }));
    
    this->addEventListener(EventListenerCustom::create(HackableEvents::EventOpenLexiconPage, [=](EventCustom* eventCustom)
    {
        OpenLexiconPageArgs* args = static_cast<OpenLexiconPageArgs*>(eventCustom->getUserData());

        if (args != nullptr)
        {
            if (args->pageIdentifier == this->pageIdentifier)
            {
                switch (this->pageType)
                {
                    case PageType::Left:
                    {
                        HackableEvents::TriggerCloseLeftLexiconPage();
                        break;
                    }
                    case PageType::Right:
                    {
                        HackableEvents::TriggerCloseRightLexiconPage();
                        break;
                    }
                    case PageType::Full:
                    {
                        HackableEvents::TriggerCloseLeftLexiconPage();
                        HackableEvents::TriggerCloseRightLexiconPage();
                        break;
                    }
                }

                this->setVisible(true);
            }
        }
    }));
}

void LexiconPage::onDeveloperModeEnable(int debugLevel)
{
    super::onDeveloperModeEnable(debugLevel);

    this->debugDrawNode->setVisible(true);
}

void LexiconPage::onDeveloperModeDisable()
{
    super::onDeveloperModeDisable();

    this->debugDrawNode->setVisible(false);
}


LexiconPage::PageType LexiconPage::getPageType()
{
    return this->pageType;
}

void LexiconPage::enableBack(std::string backPage, bool closeExisting)
{
    this->backButton->setVisible(true);

    this->backButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
    {
        if (closeExisting)
        {
            HackableEvents::TriggerCloseLeftLexiconPage();
            HackableEvents::TriggerCloseRightLexiconPage();
        }
        
		HackableEvents::TriggerOpenLexiconPage(OpenLexiconPageArgs(backPage));
    });
}

void LexiconPage::enableBack(std::string backPageLeft, std::string backPageRight)
{
    this->backButton->setVisible(true);

    this->backButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
    {
		HackableEvents::TriggerOpenLexiconPage(OpenLexiconPageArgs(backPageLeft));
		HackableEvents::TriggerOpenLexiconPage(OpenLexiconPageArgs(backPageRight));
    });
}

ClickableTextNode* LexiconPage::buildInstructionLabel(LocalizedString* instructionStr, std::string instructionIdentifier)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, instructionStr);
	LocalizedLabel* labelSelected = label->clone();

	ClickableTextNode* button = ClickableTextNode::create(label, labelSelected, UIResources::Menus_LexiconMenu_InstructionFrame, UIResources::Menus_LexiconMenu_InstructionFrameSelected);
	
	button->setTextOffset(Vec2(0.0f, -12.0f));

	label->setTextColor(LexiconPage::TextColor);
	labelSelected->setTextColor(LexiconPage::TextColor);

	button->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		HackableEvents::TriggerCloseRightLexiconPage();
		HackableEvents::TriggerOpenLexiconPage(OpenLexiconPageArgs(instructionIdentifier));
	});

    return button;
}

ClickableTextNode* LexiconPage::buildInstructionLabel(LocalizedString* instructionStr, std::string instructionIdentifierA, std::string instructionIdentifierB)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, instructionStr);
	LocalizedLabel* labelSelected = label->clone();

	ClickableTextNode* button = ClickableTextNode::create(label, labelSelected, UIResources::Menus_LexiconMenu_InstructionFrame, UIResources::Menus_LexiconMenu_InstructionFrameSelected);
	
	button->setTextOffset(Vec2(0.0f, -12.0f));

	label->setTextColor(LexiconPage::TextColor);
	labelSelected->setTextColor(LexiconPage::TextColor);

	button->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		HackableEvents::TriggerCloseLeftLexiconPage();
		HackableEvents::TriggerCloseRightLexiconPage();
		HackableEvents::TriggerOpenLexiconPage(OpenLexiconPageArgs(instructionIdentifierA));
		HackableEvents::TriggerOpenLexiconPage(OpenLexiconPageArgs(instructionIdentifierB));
	});

    return button;
}

LocalizedString* LexiconPage::pointerizeString(LocalizedString* memRegString)
{
    LocalizedString* pointerizedString = Strings::Menus_Hacking_Lexicon_Assembly_Ptr::create();

    pointerizedString->setStringReplacementVariables(memRegString);

    return pointerizedString;
}

LocalizedString* LexiconPage::offsetString(LocalizedString* memRegString, int offset)
{
    if (offset > 0)
    {
        LocalizedString* offsetString = Strings::Menus_Hacking_Lexicon_Assembly_OffsetPositive::create();

        offsetString->setStringReplacementVariables({ memRegString, ConstantString::create(std::to_string(offset)) });

        return this->pointerizeString(offsetString);
    }
    else if (offset < 0)
    {
        LocalizedString* offsetString = Strings::Menus_Hacking_Lexicon_Assembly_OffsetNegative::create();

        offsetString->setStringReplacementVariables({ memRegString, ConstantString::create(std::to_string(std::abs(offset))) });

        return this->pointerizeString(offsetString);
    }
    else
    {
        return this->pointerizeString(memRegString);
    }
}

LocalizedLabel* LexiconPage::createInstructionLabelSingle(LocalizedString* instructionString, LocalizedString* memRegString)
{
    instructionString->setStringReplacementVariables(memRegString);

    LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, instructionString);

    label->setTextColor(LexiconPage::TextColor);
    label->setAnchorPoint(Vec2(0.0f, 0.5f));

    return label;
}

LocalizedLabel* LexiconPage::createInstructionLabelDouble(LocalizedString* instructionString, LocalizedString* memRegStringA, LocalizedString* memRegStringB)
{
    instructionString->setStringReplacementVariables({ memRegStringA, memRegStringB });

    LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, instructionString);

    label->setTextColor(LexiconPage::TextColor);
    label->setAnchorPoint(Vec2(0.0f, 0.5f));

    return label;
}
    
ClickableTextNode* LexiconPage::buildExecuteButton()
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Execute::create());
	LocalizedLabel* labelSelected = label->clone();

	ClickableTextNode* button = ClickableTextNode::create(label, labelSelected, UIResources::Menus_LexiconMenu_ExecuteButton, UIResources::Menus_LexiconMenu_ExecuteButtonSelected);
	
	label->setTextColor(LexiconPage::TextColor);
	labelSelected->setTextColor(LexiconPage::TextColor);

    return button;
}

ClickableTextNode* LexiconPage::buildResetButton()
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_Lexicon_Reset::create());
	LocalizedLabel* labelSelected = label->clone();

	ClickableTextNode* button = ClickableTextNode::create(label, labelSelected, UIResources::Menus_LexiconMenu_ResetButton, UIResources::Menus_LexiconMenu_ResetButtonSelected);

	label->setTextColor(LexiconPage::TextColor);
	labelSelected->setTextColor(LexiconPage::TextColor);

    return button;
}

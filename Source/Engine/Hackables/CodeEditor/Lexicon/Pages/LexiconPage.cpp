#include "LexiconPage.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const Size LexiconPage::TotalPageSize = Size(580.0f, 832.0f);
const Size LexiconPage::PageMargin = Size(32.0f, 32.0f);
const Size LexiconPage::PageSize = LexiconPage::TotalPageSize - LexiconPage::PageMargin * 2.0f;
const Vec2 LexiconPage::ChapterMarkerLocation = Vec2(-LexiconPage::PageSize.width / 2.0f + 64.0f, LexiconPage::PageSize.height / 2.0f - 192.0f);
const Vec2 LexiconPage::ChapterLocation = Vec2(-96.0f, LexiconPage::PageSize.height / 2.0f);
const Vec2 LexiconPage::IntroLocation = LexiconPage::ChapterLocation + Vec2(0.0f, -48.0f);
const Vec2 LexiconPage::BackButtonLocation = Vec2(-PageSize.width / 2.0f + 32.0f, -PageSize.height / 2.0f + 32.0f);
const Color4B LexiconPage::TextColor = Color4B(62, 45, 32, 255);

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
        HackableEvents::OpenLexiconPageArgs* args = static_cast<HackableEvents::OpenLexiconPageArgs*>(eventCustom->getUserData());

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

void LexiconPage::onDeveloperModeEnable()
{
    super::onDeveloperModeEnable();

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

    this->backButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        if (closeExisting)
        {
            HackableEvents::TriggerCloseLeftLexiconPage();
            HackableEvents::TriggerCloseRightLexiconPage();
        }
        
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(backPage));
    });
}

void LexiconPage::enableBack(std::string backPageLeft, std::string backPageRight)
{
    this->backButton->setVisible(true);

    this->backButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(backPageLeft));
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(backPageRight));
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

	button->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		HackableEvents::TriggerCloseRightLexiconPage();
		HackableEvents::TriggerOpenLexiconPage(HackableEvents::OpenLexiconPageArgs(instructionIdentifier));
	});

    return button;
}

#include "LexiconPage.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"

using namespace cocos2d;

const Size LexiconPage::TotalPageSize = Size(580.0f, 832.0f);
const Size LexiconPage::PageMargin = Size(32.0f, 32.0f);
const Size LexiconPage::PageSize = LexiconPage::TotalPageSize - LexiconPage::PageMargin * 2.0f;
const Vec2 LexiconPage::ChapterMarkerLocation = Vec2(-LexiconPage::PageSize.width / 2.0f + 64.0f, LexiconPage::PageSize.height / 2.0f - 192.0f);
const Vec2 LexiconPage::ChapterLocation = LexiconPage::ChapterMarkerLocation + Vec2(32.0f, 32.0f);
const Color4B LexiconPage::TextColor = Color4B(62, 45, 32, 255);

LexiconPage::LexiconPage(std::string pageIdentifier, PageType pageType)
{
    this->pageType = pageType;
    this->pageIdentifier = pageIdentifier;
    this->debugDrawNode = DrawNode::create();

    this->debugDrawNode->setVisible(false);
    this->setVisible(false);

    this->debugDrawNode->drawSolidRect(-Vec2(LexiconPage::TotalPageSize / 2.0f), LexiconPage::TotalPageSize / 2.0f, Color4F(Color4B(255, 0, 0, 128)));
    this->debugDrawNode->drawSolidRect(-Vec2(LexiconPage::PageSize / 2.0f), LexiconPage::PageSize / 2.0f, Color4F(Color4B(0, 255, 0, 128)));

    this->addChild(this->debugDrawNode);
}

LexiconPage::~LexiconPage()
{
}

void LexiconPage::onEnter()
{
    super::onEnter();
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

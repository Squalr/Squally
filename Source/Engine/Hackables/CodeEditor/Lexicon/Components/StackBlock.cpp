#include "StackBlock.h"

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

#include "Strings/Hacking/Lexicon/Stack.h"

using namespace cocos2d;

const int StackBlock::StackSize = 7;

StackBlock* StackBlock::create()
{
    StackBlock* instance = new StackBlock();

    instance->autorelease();

    return instance;
}

StackBlock::StackBlock()
{
	this->labelStrings = std::vector<ConstantString*>();
	this->labels = std::vector<LocalizedLabel*>();
    this->stackBlock = Sprite::create(UIResources::Menus_LexiconMenu_StackBlock);
    this->stackSelector = Sprite::create(UIResources::Menus_LexiconMenu_StackSelector);
    this->stackTitleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_Lexicon_Stack::create());
    
    for (int index = 0; index < StackBlock::StackSize; index++)
    {
        ConstantString* str = ConstantString::create("");
        LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, str);

        label->setTextColor(LexiconPage::TextColor);
        label->setAnchorPoint(Vec2(0.0f, 0.5f));
        
        this->labelStrings.push_back(str);
        this->labels.push_back(label);
    }

    this->stackTitleLabel->setTextColor(LexiconPage::TextColor);
    this->stackTitleLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->stackSelector->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->stackSelector->setOpacity(0);

    this->addChild(this->stackBlock);
    this->addChild(this->stackTitleLabel);

    for (auto it = this->labels.begin(); it != this->labels.end(); it++)
    {
        this->addChild(*it);
    }

    this->addChild(this->stackSelector);
}

StackBlock::~StackBlock()
{
}

void StackBlock::onEnter()
{
    super::onEnter();
}

void StackBlock::initializePositions()
{
	super::initializePositions();

    const float Spacing = 28.0f;
    const float Offset = (Spacing * float(StackBlock::StackSize)) / 2.0f - 14.0f;

	this->stackTitleLabel->setPosition(Vec2(-88.0f - 12.0f, Offset + 48.0f));

    for (int index = 0; index < this->labels.size(); index++)
    {
        this->labels[index]->setPosition(Vec2(-72.0f, Offset - Spacing * float(StackBlock::StackSize - index - 1)));
    }
}

void StackBlock::clearHighlights()
{
    this->stackSelector->setOpacity(0);
}

void StackBlock::highlightTop()
{
    int index = this->values.size() <= 0 ? 0 : (this->values.size() - 1);

    this->stackSelector->setOpacity(255);
    this->stackSelector->setPosition(this->labels[index]->getPosition() - Vec2(22.0f, 0.0f));
}

void StackBlock::highlightTopPlus1()
{
    int index = this->values.size() <= 0 ? 0 : (this->values.size());
    index = index == StackBlock::StackSize ? (index - 1) : index;

    this->stackSelector->setOpacity(255);
    this->stackSelector->setPosition(this->labels[index]->getPosition() - Vec2(22.0f, 0.0f));
}

void StackBlock::clear()
{
    while(this->values.size() > 0)
    {
        this->pop();
    }
}

void StackBlock::push(unsigned long long value)
{
    if (this->values.size() >= StackBlock::StackSize)
    {
        return;
    }

    this->labelStrings[this->values.size()]->setString(std::to_string(value));
    this->values.push_back(value);
}

unsigned long long StackBlock::pop()
{
    if (this->values.size() <= 0)
    {
        return 0;
    }

    this->labelStrings[this->values.size() - 1]->setString("");

    unsigned long long ret = this->values[this->values.size() - 1];

    this->values.pop_back();

    return ret;
}

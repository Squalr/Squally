#include "HexusChapterPreview.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

#include "Resources/SoundResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

HexusChapterPreview* HexusChapterPreview::create(std::string chapterNameKey, LocalizedString* localizedChapterName)
{
	HexusChapterPreview* instance = new HexusChapterPreview(chapterNameKey, localizedChapterName);

	instance->autorelease();

	return instance;
}

HexusChapterPreview::HexusChapterPreview(std::string chapterSaveKey, LocalizedString* localizedChapterName)
{
	this->chapterSaveKey = chapterSaveKey;
	this->callback = nullptr;
	this->contentNode = Node::create();
	this->frameBackground = Sprite::create(HexusResources::Menus_EnemyFrameBackground);
	this->frame = ClickableNode::create(HexusResources::Menus_EnemyFrame, HexusResources::Menus_EnemyFrameHover);
	this->frame->setClickSound(SoundResources::Menus_Simple_Button);
	this->lockedSprite = Sprite::create(UIResources::Menus_Icons_Lock);
	this->text = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, localizedChapterName);

	DrawNode* clipStencil = DrawNode::create();
	Size frameSize = Size(this->frame->getContentSize().width, this->frame->getContentSize().height);
	Size clipSize = Size(frameSize.width - 64.0f, frameSize.height - 64.0f);
	clipStencil->drawSolidRect(Vec2(-clipSize.width / 2.0f, -clipSize.height / 2.0f), Vec2(clipSize.width / 2.0f, clipSize.height / 2.0f), Color4F::GREEN);

	this->frameClip = SmartClippingNode::create(this->contentNode, clipStencil);

	this->lockedSprite->setVisible(false);
	this->text->setVisible(false);

	this->text->enableOutline(Color4B::BLACK, 2);
	this->text->setColor(Color3B::WHITE);

	this->setContentSize(this->frame->getContentSize());

	this->addChild(this->frameBackground);
	this->addChild(this->frameClip);
	this->addChild(this->frame);
	this->addChild(this->lockedSprite);
	this->addChild(this->text);
}

HexusChapterPreview::~HexusChapterPreview()
{
}

void HexusChapterPreview::onEnter()
{
	super::onEnter();
}

void HexusChapterPreview::initializePositions()
{
	super::initializePositions();

	this->text->setPosition(Vec2(0.0f, -188.0f));
	this->lockedSprite->setPosition(Vec2(0.0f, -188.0f));
	this->frameBackground->setPosition(Vec2(0.0f, 32.0f));
}

void HexusChapterPreview::initializeListeners()
{
	super::initializeListeners();

	this->frame->setMouseClickCallback(CC_CALLBACK_0(HexusChapterPreview::onOpponentClick, this));
}

void HexusChapterPreview::disableInteraction()
{
	this->frame->disableInteraction();
	this->contentNode->setOpacity(96);
	this->text->setVisible(false);
	this->lockedSprite->setVisible(true);
}

void HexusChapterPreview::enableInteraction()
{
	this->frame->enableInteraction();
	this->contentNode->setOpacity(255);
	this->text->setVisible(true);
	this->lockedSprite->setVisible(false);
}

void HexusChapterPreview::setMouseClickCallback(std::function<void()> callback)
{
	this->callback = callback;
}

void HexusChapterPreview::onOpponentClick()
{
	if (this->callback != nullptr)
	{
		this->callback();
	}
}

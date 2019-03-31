#include "HexusChapterPreview.h"

#include "cocos/2d/CCClippingNode.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

#include "Resources/SoundResources.h"
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
	this->frame = ClickableNode::create(UIResources::Menus_Hexus_EnemyFrame, UIResources::Menus_Hexus_EnemyFrameHover);
	this->frame->setClickSound(SoundResources::Menus_Simple_Button);
	this->text = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, localizedChapterName);

	DrawNode* clipStencil = DrawNode::create();
	Size frameSize = Size(this->frame->getContentSize().width, this->frame->getContentSize().height);
	Size clipSize = Size(frameSize.width - 64.0f, frameSize.height - 64.0f);
	clipStencil->drawSolidRect(Vec2(-clipSize.width / 2.0f, -clipSize.height / 2.0f), Vec2(clipSize.width / 2.0f, clipSize.height / 2.0f), Color4F::GREEN);

	// Enable to debug clipping:
	//this->addChild(clipStencil);

	this->frameClip = ClippingNode::create(clipStencil);
	this->frameClip->setAnchorPoint(Vec2::ZERO);
	this->frameClip->setCascadeOpacityEnabled(true);

	this->text->enableOutline(Color4B::BLACK, 2);
	this->text->setColor(Color3B::WHITE);

	this->setContentSize(this->frame->getContentSize());
	this->setCascadeOpacityEnabled(true);

	this->addChild(this->frameClip);
	this->addChild(this->frame);
	this->addChild(this->text);
}

HexusChapterPreview::~HexusChapterPreview()
{
}

void HexusChapterPreview::initializePositions()
{
	 this->text->setPosition(Vec2(0.0f, -188.0f));
}

void HexusChapterPreview::initializeListeners()
{
	super::initializeListeners();

	this->frame->setMouseClickCallback(CC_CALLBACK_0(HexusChapterPreview::onOpponentClick, this));
}

void HexusChapterPreview::disableInteraction()
{
	this->frame->disableInteraction(128);
	this->frameClip->setOpacity(128);
}

void HexusChapterPreview::enableInteraction()
{
	this->frame->enableInteraction();
	this->frameClip->setOpacity(255);
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

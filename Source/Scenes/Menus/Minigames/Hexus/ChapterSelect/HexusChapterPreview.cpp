#include "HexusChapterPreview.h"

HexusChapterPreview* HexusChapterPreview::create()
{
	HexusChapterPreview* instance = new HexusChapterPreview();

	instance->autorelease();

	return instance;
}

HexusChapterPreview::HexusChapterPreview()
{
	this->callback = nullptr;
	this->frame = MenuSprite::create(Resources::Menus_MinigamesMenu_Hexus_EnemyFrame, Resources::Menus_MinigamesMenu_Hexus_EnemyFrameHover, Resources::Menus_MinigamesMenu_Hexus_EnemyFrameClick);

	DrawNode* clipStencil = DrawNode::create();
	Size frameSize = Size(this->frame->getContentSize().width, this->frame->getContentSize().height);
	Size clipSize = Size(frameSize.width - 48.0f, frameSize.height - 48.0f);
	clipStencil->drawSolidRect(Vec2(-clipSize.width / 2.0f, -clipSize.height / 2.0f), Vec2(clipSize.width / 2.0f, clipSize.height / 2.0f), Color4F::GREEN);

	// Enable to debug clipping:
	// this->addChild(clipStencil);

	this->frameClip = ClippingNode::create(clipStencil);
	this->frameClip->setAnchorPoint(Vec2::ZERO);
	this->frameClip->setCascadeOpacityEnabled(true);

	this->setContentSize(this->frame->getContentSize());
	this->setCascadeOpacityEnabled(true);

	this->addChild(this->frameClip);
	this->addChild(this->frame);
}

HexusChapterPreview::~HexusChapterPreview()
{
}

void HexusChapterPreview::initializePositions()
{
}

void HexusChapterPreview::initializeListeners()
{
	SmartNode::initializeListeners();

	this->frame->setClickCallback(CC_CALLBACK_1(HexusChapterPreview::onOpponentClick, this));
}

void HexusChapterPreview::setClickCallback(std::function<void()> callback)
{
	this->callback = callback;
}

void HexusChapterPreview::onOpponentClick(MenuSprite* HexusChapterPreview)
{
	if (this->callback != nullptr)
	{
		this->callback();
	}
}

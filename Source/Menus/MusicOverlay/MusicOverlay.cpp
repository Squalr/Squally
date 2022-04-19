#include "MusicOverlay.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/SoundEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Music.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const Vec2 MusicOverlay::ScrollOutDelta = Vec2(0.0f, -128.0f);
std::string MusicOverlay::CachedLastPlayedMusic = "";

MusicOverlay* MusicOverlay::create()
{
	MusicOverlay* instance = new MusicOverlay();

	instance->autorelease();

	return instance;
}

MusicOverlay::MusicOverlay()
{
	this->contentNode = Node::create();
	this->musicString = Strings::Menus_Music_Track::create()->setStringReplacementVariables(ConstantString::create(""));
	this->artistString = Strings::Menus_Music_Artist::create()->setStringReplacementVariables(ConstantString::create(""));
	this->musicLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->musicString);
	this->artistLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, this->artistString);
	this->note = Sprite::create(UIResources::Menus_MusicOverlay_Note);

	this->musicLabel->enableOutline(Color4B::BLACK, 2);
	this->artistLabel->enableOutline(Color4B::BLACK, 2);

	this->musicLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->artistLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->contentNode->addChild(this->note);
	this->contentNode->addChild(this->musicLabel);
	this->contentNode->addChild(this->artistLabel);
	this->addChild(this->contentNode);
}

MusicOverlay::~MusicOverlay()
{
}

void MusicOverlay::initializePositions()
{
	super::initializePositions();

	const CSize visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 Offset = Vec2(visibleSize.width - 72.0f, 64.0f);

	this->note->setPosition(Offset + Vec2(32.0f, 16.0f));
	this->musicLabel->setPosition(Offset + Vec2(0.0f, 32.0f));
	this->artistLabel->setPosition(Offset + Vec2(0.0f, 0.0f));

	this->contentNode->setPosition(MusicOverlay::ScrollOutDelta);
}

void MusicOverlay::initializeListeners()
{
	super::initializeListeners();
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(SoundEvents::EventMusicPlayed, [=](EventCustom* eventCustom)
	{
		SoundEvents::MusicPlayedArgs* args = static_cast<SoundEvents::MusicPlayedArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->showOverlayForMusic(args->music);
		}
	}));
}

void MusicOverlay::showOverlayForMusic(Music* music)
{
	if (music == nullptr)
	{
		return;
	}

	std::string musicResource = music->getSoundResource();

	if (MusicOverlay::CachedLastPlayedMusic == musicResource)
	{
		return;
	}

	MusicOverlay::CachedLastPlayedMusic = musicResource;

	this->musicLabel->setStringReplacementVariables(music->getMusicName());
	this->artistLabel->setStringReplacementVariables(music->getArtistName());

	this->contentNode->runAction(Sequence::create(
		MoveTo::create(0.5f, Vec2::ZERO),
		DelayTime::create(2.0f),
		MoveTo::create(0.5f, MusicOverlay::ScrollOutDelta),
		nullptr
	));
}

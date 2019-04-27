#include "PointerTraceLevelSelect.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEvent.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/MouseEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Scenes/PointerTrace/Menus/LevelSelect/LevelNode.h"
#include "Scenes/PointerTrace/Menus/LevelSelect/LevelSegment.h"

#include "Resources/MapResources.h"
#include "Resources/MusicResources.h"
#include "Resources/PointerTraceResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

PointerTraceLevelSelect* PointerTraceLevelSelect::instance = nullptr;

void PointerTraceLevelSelect::registerGlobalScene()
{
	if (PointerTraceLevelSelect::instance == nullptr)
	{
		PointerTraceLevelSelect::instance = new PointerTraceLevelSelect();

		PointerTraceLevelSelect::instance->autorelease();
		PointerTraceLevelSelect::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(PointerTraceLevelSelect::instance);
}

PointerTraceLevelSelect::PointerTraceLevelSelect()
{
	this->levelSegments = std::vector<LevelSegment*>();
	this->background = Sprite::create(PointerTraceResources::BalmerPeaks);
	this->hud = Hud::create();
	this->segmentsNode = Node::create();

	LevelSegment* endianForestSegment = LevelSegment::create(LevelSegment::SegmentType::EndianForest);
	LevelSegment* underflowRuinsSegment = LevelSegment::create(LevelSegment::SegmentType::UnderflowRuins);
	LevelSegment* seaSharpCavernsSegment = LevelSegment::create(LevelSegment::SegmentType::SeaSharpCaverns);
	LevelSegment* castleValgrindSegment = LevelSegment::create(LevelSegment::SegmentType::CastleValgrind);
	LevelSegment* balmerPeaksSegment = LevelSegment::create(LevelSegment::SegmentType::BalmerPeaks);
	LevelSegment* daemonsHallowSegment = LevelSegment::create(LevelSegment::SegmentType::DaemonsHallow);
	LevelSegment* lambdaCryptsSegment = LevelSegment::create(LevelSegment::SegmentType::LambdaCrypts);
	LevelSegment* voidStarSegment = LevelSegment::create(LevelSegment::SegmentType::VoidStar);

	this->addSegment(endianForestSegment);
	this->addSegment(underflowRuinsSegment);
	this->addSegment(seaSharpCavernsSegment);
	this->addSegment(castleValgrindSegment);
	this->addSegment(balmerPeaksSegment);
	this->addSegment(daemonsHallowSegment);
	this->addSegment(lambdaCryptsSegment);
	this->addSegment(voidStarSegment);
	this->stitchSegments();

	this->background->setAnchorPoint(Vec2(0.0f, 0.0f));

	this->addChild(this->background);
	this->addChild(this->segmentsNode);
	this->addChild(this->hud);
}

PointerTraceLevelSelect::~PointerTraceLevelSelect()
{
}

void PointerTraceLevelSelect::onEnter()
{
	super::onEnter();

	const float delay = 0.5f;
	const float duration = 0.75f;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float totalHeight = 0.0f;

	for (auto it = this->levelSegments.begin(); it != this->levelSegments.end(); it++)
	{
		totalHeight += (*it)->getContentSize().height;
	}

	CameraTrackingData trackingData = CameraTrackingData(Mouse::getInstance(), Vec2(416.0f, 234.0f), CameraTrackingData::CameraScrollType::Ellipse);
	GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, visibleSize.width, totalHeight));

	// Because the mouse is a HUD object (and thus unaffected by the camera position), we need a custom function for getting the position to help with camera tracking
	trackingData.customPositionFunction = [=]()
	{
		return Mouse::getInstance()->getPosition() + GameCamera::getInstance()->getCameraPosition() - visibleSize / 2.0f;
	};

	SoundManager::playMusicResource(MusicResources::Little_Wings_cut);

	GameCamera::getInstance()->setTarget(trackingData);
}

void PointerTraceLevelSelect::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	float totalHeight = 0.0f;

	for (auto it = this->levelSegments.begin(); it != this->levelSegments.end(); it++)
	{
		(*it)->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalHeight));
		totalHeight += (*it)->getContentSize().height;
	}
}

void PointerTraceLevelSelect::initializeListeners()
{
	super::initializeListeners();

	PointerTraceLevelSelect::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigatePointerTraceLevelSelect, [](EventCustom* args)
	{
		GlobalDirector::loadScene(PointerTraceLevelSelect::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(PointerTraceLevelSelect::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void PointerTraceLevelSelect::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}

void PointerTraceLevelSelect::addSegment(LevelSegment* levelSegment)
{
	this->levelSegments.push_back(levelSegment);

	this->segmentsNode->addChild(levelSegment);
}

void PointerTraceLevelSelect::stitchSegments()
{
	std::vector<LevelSegment*>::iterator prevIt = this->levelSegments.begin();

	for (auto it = this->levelSegments.begin(); it != this->levelSegments.end(); it++)
	{
		auto nextIt = (it + 1);
		bool noPrevious = prevIt == this->levelSegments.begin();
		bool noNext = nextIt == this->levelSegments.end();

		if ((noPrevious || (*it)->getSegmentType() != (*prevIt)->getSegmentType()) && (noNext || (*it)->getSegmentType() != (*nextIt)->getSegmentType()))
		{
			(*it)->loadSprite(LevelSegment::PieceType::SegmentMid);
		}
		else if ((noPrevious || (*it)->getSegmentType() != (*prevIt)->getSegmentType()) && (noNext || (*it)->getSegmentType() == (*nextIt)->getSegmentType()))
		{
			(*it)->loadSprite(LevelSegment::PieceType::SegmentBottom);
		}
		else if ((noPrevious || (*it)->getSegmentType() == (*prevIt)->getSegmentType()) && (noNext || (*it)->getSegmentType() != (*nextIt)->getSegmentType()))
		{
			(*it)->loadSprite(LevelSegment::PieceType::SegmentTop);
		}
		else
		{
			(*it)->loadSprite(LevelSegment::PieceType::Normal);
		}

		prevIt = it;
	}
}

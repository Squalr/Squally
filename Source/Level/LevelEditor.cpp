#include "LevelEditor.h"

LevelEditor* LevelEditor::create()
{
	LevelEditor* instance = new LevelEditor();

	instance->autorelease();

	return instance;
}

LevelEditor::LevelEditor()
{
	// TODO: Delete this once decoupled parsing from level parsing
	if (!FadeScene::initWithPhysics())
	{
		throw std::uncaught_exception();
	}
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::onEnter()
{
	FadeScene::onEnter();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();
}

void LevelEditor::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void LevelEditor::initializeListeners()
{
	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(LevelEditor::onKeyPressed, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(LevelEditor::onMouseWheelScroll, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(LevelEditor::onMouseMove, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void LevelEditor::loadLevel(LevelMap* levelMap, Vec2 initPosition)
{
	this->cameraNode = Node::create();
	this->camera = LevelCamera::create();
	this->map = levelMap;

	this->camera->setTarget(this->cameraNode);
	this->camera->setBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));
	this->camera->setScrollOffset(Vec2(128.0f, 96.0f));

	this->cameraNode->setPosition(initPosition);

	this->addChild(InputManager::claimInstance());
	this->addChild(this->map);
	this->addChild(Mouse::create());
	this->addChild(this->cameraNode);
	this->addChild(this->camera);
}

void LevelEditor::update(float dt)
{
	FadeScene::update(dt);
}

void LevelEditor::onMouseMove(EventMouse* event)
{
	Size screenCenter = Director::getInstance()->getVisibleSize() / 2.0f;
	Vec2 mouseDelta = Vec2(event->getCursorX(), event->getCursorY()) - screenCenter;
	Vec2 scrollOffset = this->camera->getScrollOffset();
	Vec2 delta = Vec2::ZERO;

	if (mouseDelta.x < -scrollOffset.x || mouseDelta.x > scrollOffset.x)
	{
		delta.x = (mouseDelta.x - scrollOffset.x);
	}

	if (mouseDelta.y < -scrollOffset.y || mouseDelta.y > scrollOffset.y)
	{
		delta.y = (mouseDelta.y - scrollOffset.y);
	}

	// this->cameraNode->setPosition(this->cameraNode->getPosition() + delta);
}

void LevelEditor::onMouseWheelScroll(EventMouse* event)
{
	float delta = event->getScrollY() * 64.0f;

	Camera::getDefaultCamera()->setPositionZ(Camera::getDefaultCamera()->getPositionZ() + delta);
}

void LevelEditor::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!this->isRunning() || !this->isVisible())
	{
		return;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		NavigationEvents::navigate(NavigationEvents::GameScreen::Pause);
		event->stopPropagation();
		break;
	case EventKeyboard::KeyCode::KEY_GRAVE:
		if (this->getPhysicsWorld()->getDebugDrawMask() == PhysicsWorld::DEBUGDRAW_ALL)
		{
			this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
			Director::getInstance()->setDisplayStats(false);
		}
		else
		{
			this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
			Director::getInstance()->setDisplayStats(true);
		}
		event->stopPropagation();
		break;
	}
}

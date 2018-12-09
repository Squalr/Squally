#include "CombatMap.h"

#include "Engine/Camera/GameCamera.h"

CombatMap* CombatMap::create()
{
	CombatMap* instance = new CombatMap();

	instance->autorelease();

	return instance;
}

CombatMap::CombatMap()
{
	this->mapNode = Node::create();

	if (!IMap::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	this->getPhysicsWorld()->setSpeed(0.0f);

	this->addChild(this->mapNode);
	this->addChild(Mouse::create());
}

CombatMap::~CombatMap()
{
}

void CombatMap::onEnter()
{
	IMap::onEnter();

	GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));
	GameCamera::getInstance()->setTarget(Squally::getInstance(), Vec2(0.0f, 128.0f));
}

void CombatMap::initializePositions()
{
	IMap::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void CombatMap::initializeListeners()
{
	IMap::initializeListeners();
}

void CombatMap::loadMap(SerializableMap* serializableMap)
{
	this->map = serializableMap;
	this->mapNode->removeAllChildren();

	GameUtils::changeParent(this->map, this->mapNode, false);

	GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));
	//GameCamera::getInstance()->setTarget(Squally::getInstance(), Vec2(0.0f, 128.0f));
}

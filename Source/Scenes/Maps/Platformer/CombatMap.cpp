#include "CombatMap.h"

CombatMap* CombatMap::instance = nullptr;

void CombatMap::registerGlobalScene()
{
	if (CombatMap::instance == nullptr)
	{
		CombatMap::instance = new CombatMap();
		CombatMap::instance->autorelease();
		CombatMap::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CombatMap::instance);
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

	CombatMap::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateCombat, [](EventCustom* args)
	{
		GlobalDirector::loadScene(CombatMap::instance);
	}));
}

void CombatMap::loadMap(SerializableMap* serializableMap)
{
	this->map = serializableMap;
	this->mapNode->removeAllChildren();

	GameUtils::changeParent(this->map, this->mapNode, false);

	GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));
	//GameCamera::getInstance()->setTarget(Squally::getInstance(), Vec2(0.0f, 128.0f));
}

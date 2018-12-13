#include "CombatMap.h"

#include "Engine/Camera/GameCamera.h"

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
	if (!MapBase::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	this->getPhysicsWorld()->setSpeed(0.0f);
}

CombatMap::~CombatMap()
{
}

void CombatMap::onEnter()
{
	MapBase::onEnter();

	GameCamera::getInstance()->setScrollOffset(Vec2::ZERO);
	GameCamera::getInstance()->setFollowSpeed(Vec2(0.075f, 0.075f));
}

void CombatMap::initializePositions()
{
	MapBase::initializePositions();
}

void CombatMap::initializeListeners()
{
	MapBase::initializeListeners();

	CombatMap::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateCombat, [](EventCustom* args)
	{
		NavigationEvents::NavigateCombatArgs* combatArgs = static_cast<NavigationEvents::NavigateCombatArgs*>(args->getUserData());

		if (combatArgs != nullptr)
		{
			CombatMap::instance->loadMap(SerializableMap::deserialize(combatArgs->levelFile));
			GlobalDirector::loadScene(CombatMap::instance);
		}
	}));
}

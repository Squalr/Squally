#include "GlobalHackAttributeContainer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListener.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Hackables/HackActivatedAbility.h"
#include "Engine/Hackables/HackableCode.h"

using namespace cocos2d;

GlobalHackAttributeContainer* GlobalHackAttributeContainer::Instance = nullptr;

void GlobalHackAttributeContainer::RegisterGlobalNode()
{
	if (GlobalHackAttributeContainer::Instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->RegisterGlobalNode(GlobalHackAttributeContainer::getInstance());
	}
}

GlobalHackAttributeContainer* GlobalHackAttributeContainer::getInstance()
{
	if (GlobalHackAttributeContainer::Instance == nullptr)
	{
		GlobalHackAttributeContainer::Instance = new GlobalHackAttributeContainer();

		GlobalHackAttributeContainer::Instance->autorelease();
	}

	return GlobalHackAttributeContainer::Instance;
}

GlobalHackAttributeContainer* GlobalHackAttributeContainer::create()
{
	GlobalHackAttributeContainer* Instance = new GlobalHackAttributeContainer();

	Instance->autorelease();

	return Instance;
}

GlobalHackAttributeContainer::GlobalHackAttributeContainer() : super()
{
	this->hackableCodeContainer = Node::create();
	this->hackableAbilityContainer = Node::create();

	this->addChild(this->hackableCodeContainer);
	this->addChild(this->hackableAbilityContainer);
}

GlobalHackAttributeContainer::~GlobalHackAttributeContainer()
{
}

void GlobalHackAttributeContainer::initializeListeners()
{
	super::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(SceneEvents::EventBeforeSceneChangeFinalize, [=](EventCustom* eventCustom)
	{
		HackableBase::HackTimersPaused = false;

		// These can have lambdas that interact with the objects on the map. Bad things happen if we cache between scenes.
		this->hackableAbilityContainer->removeAllChildren();
		this->hackableCodeContainer->removeAllChildren();
		this->abilityMap.clear();
		this->codeMap.clear();
	}));

	this->addGlobalEventListener(EventListenerCustom::create(HackableEvents::EventPauseHackTimers, [=](EventCustom* eventCustom)
	{
		HackableBase::HackTimersPaused = true;
	}));

	this->addGlobalEventListener(EventListenerCustom::create(HackableEvents::EventResumeHackTimers, [=](EventCustom* eventCustom)
	{
		HackableBase::HackTimersPaused = false;
	}));
}

HackableCode* GlobalHackAttributeContainer::GetHackableCode(void* startAddress)
{
	if (GlobalHackAttributeContainer::Instance->codeMap.contains(startAddress))
	{
		return GlobalHackAttributeContainer::Instance->codeMap[startAddress];
	}

	return nullptr;
}

void GlobalHackAttributeContainer::RegisterHackableCode(HackableCode* hackableCode)
{
	if (hackableCode == nullptr)
	{
		return;
	}

	if (!GlobalHackAttributeContainer::Instance->codeMap.contains(hackableCode->codePointer))
	{
		GlobalHackAttributeContainer::Instance->codeMap[hackableCode->codePointer] = hackableCode;
		GlobalHackAttributeContainer::Instance->hackableCodeContainer->addChild(hackableCode);
	}
}

HackActivatedAbility* GlobalHackAttributeContainer::GetHackActivatedAbility(std::string identifier)
{
	if (GlobalHackAttributeContainer::Instance->abilityMap.contains(identifier))
	{
		return GlobalHackAttributeContainer::Instance->abilityMap[identifier];
	}

	return nullptr;
}

void GlobalHackAttributeContainer::RegisterHackActivatedAbility(HackActivatedAbility* hackActivatedAbility)
{
	if (hackActivatedAbility == nullptr)
	{
		return;
	}

	const std::string& identifier = hackActivatedAbility->getHackableIdentifier();

	if (!GlobalHackAttributeContainer::Instance->abilityMap.contains(identifier))
	{
		GlobalHackAttributeContainer::Instance->abilityMap[identifier] = hackActivatedAbility;
		GlobalHackAttributeContainer::Instance->hackableAbilityContainer->addChild(hackActivatedAbility);
	}
}

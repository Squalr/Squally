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

GlobalHackAttributeContainer* GlobalHackAttributeContainer::instance = nullptr;

void GlobalHackAttributeContainer::registerGlobalNode()
{
	if (GlobalHackAttributeContainer::instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(GlobalHackAttributeContainer::getInstance());
	}
}

GlobalHackAttributeContainer* GlobalHackAttributeContainer::getInstance()
{
	if (GlobalHackAttributeContainer::instance == nullptr)
	{
		GlobalHackAttributeContainer::instance = new GlobalHackAttributeContainer();

		GlobalHackAttributeContainer::instance->autorelease();
	}

	return GlobalHackAttributeContainer::instance;
}

GlobalHackAttributeContainer* GlobalHackAttributeContainer::create()
{
	GlobalHackAttributeContainer* instance = new GlobalHackAttributeContainer();

	instance->autorelease();

	return instance;
}

GlobalHackAttributeContainer::GlobalHackAttributeContainer() : super()
{
	this->codeMap = std::map<void*, HackableCode*>();
	this->abilityMap = std::map<std::string, HackActivatedAbility*>();
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
	if (GlobalHackAttributeContainer::instance->codeMap.contains(startAddress))
	{
		return GlobalHackAttributeContainer::instance->codeMap[startAddress];
	}

	return nullptr;
}

void GlobalHackAttributeContainer::RegisterHackableCode(HackableCode* hackableCode)
{
	if (hackableCode == nullptr)
	{
		return;
	}

	if (!GlobalHackAttributeContainer::instance->codeMap.contains(hackableCode->codePointer))
	{
		GlobalHackAttributeContainer::instance->codeMap[hackableCode->codePointer] = hackableCode;
		GlobalHackAttributeContainer::instance->hackableCodeContainer->addChild(hackableCode);
	}
}

HackActivatedAbility* GlobalHackAttributeContainer::GetHackActivatedAbility(std::string identifier)
{
	if (GlobalHackAttributeContainer::instance->abilityMap.contains(identifier))
	{
		return GlobalHackAttributeContainer::instance->abilityMap[identifier];
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

	if (!GlobalHackAttributeContainer::instance->abilityMap.contains(identifier))
	{
		GlobalHackAttributeContainer::instance->abilityMap[identifier] = hackActivatedAbility;
		GlobalHackAttributeContainer::instance->hackableAbilityContainer->addChild(hackActivatedAbility);
	}
}

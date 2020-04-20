#include "GlobalHackAttributeContainer.h"

#include "Engine/GlobalDirector.h"
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
	this->hackablesContainer = Node::create();

	this->addChild(this->hackablesContainer);
}

GlobalHackAttributeContainer::~GlobalHackAttributeContainer()
{
}

HackableCode* GlobalHackAttributeContainer::GetHackableCode(void* startAddress)
{
	if (GlobalHackAttributeContainer::instance->codeMap.find(startAddress) != GlobalHackAttributeContainer::instance->codeMap.end())
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

	if (GlobalHackAttributeContainer::instance->codeMap.find(hackableCode->codePointer) == GlobalHackAttributeContainer::instance->codeMap.end())
	{
		GlobalHackAttributeContainer::instance->codeMap[hackableCode->codePointer] = hackableCode;
		GlobalHackAttributeContainer::instance->hackablesContainer->addChild(hackableCode);
	}
}

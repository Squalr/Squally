#pragma once

#include "Engine/GlobalNode.h"

class HackableCode;

class GlobalHackAttributeContainer : public GlobalNode
{
public:
	static GlobalHackAttributeContainer* create();

	static void registerGlobalNode();
	static HackableCode* GetHackableCode(void* startAddress);
	static void RegisterHackableCode(HackableCode* hackableCode);

protected:
	GlobalHackAttributeContainer();
	virtual ~GlobalHackAttributeContainer();

private:
	typedef GlobalNode super;
	
	static GlobalHackAttributeContainer* getInstance();

	std::map<void*, HackableCode*> codeMap;
	cocos2d::Node* hackablesContainer;

	static GlobalHackAttributeContainer* instance;
};

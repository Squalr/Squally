#pragma once

#include "Engine/GlobalNode.h"

class HackActivatedAbility;
class HackableCode;

class GlobalHackAttributeContainer : public GlobalNode
{
public:
	static GlobalHackAttributeContainer* create();

	static void registerGlobalNode();
	static HackableCode* GetHackableCode(void* startAddress);
	static void RegisterHackableCode(HackableCode* hackableCode);
	static HackActivatedAbility* GetHackActivatedAbility(std::string identifier);
	static void RegisterHackActivatedAbility(HackActivatedAbility* hackActivatedAbility);

protected:
	GlobalHackAttributeContainer();
	virtual ~GlobalHackAttributeContainer();

	void initializeListeners() override;

private:
	typedef GlobalNode super;
	
	static GlobalHackAttributeContainer* getInstance();

	std::map<void*, HackableCode*> codeMap;
	std::map<std::string, HackActivatedAbility*> abilityMap;
	cocos2d::Node* hackableCodeContainer;
	cocos2d::Node* hackableAbilityContainer;

	static GlobalHackAttributeContainer* instance;
};

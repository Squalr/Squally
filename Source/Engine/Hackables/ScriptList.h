#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
}

class ConstantString;
class HackableCode;
class LocalizedLabel;

class ScriptList : public SmartNode
{
public:
	static ScriptList* create(std::function<void(std::string)> onScriptSelect);

	void loadScripts(HackableCode* hackableCode);

protected:
	ScriptList(std::function<void(std::string)> onScriptSelect);
	~ScriptList() = default;

private:
	typedef SmartNode super;

	void initializePositions() override;
	
	LocalizedLabel* titleLabel;
	cocos2d::Node* scriptsNode;
	std::function<void(std::string)> onScriptSelect;
};

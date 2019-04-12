#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class GameState;
class LocalizedLabel;

class AssemblyHelpText : public ComponentBase
{
public:
	static AssemblyHelpText* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	AssemblyHelpText();
	~AssemblyHelpText();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	LocalizedLabel* assemblyHelpLabel;
	ConstantString* operationString;
	ConstantString* sourceString;
	ConstantString* destinationString;
	GameState* gameState;

	static const std::string SourceOperand;
	static const std::string DestOperand;
	static const std::string ManyOperand;
};

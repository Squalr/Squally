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
	AssemblyHelpText();
	virtual ~AssemblyHelpText();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;

	LocalizedLabel* assemblyHelpLabel = nullptr;
	ConstantString* operationString = nullptr;
	ConstantString* sourceString = nullptr;
	ConstantString* destinationString = nullptr;
	GameState* gameState = nullptr;

	static const std::string SourceOperand;
	static const std::string DestOperand;
	static const std::string ManyOperand;
};

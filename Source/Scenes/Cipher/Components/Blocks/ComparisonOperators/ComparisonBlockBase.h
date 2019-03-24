#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class LocalizedString;

class ComparisonBlockBase : public BlockBase
{
protected:
	ComparisonBlockBase(BlockType blockType, std::string iconResource, LocalizedString* localizedString);
	~ComparisonBlockBase();

	void execute(std::function<void()> onExecuteComplete) override;
	char compute() override;
	virtual bool compare(char inputA, char inputB) = 0;

private:
	typedef BlockBase super;
};

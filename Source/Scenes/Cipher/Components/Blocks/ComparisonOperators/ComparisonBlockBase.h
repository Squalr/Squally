#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class LocalizedString;

class ComparisonBlockBase : public BlockBase
{
protected:
	ComparisonBlockBase(BlockType blockType, std::string iconResource, LocalizedString* localizedString);
	virtual ~ComparisonBlockBase();

	void execute(std::function<void()> onExecuteComplete) override;
	unsigned char compute() override;
	virtual bool compare(unsigned char inputA, unsigned char inputB) = 0;

private:
	typedef BlockBase super;
};

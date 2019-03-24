#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class GreaterThanOrEqualsBlock : public BlockBase
{
public:
	static GreaterThanOrEqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	GreaterThanOrEqualsBlock(BlockType blockType);
	~GreaterThanOrEqualsBlock();

	void onEnter() override;
	void initializePositions() override;
};

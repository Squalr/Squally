#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class EqualsBlock : public BlockBase
{
public:
	static EqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	EqualsBlock(BlockType blockType);
	~EqualsBlock();

	void onEnter() override;
	void initializePositions() override;
};

#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class DivBlock : public BlockBase
{
public:
	static DivBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	DivBlock(BlockType blockType);
	~DivBlock();

	void onEnter() override;
	void initializePositions() override;
};

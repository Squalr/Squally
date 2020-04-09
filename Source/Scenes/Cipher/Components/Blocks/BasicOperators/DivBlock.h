#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class DivBlock : public BlockBase
{
public:
	static DivBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	DivBlock(BlockType blockType);
	virtual ~DivBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};

#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ShrBlock : public BlockBase
{
public:
	static ShrBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	ShrBlock(BlockType blockType);
	virtual ~ShrBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};

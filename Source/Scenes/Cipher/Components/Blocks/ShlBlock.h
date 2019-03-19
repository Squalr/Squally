#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ShlBlock : public BlockBase
{
public:
	static ShlBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	ShlBlock(BlockType blockType);
	~ShlBlock();

	void onEnter() override;
	void initializePositions() override;
};

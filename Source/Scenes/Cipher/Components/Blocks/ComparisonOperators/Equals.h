#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class Equals : public BlockBase
{
public:
	static Equals* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	Equals(BlockType blockType);
	~Equals();

	void onEnter() override;
	void initializePositions() override;
};

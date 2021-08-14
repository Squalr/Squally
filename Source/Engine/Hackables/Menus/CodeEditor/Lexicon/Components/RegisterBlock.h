#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class ConstantString;

class RegisterBlock : public SmartNode
{
public:
	static RegisterBlock* create();

	void clearHighlights();
	void highlightEax(bool isDest);
	void highlightEbx(bool isDest);
	void highlightEcx(bool isDest);
	void highlightEdx(bool isDest);
	void highlightEdi(bool isDest);
	void highlightEsi(bool isDest);
	void highlightEbp(bool isDest);
	void highlightEsp(bool isDest);
	void highlightEip(bool isDest);
	void highlightEaxPtr(bool isDest, int offset);
	void highlightEbxPtr(bool isDest, int offset);
	void highlightEcxPtr(bool isDest, int offset);
	void highlightEdxPtr(bool isDest, int offset);
	void highlightEdiPtr(bool isDest, int offset);
	void highlightEsiPtr(bool isDest, int offset);
	void highlightEbpPtr(bool isDest, int offset);
	void highlightEspPtr(bool isDest, int offset);
	void highlightEipPtr(bool isDest, int offset);

	void initEax(unsigned long long eax, std::vector<unsigned long long> values = { });
	void initEbx(unsigned long long ebx, std::vector<unsigned long long> values = { });
	void initEcx(unsigned long long ecx, std::vector<unsigned long long> values = { });
	void initEdx(unsigned long long edx, std::vector<unsigned long long> values = { });
	void initEdi(unsigned long long edi, std::vector<unsigned long long> values = { });
	void initEsi(unsigned long long esi, std::vector<unsigned long long> values = { });
	void initEbp(unsigned long long ebp, std::vector<unsigned long long> values = { });
	void initEsp(unsigned long long esp, std::vector<unsigned long long> values = { });
	void initEip(unsigned long long eip, std::vector<unsigned long long> values = { });

	void setEax(unsigned long long eax);
	void setEbx(unsigned long long ebx);
	void setEcx(unsigned long long ecx);
	void setEdx(unsigned long long edx);
	void setEdi(unsigned long long edi);
	void setEsi(unsigned long long esi);
	void setEbp(unsigned long long ebp);
	void setEsp(unsigned long long esp);
	void setEip(unsigned long long eip);

	void setEaxPtr(unsigned long long value, int offset);
	void setEbxPtr(unsigned long long value, int offset);
	void setEcxPtr(unsigned long long value, int offset);
	void setEdxPtr(unsigned long long value, int offset);
	void setEdiPtr(unsigned long long value, int offset);
	void setEsiPtr(unsigned long long value, int offset);
	void setEbpPtr(unsigned long long value, int offset);
	void setEspPtr(unsigned long long value, int offset);
	void setEipPtr(unsigned long long value, int offset);

	unsigned long long getEax();
	unsigned long long getEbx();
	unsigned long long getEcx();
	unsigned long long getEdx();
	unsigned long long getEdi();
	unsigned long long getEsi();
	unsigned long long getEbp();
	unsigned long long getEsp();
	unsigned long long getEip();

	unsigned long long getEaxPtr(int offset);
	unsigned long long getEbxPtr(int offset);
	unsigned long long getEcxPtr(int offset);
	unsigned long long getEdxPtr(int offset);
	unsigned long long getEdiPtr(int offset);
	unsigned long long getEsiPtr(int offset);
	unsigned long long getEbpPtr(int offset);
	unsigned long long getEspPtr(int offset);
	unsigned long long getEipPtr(int offset);

protected:
	RegisterBlock();
	virtual ~RegisterBlock();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void highlightSource(cocos2d::Vec2 position);
	void highlightDest(cocos2d::Vec2 position);

	struct Register
	{
		bool initialized = false;
		unsigned long long currentValue = 0;
		unsigned long long initialValue = 0;
		std::vector<unsigned long long> initialValues;
		std::vector<unsigned long long> currentValues;

		Register() { }
		Register(unsigned long long currentValue, unsigned long long initialValue, std::vector<unsigned long long> initialValues, std::vector<unsigned long long> currentValues) :
			initialized(true), currentValue(currentValue), initialValue(initialValue), initialValues(initialValues), currentValues(currentValues) {}
	};

	void addToData(unsigned long long value, int index, Node* node, std::vector<ConstantString*>* strings, std::vector<LocalizedLabel*>* labels);

	cocos2d::Sprite* registerBlock = nullptr;
	LocalizedLabel* titleLabel = nullptr;
	LocalizedLabel* memoryTitleLabel = nullptr;
	LocalizedLabel* eaxLabel = nullptr;
	LocalizedLabel* ebxLabel = nullptr;
	LocalizedLabel* ecxLabel = nullptr;
	LocalizedLabel* edxLabel = nullptr;
	LocalizedLabel* ediLabel = nullptr;
	LocalizedLabel* esiLabel = nullptr;
	LocalizedLabel* ebpLabel = nullptr;
	LocalizedLabel* espLabel = nullptr;
	LocalizedLabel* eipLabel = nullptr;
	cocos2d::Node* eaxPtrNode = nullptr;
	cocos2d::Node* ebxPtrNode = nullptr;
	cocos2d::Node* ecxPtrNode = nullptr;
	cocos2d::Node* edxPtrNode = nullptr;
	cocos2d::Node* ediPtrNode = nullptr;
	cocos2d::Node* esiPtrNode = nullptr;
	cocos2d::Node* ebpPtrNode = nullptr;
	cocos2d::Node* espPtrNode = nullptr;
	cocos2d::Node* eipPtrNode = nullptr;
	cocos2d::Sprite* destSelector = nullptr;
	cocos2d::Sprite* srcSelector = nullptr;

	std::vector<ConstantString*> eaxPtrStrings;
	std::vector<ConstantString*> ebxPtrStrings;
	std::vector<ConstantString*> ecxPtrStrings;
	std::vector<ConstantString*> edxPtrStrings;
	std::vector<ConstantString*> ediPtrStrings;
	std::vector<ConstantString*> esiPtrStrings;
	std::vector<ConstantString*> ebpPtrStrings;
	std::vector<ConstantString*> espPtrStrings;
	std::vector<ConstantString*> eipPtrStrings;

	std::vector<LocalizedLabel*> eaxPtrLabels;
	std::vector<LocalizedLabel*> ebxPtrLabels;
	std::vector<LocalizedLabel*> ecxPtrLabels;
	std::vector<LocalizedLabel*> edxPtrLabels;
	std::vector<LocalizedLabel*> ediPtrLabels;
	std::vector<LocalizedLabel*> esiPtrLabels;
	std::vector<LocalizedLabel*> ebpPtrLabels;
	std::vector<LocalizedLabel*> espPtrLabels;
	std::vector<LocalizedLabel*> eipPtrLabels;

	ConstantString* eaxString = nullptr;
	ConstantString* ebxString = nullptr;
	ConstantString* ecxString = nullptr;
	ConstantString* edxString = nullptr;
	ConstantString* ediString = nullptr;
	ConstantString* esiString = nullptr;
	ConstantString* ebpString = nullptr;
	ConstantString* espString = nullptr;
	ConstantString* eipString = nullptr;

	Register eax;
	Register ebx;
	Register ecx;
	Register edx;
	Register edi;
	Register esi;
	Register ebp;
	Register esp;
	Register eip;

	static const float RegisterPtrSpacing;
	static const cocos2d::Vec2 SelectorRegOffset;
};

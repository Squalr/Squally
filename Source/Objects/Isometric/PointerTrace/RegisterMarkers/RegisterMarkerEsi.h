#pragma once

#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarker.h"

class RegisterMarkerEsi : public RegisterMarker
{
public:
	static RegisterMarkerEsi* create();

protected:
	RegisterMarkerEsi();
	virtual ~RegisterMarkerEsi();

	int getRegisterIndex() override;

private:
	typedef RegisterMarker super;
};

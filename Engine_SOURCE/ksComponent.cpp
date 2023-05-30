#include "ksComponent.h"


namespace ks
{
	Component::Component(eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}
	Component::~Component()
	{
	}
}

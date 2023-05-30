#include "ksLight.h"
#include "ksTransform.h"
#include "ksGameObject.h"
#include "ksRenderer.h"

namespace ks
{
	Light::Light()
		: Component(eComponentType::Light)
	{

	}

	Light::~Light()
	{

	}

	void Light::Initalize()
	{

	}

	void Light::Update()
	{

	}

	void Light::FixedUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 position = tr->GetPosition();
		mAttribute.position = Vector4(position.x, position.y, position.z, 1.0f);
		mAttribute.direction = Vector4(tr->Right().x, tr->Right().y, tr->Right().z, 1.0f);

		renderer::lights.push_back(mAttribute);
	}

	void Light::Render()
	{

	}
}

#pragma once

#include "ksComponent.h"
#include "ksMesh.h"
#include "ksMaterial.h"
#include "ksBaseRenderer.h"

using namespace ks::graphics;
namespace ks
{
	class SpriteRenderer : public BaseRenderer
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}

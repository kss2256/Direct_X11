#include "ksSpriteRenderer.h"
#include "ksGameObject.h"
#include "ksTransform.h"
#include "ksAnimator.h"

namespace ks
{
	SpriteRenderer::SpriteRenderer()
		: BaseRenderer(eComponentType::SpriteRenderer)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initalize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::FixedUpdate()
	{
	}

	void SpriteRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		GetMaterial()->Bind();
		GetMesh()->BindBuffer();

		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator)
		{
			animator->Binds();
		}

		GetMesh()->Render();
		GetMaterial()->Clear();

		if (animator)
		{
			animator->Clear();
		}

	}

}

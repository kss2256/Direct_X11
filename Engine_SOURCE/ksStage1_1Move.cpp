#include "ksStage1_1Move.h"
#include "ksPlayer.h"
#include "ksPlayerAttack.h"
#include "ksTransform.h"
#include "ksTime.h"
#include "ksAnimator.h"
#include "ksResources.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksSpriteRenderer.h"
#include "ksFadeEffect.h"
#include "ksTime.h"
#include "ksStage1_1.h"

namespace ks
{

	Player* Stage1_1Move::mTarget = nullptr;
	bool Stage1_1Move::mFadeEffect = false;
	bool Stage1_1Move::mFadeEffectCheak = false;
	bool Stage1_1Move::mGroundExecuted = false;

	Stage1_1Move::Stage1_1Move()
		: mGroundStage(eGroundStage::Ground1)
		//, mFadeEffect(false)
		//, mFadeEffectCheak(false)
		//, mGroundExecuted(false)

	{

		mTransform = GetComponent<Transform>();

		mCollider = AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		AddComponent<SpriteRenderer>();


	}
	Stage1_1Move::~Stage1_1Move()
	{

	}


	void Stage1_1Move::Initalize()
	{
		AddComponent<FadeEffect>();
		GetComponent<FadeEffect>()->Initalize();
	

		GameObject::Initalize();
	}

	void Stage1_1Move::Update()
	{


		mGroundStage = mTarget->GetGroundStage();

		if (mFadeEffect)
		{			
			mTransform->SetScale(Vector3(50.0f, 50.0f, 2.0f));
			GetComponent<FadeEffect>()->Fade_Out();
			mFadeEffectCheak = true;
			mFadeEffect = false;
			mTime = 0.f;
		}
		if (mFadeEffectCheak)
		{

			mTime += Time::DeltaTime();

			if (mTime >= 1.5f)
			{
				switch (mGroundStage)
				{
				case ks::enums::eGroundStage::Start:
				{
					if (!mGroundExecuted)
					{
						mTransform->SetPosition(Vector3(35.0f, 0.0f, 2.0f));
						GetComponent<FadeEffect>()->Fade_In();
						mTarget->GetComponent<Transform>()->SetPosition(Vec3(35.0f, 0.0f, 2.0f));
						mTarget->SetGroundStage(eGroundStage::Ground1);
						mGroundStage = mTarget->GetGroundStage();
						mGroundExecuted = true;
					}
				}
				break;
				case ks::enums::eGroundStage::Ground1:
				{
					if (!mGroundExecuted)
					{
						mTransform->SetPosition(Vector3(70.0f, -10.0f, 2.0f));
						GetComponent<FadeEffect>()->Fade_In();
						mTarget->GetComponent<Transform>()->SetPosition(Vec3(70.0f, -10.0f, 2.0f));
						mTarget->SetGroundStage(eGroundStage::Ground2);
						mGroundStage = mTarget->GetGroundStage();
						mGroundExecuted = true;
					}

					if (mTime >= 3.0f)
					{						
						Stage1_1* stage = nullptr;
						stage->SetKeyCheak(false);

						mTime = 0.f;
						mFadeEffectCheak = false;
						mGroundExecuted = false;
					}

				}
				break;
				case ks::enums::eGroundStage::Ground2:
				{
					if (!mGroundExecuted)
					{
						mTransform->SetPosition(Vector3(118.f, -3.7f, 2.0f));
						GetComponent<FadeEffect>()->Fade_In();
						mTarget->GetComponent<Transform>()->SetPosition(Vec3(118.f, -3.7f, 2.0f));
						mTarget->SetGroundStage(eGroundStage::Ground3);
						mGroundStage = mTarget->GetGroundStage();
						mGroundExecuted = true;
					}
					if (mTime >= 3.0f)
					{
						Stage1_1* stage = nullptr;
						stage->SetKeyCheak(false);
						mTime = 0.f;
						mFadeEffectCheak = false;
						mGroundExecuted = false;
					}
				}
				break;
				case ks::enums::eGroundStage::Ground3:
				{
					if (!mGroundExecuted)
					{
						mTransform->SetPosition(Vector3(140.0f, -10.5f, 2.0f));
						GetComponent<FadeEffect>()->Fade_In();
						mTarget->GetComponent<Transform>()->SetPosition(Vec3(140.0f, -10.5f, 2.0f));
						mTarget->SetGroundStage(eGroundStage::Ground4);
						mGroundStage = mTarget->GetGroundStage();
						mGroundExecuted = true;
					}
					if (mTime >= 3.0f)
					{
						Stage1_1* stage = nullptr;
						stage->SetKeyCheak(false);
						mTime = 0.f;
						mFadeEffectCheak = false;
						mGroundExecuted = false;
					}
				}
				break;
				case ks::enums::eGroundStage::Ground4:
				{
					if (!mGroundExecuted)
					{
						mTransform->SetPosition(Vector3(175.1f, -10.4f, 2.0f));
						GetComponent<FadeEffect>()->Fade_In();
						mTarget->GetComponent<Transform>()->SetPosition(Vec3(175.1f, -10.4f, 2.0f));
						mTarget->SetGroundStage(eGroundStage::Ground5);
						mGroundStage = mTarget->GetGroundStage();
						mGroundExecuted = true;
					}
					if (mTime >= 3.0f)
					{
						Stage1_1* stage = nullptr;
						stage->SetKeyCheak(false);
						mTime = 0.f;
						mFadeEffectCheak = false;
						mGroundExecuted = false;
					}
				}
				break;
				case ks::enums::eGroundStage::Ground5:
				{
					if (!mGroundExecuted)
					{
						
						mTransform->SetPosition(Vector3(210.0f, 0.0f, 2.0f));
						GetComponent<FadeEffect>()->Fade_In();
						mTarget->GetComponent<Transform>()->SetPosition(Vec3(210.0f, 0.0f, 2.0f));
						mTarget->SetGroundStage(eGroundStage::Ground6);
				
						mGroundStage = mTarget->GetGroundStage();
						mGroundExecuted = true;
					}
					if (mTime >= 3.0f)
					{
						Stage1_1* stage = nullptr;
						stage->SetKeyCheak(false);						
						mTime = 0.f;
						mFadeEffectCheak = false;
						mGroundExecuted = false;
					}
				}
				break;
				case ks::enums::eGroundStage::Ground6:
				{
					if (!mGroundExecuted)
					{
						mTransform->SetPosition(Vector3(245.1f, -10.2f, 2.0f));
						GetComponent<FadeEffect>()->Fade_In();
						mTarget->GetComponent<Transform>()->SetPosition(Vec3(245.1f, -10.2f, 2.0f));
						mTarget->SetGroundStage(eGroundStage::Ground7);
						mGroundStage = mTarget->GetGroundStage();
						mGroundExecuted = true;
					}
					if (mTime >= 3.0f)
					{
						Stage1_1* stage = nullptr;
						stage->SetKeyCheak(false);
						stage->SetKey(false);
						mTime = 0.f;
						mFadeEffectCheak = false;
						mGroundExecuted = false;
					}
				}
				break;
				case ks::enums::eGroundStage::Ground7:
				{
					if (!mGroundExecuted)
					{
						mTransform->SetPosition(Vector3(279.8f, -10.1f, 2.0f));
						GetComponent<FadeEffect>()->Fade_In();
						mTarget->GetComponent<Transform>()->SetPosition(Vec3(279.8f, -10.1f, 2.0f));
						mTarget->SetGroundStage(eGroundStage::Ground8);
						mGroundStage = mTarget->GetGroundStage();
						mGroundExecuted = true;
					}
					if (mTime >= 3.0f)
					{
						Stage1_1* stage = nullptr;
						stage->SetKeyCheak(false);
						mTime = 0.f;
						mFadeEffectCheak = false;
						mGroundExecuted = false;
					}
				}
				break;
				case ks::enums::eGroundStage::Ground8:
				{
					if (!mGroundExecuted)
					{
						mTransform->SetPosition(Vector3(314.4f, -8.5f, 2.0f));
						GetComponent<FadeEffect>()->Fade_In();
						mTarget->GetComponent<Transform>()->SetPosition(Vec3(314.4f, -8.5f, 2.0f));
						mTarget->SetGroundStage(eGroundStage::Ground9);
						mGroundStage = mTarget->GetGroundStage();
						mGroundExecuted = true;
					}
					if (mTime >= 3.0f)
					{
						Stage1_1* stage = nullptr;
						stage->SetKeyCheak(false);
						mTime = 0.f;
						mFadeEffectCheak = false;
						mGroundExecuted = false;
					}
				}
				break;
				case ks::enums::eGroundStage::Ground9:
				{
					if (!mGroundExecuted)
					{
						//여긴 끝나는 방 다음 으로 이동할거
						//mTransform->SetPosition(Vector3(300.7f, 0.3f, 2.0f));
						GetComponent<FadeEffect>()->Fade_In();
						//mTarget->GetComponent<Transform>()->SetPosition(Vec3(300.7f, 0.3f, 2.0f));
						mTarget->SetGroundStage(eGroundStage::Boss);
						mGroundStage = mTarget->GetGroundStage();
						mGroundExecuted = true;
					}
					if (mTime >= 3.0f)
					{
						Stage1_1* stage = nullptr;
						stage->SetKeyCheak(false);
						mTime = 0.f;
						mFadeEffectCheak = false;
						mGroundExecuted = false;
					}
				}
				break;
				case ks::enums::eGroundStage::Boss:
				{
					if (!mGroundExecuted)
					{
						mTransform->SetPosition(Vector3(300.7f, 0.3f, 2.0f));
						GetComponent<FadeEffect>()->Fade_In();
						mTarget->GetComponent<Transform>()->SetPosition(Vec3(300.7f, 0.3f, 2.0f));
						mTarget->SetGroundStage(eGroundStage::Boss);
						mGroundStage = mTarget->GetGroundStage();
						mGroundExecuted = true;
					}
					if (mTime >= 3.0f)
					{
						Stage1_1* stage = nullptr;
						stage->SetKeyCheak(false);
						mTime = 0.f;
						mFadeEffectCheak = false;
						mGroundExecuted = false;
					}

				}
				break;
				}


			}

		}


		if(mFadeEffectCheak == false)
		{
			switch (mGroundStage)
			{
			case ks::enums::eGroundStage::Start:
			{
				
			}
			break;
			case ks::enums::eGroundStage::Ground1:
			{
				Transform* tr = GetComponent<Transform>();
				tr->SetPosition(Vector3(35.f, 11.0f, 2.0f));
				mCollider->SetSize(Vector2(0.1f, 0.025f));
			}
			break;
			case ks::enums::eGroundStage::Ground2:
			{
				Transform* tr = GetComponent<Transform>();
				tr->SetPosition(Vector3(55.6f, -3.7f, 2.0f));
				mCollider->SetSize(Vector2(0.025f, 0.08f));
			}
			break;
			case ks::enums::eGroundStage::Ground3:
			{
				Transform* tr = GetComponent<Transform>();
				tr->SetPosition(Vector3(104.9f, 10.8f, 2.0f));
				mCollider->SetSize(Vector2(0.1f, 0.025f));
			}
				break;
			case ks::enums::eGroundStage::Ground4:
			{
				Transform* tr = GetComponent<Transform>();
				tr->SetPosition(Vector3(140.f, 10.7f, 2.0f));
				mCollider->SetSize(Vector2(0.1f, 0.025f));
			}
				break;
			case ks::enums::eGroundStage::Ground5:
			{
				Transform* tr = GetComponent<Transform>();
				tr->SetPosition(Vector3(174.9f, 10.8f, 2.0f));
				mCollider->SetSize(Vector2(0.1f, 0.025f));
			}
				break;
			case ks::enums::eGroundStage::Ground6:
			{
				Transform* tr = GetComponent<Transform>();
				tr->SetPosition(Vector3(210.0f, 10.6f, 2.0f));
				mCollider->SetSize(Vector2(0.08f, 0.025f));
			}
				break;
			case ks::enums::eGroundStage::Ground7:
			{
				Transform* tr = GetComponent<Transform>();
				tr->SetPosition(Vector3(245.f, 10.5f, 2.0f));
				mCollider->SetSize(Vector2(0.08f, 0.025f));
			}
				break;
			case ks::enums::eGroundStage::Ground8:
			{
				Transform* tr = GetComponent<Transform>();
				tr->SetPosition(Vector3(294.6f, 0.2f, 2.0f));
				mCollider->SetSize(Vector2(0.04f, 0.08f));
			}
				break;
			case ks::enums::eGroundStage::Ground9:
			{
				Transform* tr = GetComponent<Transform>();
				tr->SetPosition(Vector3(342.8f, 5.9f, 2.0f));
				mCollider->SetSize(Vector2(0.04f, 0.08f));
			}
				break;
			}
		}



		GameObject::Update();
	}

	void Stage1_1Move::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Stage1_1Move::Render()
	{

		GameObject::Render();
	}

}

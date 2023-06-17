#include "ksStage1_1.h"
#include "ksTime.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksMeshRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksDiary.h"
#include "ksObject.h"
#include "ksStart_Effect.h"
#include "ksObject.h"
#include "ksCollider2D.h"
#include "ksInput.h"
#include "ksBoss_Ent.h"
#include "ksBoss_Flime.h"
#include "ksForest_Fairy.h"
#include "ksSnake_Green.h"
#include "ksSlime_Green.h"
#include "ksBossLayout.h"
#include "ksBossTpMeter.h"
#include "ksAudioClip.h"


using namespace ks::graphics;

namespace ks
{

	GameObject* Stage1_1::mTarget = nullptr;
	bool Stage1_1::mKey = false;
	bool Stage1_1::mKeyCheak = false;
	bool Stage1_1::m_bSoundCheak = false;
	UINT Stage1_1::mKeyCount = 0;
	Stage_Step Stage1_1::mStep = Stage_Step::None;
	Vec3 Stage1_1::mMoveCam = Vec3::Zero;
	Vec3 Stage1_1::mEndCam = Vec3::Zero;

	Stage1_1::Stage1_1()
		: mFlimeTime(0.f)
		
	{


	}

	Stage1_1::~Stage1_1()
	{
	}


	void Stage1_1::Initalize()
	{
		//std::shared_ptr<Texture> ground1 = Resources::Load<Texture>(L"Ground1", L"Map\\Ground\\Ground1.png");
		std::shared_ptr<Texture> ground1 = Resources::Load<Texture>(L"Ground1", L"Map\\Ground\\Ground1.png");
		std::shared_ptr<Texture> ground2 = Resources::Load<Texture>(L"Ground2", L"Map\\Ground\\Ground2.png");
		std::shared_ptr<Texture> ground3 = Resources::Load<Texture>(L"Ground3", L"Map\\Ground\\Ground3.png");
		std::shared_ptr<Texture> ground4 = Resources::Load<Texture>(L"Ground4", L"Map\\Ground\\Ground4.png");
		std::shared_ptr<Texture> ground5 = Resources::Load<Texture>(L"Ground5", L"Map\\Ground\\Ground5.png");
		std::shared_ptr<Texture> ground6 = Resources::Load<Texture>(L"Ground6", L"Map\\Ground\\Ground6.png");
		std::shared_ptr<Texture> ground7 = Resources::Load<Texture>(L"Ground7", L"Map\\Ground\\Ground7.png");
		std::shared_ptr<Texture> ground8 = Resources::Load<Texture>(L"Ground8", L"Map\\Ground\\Ground8.png");
		std::shared_ptr<Texture> ground9 = Resources::Load<Texture>(L"Ground9", L"Map\\Ground\\Ground9.png");
		std::shared_ptr<Texture> start = Resources::Load<Texture>(L"Start", L"Map\\Ground\\Start.png");




		switch (mGroundStage)
		{
		case ks::enums::eGroundStage::Ground1:
		{
			createGround(L"Ground1", ground1);
			Start_Effect* effect = object::Instantiate<Start_Effect>(eLayerType::Player_Afterimage);
		}
			break;
		case ks::enums::eGroundStage::Ground2:
			createGround(L"Ground2", ground2);
			break;
		case ks::enums::eGroundStage::Ground3:
			createGround(L"Ground3", ground3);
			break;
		case ks::enums::eGroundStage::Ground4:
			createGround(L"Ground4", ground4);
			break;
		case ks::enums::eGroundStage::Ground5:
			createGround(L"Ground5", ground5);
			break;
		case ks::enums::eGroundStage::Ground6:
		{
			createGround(L"Ground6", ground1);
			Start_Effect* effect = object::Instantiate<Start_Effect>(eLayerType::Player_Afterimage);
			effect->GetComponent<Transform>()->SetPosition(Vec3(210.f, 0.0f, 1.0f));
		}
			break;
		case ks::enums::eGroundStage::Ground7:
			createGround(L"Ground7", ground7);
			break;
		case ks::enums::eGroundStage::Ground8:
			createGround(L"Ground8", ground8);
			break;
		case ks::enums::eGroundStage::Ground9:
			createGround(L"Ground9", ground9);
			break;
		case ks::enums::eGroundStage::Start:
		{
			createGround(L"Start", start);
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vec3(37.f, 35.f, 1.0f));
			createDiary();

			//mCollider = AddComponent<Collider2D>();
			//
			////Collider2D* collider = missile->GetComponent<Collider2D>();
			//mCollider->SetType(eColliderType::Rect);
			//mCollider->SetSize(Vec2(0.4f, 0.36f));
			//mCollider->SetCenter(Vec2(0.0f, 1.6f));
			////mCollider->SetCenter(Vec2(0.0f, 0.0f));
			



		}
			break;

		}

		

		GameObject::Initalize();
	}

	void Stage1_1::Update()
	{

		if (mTarget == nullptr)
			return;

		Player* player = (Player*)mTarget;
		mGroundStage = player->GetGroundStage();
		


		switch (mGroundStage)
		{
		case ks::enums::eGroundStage::Ground1:
		{
			//시작 지점, 아이템 3개 구비 해두고 먹으면 Key 는 트루로 변경.
			//아이템 먹으면 트루!
			if(!m_bSoundCheak)
			{
				std::shared_ptr<AudioClip> booksound = Resources::Load<AudioClip>
					(L"Stage_1", L"D:\\50\\Resources\\Sound\\Stage_1.ogg");
				booksound->SetLoop(true);
				booksound->Play(0.3f);
				m_bSoundCheak = true;
			}
			if (!mKey)
			{							
				range_In(Vec4(26.2f, 42.2f, 6.0f, -6.7f));
			}

			if (mKeyCount == 3)
			{
				mKey = true;
				//mainCamera->SetShock(true);
				//mainCamera->SetShockDuration(0.7f);
				mKeyCount = 0;
			}


		}
			break;
		case ks::enums::eGroundStage::Ground2:
		{			
			if (!mKeyCheak)
			{
				mSlime->GetComponent<Transform>()->SetPosition(Vec3(74.2f, 0.2f, 2.0f));
				mSlime_Two->GetComponent<Transform>()->SetPosition(Vec3(66.6f, 0.8f, 2.0f));
				mSnake->GetComponent<Transform>()->SetPosition(Vec3(74.6f, 2.8f, 2.0f));
				//시작지점에서 이동 하면 Ckeak , 몬스터 인식 true key = false , 몬스터 전부 처치 후 key = true;
				Vec3 pos = mTarget->GetComponent<Transform>()->GetPosition();
				if (pos.y >= -7.54f)
				{	
					mSlime->SetDetection(true);
					mSlime_Two->SetDetection(true);
					mSnake->SetDetection(true);

					mKeyCheak = true;
					mKey = false;
				}
			}			

			if(mKeyCount == 3)
			{
				mKey = true;
				mainCamera->SetShock(true);
				mainCamera->SetShockDuration(0.7f);
				mKeyCount = 0;
			}


			if (!mKey)
			{
				range_In(Vec4(61.0f, 78.96f, 2.37f, -9.8f));
			}
		}
			break;
		case ks::enums::eGroundStage::Ground3:
		{
			if (!mKeyCheak)
			{
				//시작지점에서 이동 하면 Ckeak = true , key = false , 장비 보여주고 전부 먹으면 key = true;
				Vec3 pos = mTarget->GetComponent<Transform>()->GetPosition();
				if (pos.x <= 113.9f)
				{
					mKeyCheak = true;
					mKey = false;
					mSlime->resurrection();
					mSlime_Two->resurrection();
					mSnake->resurrection();
					mSnake_Two->resurrection();
				}
			}

			if (mKeyCount == 3)
			{
				mKey = true;
				//mainCamera->SetShock(true);
				//mainCamera->SetShockDuration(0.7f);
				mKeyCount = 0;
			}

			if (Input::GetKeyDown(eKeyCode::ESC))
				mKey = true;
			if (!mKey)
			{
				range_In(Vec4(96.06f, 114.0f, 2.21f, -9.31f));
			}

		}
			break;
		case ks::enums::eGroundStage::Ground4:
		{
			if (!mKeyCheak)
			{
				mSlime->GetComponent<Transform>()->SetPosition(Vec3(135.0f, 1.4f, 2.0f));
				mSlime_Two->GetComponent<Transform>()->SetPosition(Vec3(146.5f, -4.1f, 2.0f));
				mSnake->GetComponent<Transform>()->SetPosition(Vec3(133.5f, -1.1f, 2.0f));
				mSnake_Two->GetComponent<Transform>()->SetPosition(Vec3(143.2f, 2.0f, 2.0f));

				//시작지점에서 이동 하면 Ckeak , 몬스터 인식 true key = false , 몬스터 전부 처치 후 key = true;
				Vec3 pos = mTarget->GetComponent<Transform>()->GetPosition();
				if (pos.y >= -7.92f)
				{					
					mSlime->SetDetection(true);			
					mSlime_Two->SetDetection(true);
					mSnake->SetDetection(true);
					mSnake_Two->SetDetection(true);
					mKeyCheak = true;
					mKey = false;
				}
			}
			if (mKeyCount == 4)
			{
				mKey = true;
				mainCamera->SetShock(true);
				mainCamera->SetShockDuration(0.7f);
				mKeyCount = 0;
			}

			if (!mKey)
			{
				range_In(Vec4(131.0f, 148.9f, 2.37f, -9.17f));
			}
		}

			break;
		case ks::enums::eGroundStage::Ground5:
		{
			//꽃 괴물	175  -0.5
			if (!mKeyCheak)
			{
				//시작지점에서 이동 하면 Ckeak , 몬스터 인식 true key = false , 몬스터 전부 처치 후 key = true;
				Vec3 pos = mTarget->GetComponent<Transform>()->GetPosition();
				if (pos.y >= -8.2f)
				{	
					if (!m_bSoundCheak)
					{

						std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Stage_1");
						sound->Stop();

						std::shared_ptr<AudioClip> booksound = Resources::Load<AudioClip>
							(L"Boss_Flime_Battle", L"D:\\50\\Resources\\Sound\\Boss_Flime_Battle.ogg");
						booksound->SetLoop(true);
						booksound->Play();
						m_bSoundCheak = true;
					}

					flime_Start();
					
				}
			}

			if (mKeyCount == 1)
			{
				m_bSoundCheak = false;
				mBossMeter->Death();
				mBossLayout->Death();
				
				mKey = true;
				mainCamera->SetShock(true);
				mainCamera->SetShockDuration(0.7f);
				mKeyCount = 0;

				if (!m_bSoundCheak)
				{
					std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Stage_1");
					sound->SetLoop(true);
					sound->Play(0.5);

					std::shared_ptr<AudioClip> booksound = Resources::Find<AudioClip>(L"Boss_Flime_Battle");
					booksound->Stop();
					m_bSoundCheak = true;
				}
			}

			if (!mKey)
			{
				//range_In(Vec4(168.3f, 183.0f, 7.73f, -6.2f));
				range_In(Vec4(168.3f, 183.0f, 7.73f, -8.2f));
			}

		}
			break;
		case ks::enums::eGroundStage::Ground6:
		{



			//아이템 먹으면 트루!
			if (!mKeyCheak)
			{
				if (Input::GetKeyDown(eKeyCode::ESC))
				{
					mSlime->resurrection();
					mSnake->resurrection();
					mSnake_Two->resurrection();
					mFairy->resurrection();


					mKeyCheak = true;	
					mKey = true;
				}
			}
			if (!mKey)
			{
				range_In(Vec4(201.0f, 217.0f, 5.58f, -6.6f));
			}
		}
			break;
		case ks::enums::eGroundStage::Ground7:
		{
			if (!mKeyCheak)
			{

				mSlime->GetComponent<Transform>()->SetPosition(Vec3(238.8f, 0.53f, 2.0f));
				mSnake->GetComponent<Transform>()->SetPosition(Vec3(243.8f, 3.29f, 2.0f));
				mSnake_Two->GetComponent<Transform>()->SetPosition(Vec3(249.8f, 1.92f, 2.0f));
				mFairy->GetComponent<Transform>()->SetPosition(Vec3(250.4f, -4.15f, 2.0f));

				Vec3 pos = mTarget->GetComponent<Transform>()->GetPosition();
				if (pos.y >= -7.59f)
				{
					mSlime->SetDetection(true);
					mSnake->SetDetection(true);
					mSnake_Two->SetDetection(true);
					mFairy->SetDetection(true);

					mKeyCheak = true;
					mKey = false;
				}
			}
			if (mKeyCount == 4)
			{
				mKey = true;
				mainCamera->SetShock(true);
				mainCamera->SetShockDuration(0.7f);
				mKeyCount = 0;
			}

			if (!mKey)
			{
				range_In(Vec4(237.6f, 253.9f, 3.30f, -7.59f));
			}


		}
			break;
		case ks::enums::eGroundStage::Ground8:
		{
			//스킬 or 아이템 or 여신상
			if (!mKeyCheak)
			{				
				Vec3 pos = mTarget->GetComponent<Transform>()->GetPosition();
				if (pos.y >= -8.3f)
				{		
					mKeyCheak = true;
					mKey = false;
				}
			}
			if (Input::GetKeyDown(eKeyCode::ESC))
				mKey = true;
			if (!mKey)
			{
				range_In(Vec4(271.7f, 287.89f, 3.36f, -8.3f));
			}

		}
			break;
		case ks::enums::eGroundStage::Ground9:
		{

			if (!mKeyCheak)
			{
				//1Stage_Boss
				Vec3 pos = mTarget->GetComponent<Transform>()->GetPosition();
				if (pos.y >= -6.9f)
				{
					if (!m_bSoundCheak)
					{
						std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Stage_1");
						sound->Stop();

						std::shared_ptr<AudioClip> booksound = Resources::Load<AudioClip>
							(L"Boss_Ent_Battle", L"D:\\50\\Resources\\Sound\\Boss_Ent_Battle.ogg");
						booksound->SetLoop(true);
						booksound->Play();
						m_bSoundCheak = true;
					}

					ent_Start();					
				}
			}
			if (mKeyCount == 1)
			{
				mBossMeter->Death();
				mBossLayout->Death();
				mKey = true;
				mainCamera->SetShock(true);
				mainCamera->SetShockDuration(0.7f);
				mKeyCount = 0;
			}
			if (!mKey)
			{
				range_In(Vec4(308.3f, 322.3f, 1.72f, -6.9f));
			}
		}
			break;
		case ks::enums::eGroundStage::Start:
		{		
			if(!mKey)
			{
				range_In(Vec4(343.4f, 356.6f, 2.34f, -3.65f));
				range_Out(Vec4(347.9f, 352.2f, 1.6f, -0.9f));
			}
		}
			break;
		case ks::enums::eGroundStage::Boss:
			break;
		}





		GameObject::Update();
	}

	void Stage1_1::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Stage1_1::Render()
	{

		GameObject::Render();
	}

	void Stage1_1::createDiary()
	{

		Diary* diary = object::Instantiate<Diary>(eLayerType::Monster);
		

		//diary->AddComponent<Collider2D>();
		//Collider2D* collider = diary->GetComponent<Collider2D>();
		//collider->SetType(eColliderType::Rect);
		//collider->SetSize(Vec2(0.6f, 0.6f));

		//Transform* tr = diary->GetComponent<Transform>();
		//tr->SetPosition(Vec3(350.f, 0.0f, 1.0f));
		//tr->SetScale(Vec3(0.7f, 0.7f, 2.0f));
		//diary->Initalize();


	}

	void Stage1_1::range_In(Vector4 pos)
	{
		Transform* tr = mTarget->GetComponent<Transform>();
		Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();


		Vec3 fixedpos = playerpos;
		if (playerpos.x <= pos.x)
			fixedpos.x = pos.x;
		if (playerpos.x >= pos.y)
			fixedpos.x = pos.y;
		if (playerpos.y >= pos.z)
			fixedpos.y = pos.z;
		if (playerpos.y <= pos.w)
			fixedpos.y = pos.w;

		tr->SetPosition(fixedpos);


	}

	void Stage1_1::range_Out(Vector4 pos)
	{

		Transform* tr = mTarget->GetComponent<Transform>();
		Vec3 playerpos = tr->GetPosition();

		Vec3 fixedpos = playerpos;

		if (playerpos.x >= pos.x && playerpos.x <= pos.y && playerpos.y >= pos.w && playerpos.y <= pos.z)
		{
			fixedpos = mPrevPos; 
		}


		tr->SetPosition(fixedpos);		
		mPrevPos = fixedpos;

	}

	void Stage1_1::flime_Start()
	{

		if(mStep == Stage_Step::None)
		{
			mainCamera->SetFixCam(false);
			mFlime->GetComponent<Transform>()->SetPosition(Vec3(175.0f, 0.5f, 2.0f));
			Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();
			Vec3 flimepos = mFlime->GetComponent<Transform>()->GetPosition();
			mEndCam = flimepos;

			mBossMeter = object::Instantiate<BossTpMeter>(eLayerType::UI);
			mBossMeter->SetName(L"FlimeMeter");
			mBossMeter->SetMonster(mFlime);


			Transform* bossMetetr = mBossMeter->GetComponent<Transform>();
			bossMetetr->SetPosition(Vector3(Vec3(0.0f, 4.3f, 0.0f)));
			bossMetetr->SetScale(Vector3(9.7f, 0.8f, 1.0f));
			mBossMeter->Initalize();

			mBossLayout = object::Instantiate<BossLayout>(eLayerType::UI);
			mBossLayout->SetName(L"FlimeLayout");

			Transform* layouttr = mBossLayout->GetComponent<Transform>();
			layouttr->SetPosition(Vector3(Vec3(0.0f, 4.3f, 0.0f)));
			layouttr->SetScale(Vector3(10.0f, 1.0f, 1.0f));
			mBossLayout->Initalize();

			flimepos.x += 1.0f;
			mMoveCam = flimepos  - playerpos;
			mMoveCam.Normalize();
			mStep = Stage_Step::Stet_1;

		}

		if (mStep == Stage_Step::Stet_1)
		{
			Transform* tr = mainCamera->GetOwner()->GetComponent<Transform>();
			Vec3 pos = tr->GetPosition();

			pos += mMoveCam * 0.5f * Time::DeltaTime();

			tr->SetPosition(pos);

			if (mEndCam.y < pos.y)
			{				
				mStep = Stage_Step::Stet_2;
				
			}

		}
		if (mStep == Stage_Step::Stet_2)
		{
			mFlimeTime += Time::DeltaTime();
			if (mFlimeTime >= 1.5f)
			{
				Transform* tr = mainCamera->GetOwner()->GetComponent<Transform>();
				Vec3 pos = tr->GetPosition();

				Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();
				mEndCam = playerpos;
				mMoveCam = playerpos - pos;
				mMoveCam.Normalize();
				mStep = Stage_Step::Stet_3;
				mFlimeTime = 0.f;
			}

		}

		if (mStep == Stage_Step::Stet_3)
		{
			Transform* tr = mainCamera->GetOwner()->GetComponent<Transform>();
			Vec3 pos = tr->GetPosition();
			Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();
			//mMoveCam = playerpos - pos;
			//mMoveCam.Normalize();
			pos += mMoveCam * 0.5f * Time::DeltaTime();

			tr->SetPosition(pos);

			if (playerpos.y + 1.0f > pos.y)
			{
				mStep = Stage_Step::None;
				mFlime->SetDetection(true);
				mKeyCheak = true;
				mKey = false;
				mainCamera->SetFixCam(true);
			}
		}
			




	}

	void Stage1_1::ent_Start()
	{
		if (mStep == Stage_Step::None)
		{
			mainCamera->SetFixCam(false);
			mEnt->GetComponent<Transform>()->SetPosition(Vec3(314.4f, 6.0f, 2.0f));
			Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();
			Vec3 flimepos = mEnt->GetComponent<Transform>()->GetPosition();
			mEndCam = flimepos;

			mBossMeter = object::Instantiate<BossTpMeter>(eLayerType::UI);
			mBossMeter->SetName(L"FlimeMeter");
			mBossMeter->SetMonster(mEnt);


			Transform* bossMetetr = mBossMeter->GetComponent<Transform>();
			bossMetetr->SetPosition(Vector3(Vec3(0.0f, 4.3f, 0.0f)));
			bossMetetr->SetScale(Vector3(9.7f, 0.8f, 1.0f));
			mBossMeter->Initalize();

			mBossLayout = object::Instantiate<BossLayout>(eLayerType::UI);
			mBossLayout->SetName(L"FlimeLayout");

			Transform* layouttr = mBossLayout->GetComponent<Transform>();
			layouttr->SetPosition(Vector3(Vec3(0.0f, 4.3f, 0.0f)));
			layouttr->SetScale(Vector3(10.0f, 1.0f, 1.0f));
			mBossLayout->Initalize();

			
			mMoveCam = flimepos - playerpos;
			mMoveCam.Normalize();
			mStep = Stage_Step::Stet_1;
		}

		if (mStep == Stage_Step::Stet_1)
		{
			Transform* tr = mainCamera->GetOwner()->GetComponent<Transform>();
			Vec3 pos = tr->GetPosition();

			pos += mMoveCam * 0.5f * Time::DeltaTime();

			tr->SetPosition(pos);

			if (mEndCam.y < pos.y)
			{
				mStep = Stage_Step::Stet_2;
				mFlimeTime = 0.f;
				mEntTime = 0.f;
			}

		}
		if (mStep == Stage_Step::Stet_2)
		{
			mEntTime += Time::DeltaTime();
			if (mEntTime >= 2.0f)
			{
				Transform* tr = mainCamera->GetOwner()->GetComponent<Transform>();
				Vec3 pos = tr->GetPosition();

				Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();
				mEndCam = playerpos;
				mMoveCam = playerpos - pos;
				mMoveCam.Normalize();
				mStep = Stage_Step::Stet_3;
				mEntTime = 0.f;
			}

		}

		if (mStep == Stage_Step::Stet_3)
		{
			Transform* tr = mainCamera->GetOwner()->GetComponent<Transform>();
			Vec3 pos = tr->GetPosition();
			Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();
			mMoveCam = playerpos - pos;
			mMoveCam.Normalize();
			pos += mMoveCam * 0.5f * Time::DeltaTime();

			tr->SetPosition(pos);

			if (playerpos.y + 1.0f > pos.y)
			{
				mStep = Stage_Step::None;
				mEnt->SetDetection(true);
				mKeyCheak = true;
				mKey = false;
				mainCamera->SetFixCam(true);
			}
		}


	}

	template<typename T>
	void Stage1_1::createGround(const std::wstring& name, std::shared_ptr<T> texture)
	{

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vec3(30.5f, 22.95f, 1.0f));

		std::wstring finshname = name + L"Material";

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(finshname);

		mateiral->SetTexture(texture);

		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);


	}


}
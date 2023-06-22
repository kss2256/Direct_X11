#include "ksOptionUi.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksAudioClip.h"
#include "ksSceneManager.h"
#include "ksPlayerScript.h"
#include "ksInventory.h"
#include "ksOptionCheak.h"
#include "ksObject.h"
#include "ksOnOff.h"
#include "ksStage1_1.h"

#include "ksInput.h"


namespace ks
{

	bool OptionUi::m_bOptionOnOff = false;

	OptionUi::OptionUi()
	{

		mTransform = GetComponent<Transform>();

		loadSound();

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"OptionMaterial");
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Option", L"UI\\Option.png");
		mateiral->SetTexture(texture);
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);
		optionCheakCreate();
		onOffCreate();
		volumeCreate();

	}

	OptionUi::~OptionUi()
	{

	}

	void OptionUi::Initalize()
	{

		mUiPos = mTransform->GetPosition();



		GameObject::Initalize();
	}

	void OptionUi::Update()
	{
		m_vMousePos = Input::GetMousWorldPosition();

		if (m_bOptionOnOff)
		{
			//Vec3 pos = mTarget->GetComponent<Transform>()->GetPosition();
			Vec3 pos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
			pos += mUiPos;			
			mTransform->SetPosition(pos);

			pos.y += 1.75f;
			pos.x += 3.5f;
			mOnOff->GetComponent<Transform>()->SetPosition(pos);

			pos.y -= 2.3f;
			mVolume->GetComponent<Transform>()->SetPosition(pos);


		}
		//인벤토리 켜진상태에서 다시 i 누르면 안보이는 장소로 인벤토리 이동
		else
		{
			mTransform->SetPosition(mUiPos);
			mOnOff->GetComponent<Transform>()->SetPosition(Vec3::Zero);
			mVolume->GetComponent<Transform>()->SetPosition(Vec3::Zero);
			m_bOptionCheak = false;
		}


		//마우스가 인벤토리로 올라오면 플레이어 공격 기능 X
		if (IsMouseOn())
		{
			PlayerScript* player = nullptr;
			player->SetPlayerAttackStop(true);
			Vec3 campos = mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
			Vec3 finalpos = m_vMousePos - campos;
			
			bool lbtndown = Input::GetKeyDown(eKeyCode::LBTN);
			bool lbtnup = Input::GetKeyUp(eKeyCode::LBTN);



			if (finalpos.y <= 2.2f && finalpos.y >= 0.8f)
			{
				if(lbtndown)
				{
					optionSelectSound();
					mOnOff->SetOnOffOneCheak(true);
					if (mOnOff->GetOnOffCheak())
					{
						//걷게 하기
						PlayerScript::SetPlayerRunning(false);
						mOnOff->SetOnOffCheak(false);
					}
					else
					{
						//뛰게 하기
						PlayerScript::SetPlayerRunning(true);
						mOnOff->SetOnOffCheak(true);
					}
				}

				Vec3 pos = mTransform->GetPosition();			
				pos.y += 1.75f;
				mOptionCheak->SetOptionCheakUiPos(pos);
				mOptionCheak->SetOptionCheak1(false);
				mOptionCheak->SetOptionCheak2(true);
				mOptionCheak->SetOptionCheak3(false);
				mOptionCheak->SetOptionCheak4(false);
				mOptionCheak->SetOptionCheak5(false);
			}
			else if (finalpos.y <= 0.8f && finalpos.y >= -0.3f)
			{
				Vec3 pos = mTransform->GetPosition();
				pos.y += 0.55f;
				mOptionCheak->SetOptionCheakUiPos(pos);
				mOptionCheak->SetOptionCheak1(false);
				mOptionCheak->SetOptionCheak2(false);
				mOptionCheak->SetOptionCheak3(true);
				mOptionCheak->SetOptionCheak4(false);
				mOptionCheak->SetOptionCheak5(false);
			}
			else if (finalpos.y <= -0.3f && finalpos.y >= -1.5f)
			{
				if (lbtnup)
				{				
					mVolume->SetChangeVolume(true);					
					
					switch (mVolume->GetVolume())
					{
					case e_Volume::Volume_100:
					{
						mVolume->SetVolume(e_Volume::Volume_0);
						soundVolume(0.0f);
					}
						break;
					case e_Volume::Volume_0:
					{
						mVolume->SetVolume(e_Volume::Volume_20);
						soundVolume(0.2f);
					}
						break;
					case e_Volume::Volume_20:
					{
						mVolume->SetVolume(e_Volume::Volume_40);
						soundVolume(0.4f);
					}
						break;
					case e_Volume::Volume_40:
					{
						mVolume->SetVolume(e_Volume::Volume_60);
						soundVolume(0.6f);
					}
						break;
					case e_Volume::Volume_60:
					{
						mVolume->SetVolume(e_Volume::Volume_80);
						soundVolume(0.8f);
					}
						break;
					case e_Volume::Volume_80:
					{
						mVolume->SetVolume(e_Volume::Volume_100);
						soundVolume(1.0f);
					}
						break;				
					}
				}				

				Vec3 pos = mTransform->GetPosition();
				pos.y += -0.7f;
				mOptionCheak->SetOptionCheakUiPos(pos);
				mOptionCheak->SetOptionCheak1(false);
				mOptionCheak->SetOptionCheak2(false);
				mOptionCheak->SetOptionCheak3(false);
				mOptionCheak->SetOptionCheak4(true);
				mOptionCheak->SetOptionCheak5(false);
			}
			else if (finalpos.y <= -1.5f && finalpos.y >= -2.5f)
			{
				Vec3 pos = mTransform->GetPosition();
				pos.y += -1.8f;
				mOptionCheak->SetOptionCheakUiPos(pos);
				mOptionCheak->SetOptionCheak1(false);
				mOptionCheak->SetOptionCheak2(false);
				mOptionCheak->SetOptionCheak3(false);
				mOptionCheak->SetOptionCheak4(false);
				mOptionCheak->SetOptionCheak5(true);
			}


			
			
		}
		//마우스가 인벤토리에서 벗어나면 공격 기능 On
		else
		{
			mOptionCheak->SetOptionCheak1(true);

			if (!m_bOptionOnOff && !Inventory::GetInventoryOnOff())
			{
				PlayerScript* player = nullptr;
				player->SetPlayerAttackStop(false);
			}
		}



		UIBase::Update();

	}

	void OptionUi::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void OptionUi::Render()
	{
		GameObject::Render();
	}



	void OptionUi::loadSound()
	{

		std::shared_ptr<AudioClip> Option_Select = Resources::Load<AudioClip>
			(L"Option_Select", L"..\\Resources\\Sound\\Option_Select.ogg");




	}

	void OptionUi::optionSelectSound()
	{
		std::shared_ptr<AudioClip> sound = Resources::Find<AudioClip>(L"Option_Select");
		sound->SetLoop(false);
		sound->Play();
	}

	void OptionUi::optionCheakCreate()
	{

		{
			mOptionCheak = object::Instantiate<OptionCheak>(eLayerType::Gold_Ui);
			mOptionCheak->SetName(L"Option");
			mOptionCheak->SetTarget(mTarget);
			

			Transform* tr = mOptionCheak->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			tr->SetScale(Vector3(11.8f, 1.3f, 1.0f));

			
		}
	}

	void OptionUi::onOffCreate()
	{
		{
			mOnOff = object::Instantiate<OnOff>(eLayerType::Gold_Ui);
			mOnOff->SetName(L"OnOff");

			Transform* tr = mOnOff->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			tr->SetScale(Vector3(1.5f, 0.8f, 1.0f));			
		}

	}

	void OptionUi::volumeCreate()
	{
		{
			mVolume = object::Instantiate<Volume>(eLayerType::Gold_Ui);
			mVolume->SetName(L"Volume");

			Transform* tr = mVolume->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			tr->SetScale(Vector3(1.5f, 0.9f, 1.0f));
		}


	}

	void OptionUi::soundVolume(float volume)
	{
		AudioClip::SetVolume(volume);
		switch (mTarget->GetGroundStage())
		{
		case ks::enums::eGroundStage::Ground1:
		{
			Stage1_1::stage_1SoundStop();
			Stage1_1::stage_1Sound();
		}
		break;
		case ks::enums::eGroundStage::Ground2:
		{
			Stage1_1::stage_1SoundStop();
			Stage1_1::stage_1Sound();
		}
		break;
		case ks::enums::eGroundStage::Ground3:
		{
			Stage1_1::stage_1SoundStop();
			Stage1_1::stage_1Sound();
		}
		break;
		case ks::enums::eGroundStage::Ground4:
		{
			Stage1_1::stage_1SoundStop();
			Stage1_1::stage_1Sound();
		}
		break;
		case ks::enums::eGroundStage::Ground6:
		{
			Stage1_1::stage_1SoundStop();
			Stage1_1::stage_1Sound();
		}
		break;
		case ks::enums::eGroundStage::Ground7:
		{
			Stage1_1::stage_1SoundStop();
			Stage1_1::stage_1Sound();
		}
		break;
		case ks::enums::eGroundStage::Ground8:	
		{
			Stage1_1::stage_1SoundStop();
			Stage1_1::stage_1Sound();
		}
		break;
		break;
		}

	
	}



}
#include "ksPlayScene.h"
#include "ksTransform.h"
#include "ksMeshRenderer.h"
#include "ksRenderer.h"
#include "ksResources.h"
#include "ksPlayerScript.h"
#include "ksCamera.h"
#include "ksCameraScript.h"
#include "ksSpriteRenderer.h"
#include "ksGridScript.h"
#include "ksObject.h"
#include "ksPlayer.h"
#include "ksInput.h"
#include "ksCollisionManager.h"
#include "ksStatus.h"
#include "ksSceneManager.h"
#include "ksGameObject.h"
#include "ksCursor.h"
#include "ksMouse.h"
#include "ksStage1_1.h"
#include "ksStage1_1Shadows.h"
#include "ksStage1_1Parts.h"
#include "ksStage1_1Move.h"
#include "ksCloud.h"
#include "ksFadeEffect.h"
#include "ksForest_Fairy.h"
#include "ksSlime_Green.h"
#include "ksSnake_Green.h"
#include "ksBoss_Flime.h"
#include "ksBoss_Ent.h"
#include "ksCollider2D.h"
#include "ksMonster_Trap_Line.h"
#include "ksPlayerLayout.h"
#include "ksPlayerTpMeter.h"
#include "ksPlayerSlot.h"
#include "ksPlayerItem.h"
#include "ksPlayerHP.h"

#include "ksInventory.h"
#include "ksInventorySlot.h"
#include "ksCCoin.h"
#include "ksGoldUi.h"
#include "ksMoneyUi.h"
#include "ksShop_Ui.h"
#include "ksFontWrapper.h"
#include "ksFmod.h"
#include "ksAudioClip.h"
#include "ksAudioListener.h"

#include "ksMonsterMissile.h"

namespace ks
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
		, mSlotname(1)
	{

	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initalize()
	{

		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->TurnLayerMask(eLayerType::UI, true);


		
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
		mainCamera->SetFixCam(true);

		{
			mPlayer = object::Instantiate<Player>(eLayerType::Player);
			mPlayer->SetName(L"PLAYER");

			Transform* tr = mPlayer->GetComponent<Transform>();
			tr->SetPosition(Vector3(350.0f, -2.0f, 2.0f));
			//tr->SetPosition(Vector3(35.0f, 0.0f, 2.0f));
			//tr->SetPosition(Vector3(280.0f, 0.0f, 2.0f));

			//tr->SetScale(Vector3(6.0f, 6.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			loadAnimation();
		

			

			SpriteRenderer* mr = mPlayer->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			Collider2D* collider = mPlayer->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.08f, 0.12f));
			mPlayer->AddComponent<Status>();
			mPlayer->AddComponent<PlayerScript>();
			mPlayer->SetGroundStage(eGroundStage::Start);
			cameraComp->SetTarget(mPlayer);
			
			

		}

		{
			PlayerTpMeter* meter = object::Instantiate<PlayerTpMeter>(eLayerType::UI);
			meter->SetName(L"TpMeter");
			meter->SetTarget(mPlayer);

			Transform* tr = meter->GetComponent<Transform>();
			tr->SetPosition(Vector3(-0.12f, -4.29f, 0.0f));
			tr->SetScale(Vector3(3.2f, 0.3f, 1.0f));			

			//tr->SetPosition(Vector3(0.0f, -2.0f, 0.0f));
			//tr->SetScale(Vector3(5.f, 5.f, 1.0f));

		}

		{
			PlayerLayout* layout = object::Instantiate<PlayerLayout>(eLayerType::UI);			
			layout->SetName(L"Layout");
			layout->SetTarget(mPlayer);
			


			Transform* tr = layout->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, -3.75f, 0.0f));			
			tr->SetScale(Vector3(4.5f, 1.8f, 1.0f));

			//tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			//tr->SetScale(Vector3(9.5f, 5.0f, 1.0f));


			
		}
		{
			PlayerSlot* sloat = object::Instantiate<PlayerSlot>(eLayerType::UI);
			sloat->SetName(L"Sloat");
			sloat->SetTarget(mPlayer);

			Transform* tr = sloat->GetComponent<Transform>();
			tr->SetPosition(Vector3(8.3f, -4.1f, 0.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		}





		{

			mInventory = object::Instantiate<Inventory>(eLayerType::UI);
			mInventory->SetName(L"Inventroy");
			mInventory->SetTarget(mPlayer);
		

			Transform* tr = mInventory->GetComponent<Transform>();
			tr->SetPosition(Vector3(5.0f, 0.0f, 0.0f));
			tr->SetScale(Vector3(7.0f, 7.0f, 1.0f));

			for (int j = 0; j < 3; j++)
			{
				for (int i = -2; i < 3; i++)
				{
					InventorySlot* inventoryslot = new InventorySlot();

					inventoryslot->SetName(std::wstring(L"inventoryslot" + std::to_wstring(mSlotname)));
					inventoryslot->SetTarget(mPlayer);

					Transform* inventorytr = inventoryslot->GetComponent<Transform>();
					Vec3 pos = (Vector3(1 * i, 1.5f - j, 0.0f));
					inventorytr->SetPosition(pos);
					inventorytr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

					mInventory->AddChild(inventoryslot);
					mInventory->SetSlotPos(pos);
					mInventory->SetSlot(inventoryslot);
					++mSlotname;
				}
				
			}
			mSlotname = 0;
			mPlayer->SetInventoryTarget(mInventory);


		}

		{
			PlayerItem* weapon = object::Instantiate<PlayerItem>(eLayerType::UI);
			weapon->SetName(L"Weapon_Sword");
			weapon->SetTarget(mPlayer);
			weapon->SetPlayerItem(eItem::Sword);

			Collider2D* collider = weapon->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.07f, 0.09f));


			Transform* tr = weapon->GetComponent<Transform>();
			tr->SetPosition(Vector3(35.0f, 4.0f, 2.0f));
			tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
		}


		{
			PlayerItem* weapon = object::Instantiate<PlayerItem>(eLayerType::UI);
			weapon->SetName(L"Weapon_Staff");
			weapon->SetTarget(mPlayer);
			weapon->SetPlayerItem(eItem::Staff);

			Collider2D* collider = weapon->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.07f, 0.09f));

			Transform* tr = weapon->GetComponent<Transform>();
			tr->SetPosition(Vector3(32.0f, 4.0f, 2.0f));
			tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
		}

		{
			PlayerItem* weapon = object::Instantiate<PlayerItem>(eLayerType::UI);
			weapon->SetName(L"Weapon_Bow");
			weapon->SetTarget(mPlayer);
			weapon->SetPlayerItem(eItem::Bow);

			Collider2D* collider = weapon->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.07f, 0.09f));

			Transform* tr = weapon->GetComponent<Transform>();
			tr->SetPosition(Vector3(38.0f, 4.0f, 2.0f));
			tr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
		}

		{
			PlayerHP* playerhp = object::Instantiate<PlayerHP>(eLayerType::UI);
			playerhp->SetName(L"Player_Hp_UI");
			playerhp->SetTarget(mPlayer);		

			/*Transform* tr = playerhp->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.0f, -3.5f, 0.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));*/
		}

		{
			GoldUi* goldui = object::Instantiate<GoldUi>(eLayerType::Gold_Ui);
			goldui->SetName(L"GoldUi");
			goldui->SetTarget(mPlayer);

			Transform* tr = goldui->GetComponent<Transform>();
			tr->SetPosition(Vector3(9.0f, 4.7f, 0.0f));
			tr->SetScale(Vector3(0.7f, 0.7f, 1.0f));
		}

		{
			MoneyUi* goldui = object::Instantiate<MoneyUi>(eLayerType::Gold_Ui);
			goldui->SetName(L"MoneyUi");
			goldui->SetTarget(mPlayer);

			Transform* tr = goldui->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			tr->SetScale(Vector3(0.7f, 0.7f, 1.0f));
		}


		{
			Shop_Ui* shop = object::Instantiate<Shop_Ui>(eLayerType::Shop_UI);
			shop->SetName(L"MoneyUi");
			shop->SetTarget(mPlayer);

			Transform* tr = shop->GetComponent<Transform>();
			tr->SetPosition(Vector3(105.0f, 1.5f, 0.0f));			
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
		}


		{

			mMouse = object::Instantiate<Mouse>(eLayerType::Mouse);
			mMouse->SetName(L"CURSOR1");
			mMouse->AddComponent<Cursor>();
			mMouse->AddComponent<Cursor>()->SetTarget(mPlayer);
			Transform* montr = mMouse->GetComponent<Transform>();
			montr->SetPosition(Vector3(35.f, 0.f, 2.0f));
			montr->SetScale(Vector3(0.7f, 0.7f, 1.0f));
			SpriteRenderer* monmr = mMouse->AddComponent<SpriteRenderer>();

			std::shared_ptr<Material> monmateiral = Resources::Find<Material>(L"CursorMaterial");
			monmr->SetMaterial(monmateiral);
			std::shared_ptr<Mesh> monmesh = Resources::Find<Mesh>(L"RectMesh");
			monmr->SetMesh(monmesh);

		}



		{
			Cloud* fogobj = object::Instantiate<Cloud>(eLayerType::Fog);
			fogobj->SetName(L"FOG_1");
			fogobj->SetTarget(mPlayer);
			fogobj->SetGroundStage(mPlayer->GetGroundStage());
			Transform* montr = fogobj->GetComponent<Transform>();			
			montr->SetScale(Vector3(35.0f, 35.0f, 1.0f));			
		}



		{
			mForest_Fairy = object::Instantiate<Forest_Fairy>(eLayerType::Monster);
			mForest_Fairy->SetName(L"Forest_Fairy");
			mForest_Fairy->SetTarget(mPlayer);
			Collider2D* collider = mForest_Fairy->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.125f, 0.175f));
			collider->SetCenter(Vec2(0.05f, -0.2f));


			Transform* montr = mForest_Fairy->GetComponent<Transform>();
			montr->SetPosition(Vector3(0.0f, 20.0f, 2.0f));
			montr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
		}

		{
			mSlime_Green = object::Instantiate<Slime_Green>(eLayerType::Monster);			
			mSlime_Green->SetName(L"Slime_Green");
			mSlime_Green->SetTarget(mPlayer);

			Collider2D* collider = mSlime_Green->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.15f, 0.12f));
			collider->SetCenter(Vec2(0.05f, -0.6f));
			Transform* montr = mSlime_Green->GetComponent<Transform>();
			montr->SetPosition(Vector3(0.f, 20.f, 2.0f));
			montr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
		}

		{
			mSlime_Green_Two = object::Instantiate<Slime_Green>(eLayerType::Monster);
			mSlime_Green_Two->SetName(L"Slime_Green2");
			mSlime_Green_Two->SetTarget(mPlayer);

			Collider2D* collider = mSlime_Green_Two->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.15f, 0.12f));
			collider->SetCenter(Vec2(0.05f, -0.6f));
			Transform* montr = mSlime_Green_Two->GetComponent<Transform>();
			montr->SetPosition(Vector3(0.f, 20.f, 2.0f));
			montr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
		}


		{
			mSnake_Green = object::Instantiate<Snake_Green>(eLayerType::Monster);
			mSnake_Green->SetName(L"Snake_Green");
			mSnake_Green->SetTarget(mPlayer);
			Collider2D* collider = mSnake_Green->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.1f, 0.12f));
			Transform* montr = mSnake_Green->GetComponent<Transform>();
			montr->SetPosition(Vector3(0.f, 20.f, 2.0f));
			montr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
		}

		{
			mSnake_Green_Two = object::Instantiate<Snake_Green>(eLayerType::Monster);
			mSnake_Green_Two->SetName(L"Snake_Green_Two");
			mSnake_Green_Two->SetTarget(mPlayer);
			Collider2D* collider = mSnake_Green_Two->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.1f, 0.12f));
			Transform* montr = mSnake_Green_Two->GetComponent<Transform>();
			montr->SetPosition(Vector3(0.f, 20.f, 2.0f));
			montr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
		}


		{
			mBoss_Flime = object::Instantiate<Boss_Flime>(eLayerType::Monster);
			mBoss_Flime->SetName(L"Boss_Flime");
			mBoss_Flime->SetTarget(mPlayer);

			Collider2D* collider = mBoss_Flime->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.30f, 0.37f));


			Transform* montr = mBoss_Flime->GetComponent<Transform>();
			montr->SetPosition(Vector3(0.0f, 20.0f, 2.0f));
			montr->SetScale(Vector3(14.0f, 14.0f, 1.0f));
		}

		{
			mBoss_Ent = object::Instantiate<Boss_Ent>(eLayerType::Monster);
			mBoss_Ent->SetName(L"Boss_Ent");
			mBoss_Ent->SetTarget(mPlayer);

			Collider2D* collider = mBoss_Ent->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.3f, 0.75f));
			//collider->SetCenter(Vec2(0.0f, -2.0f));


			Transform* montr = mBoss_Ent->GetComponent<Transform>();
			montr->SetPosition(Vector3(0.0f, 20.0f, 2.0f));
			montr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
		}




		{
			mStageMove = object::Instantiate<Stage1_1Move>(eLayerType::Mouse);
			mStageMove->SetName(L"Stage_Move");
			mStageMove->SetTarget(mPlayer);
			
			Transform* montr = mStageMove->GetComponent<Transform>();
			montr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
			montr->SetPosition(Vec3(350.f, 0.0f, 1.0f));
		}
	





		{
			eGroundStage stage = eGroundStage::Ground1;
			float size = 35.f;
			for (size_t i = 1; i < 11; i++)
			{
				stage = (eGroundStage)i;			
				if (i == 10)
				{
					loadGround(eLayerType::Ground, stage, std::wstring(L"Start"), Vec3(size, 0.f, 1.0f));
					loadShadows(eLayerType::Ground_Shadows, stage, std::wstring(L"StartShadows"), Vec3(size, 0.f, 1.0f));
					loadParts(eLayerType::Ground_Parts, stage, std::wstring(L"StartParts"), Vec3(size, 0.f, 1.0f));
				}
				else
				{
					loadGround(eLayerType::Ground, stage, std::wstring(L"Ground" + std::to_wstring(i)), Vec3(size, 0.f, 1.0f));
					loadShadows(eLayerType::Ground_Shadows, stage, std::wstring(L"GroundShadows" + std::to_wstring(i)), Vec3(size, 0.f, 1.0f));
					loadParts(eLayerType::Ground_Parts, stage, std::wstring(L"GroundParts" + std::to_wstring(i)), Vec3(size, 0.f, 1.0f));
				}

				size += 35.f;				
			}
		}



		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player_Attack, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Mouse, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster_Attack, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::UI, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Shop_Item, true);


		Scene::Initalize();







	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
		}



		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		Destroy();
		Initalize();

	}

	void PlayScene::OnExit()
	{

		LayerObjectClear(eLayerType::Camera);
		LayerObjectClear(eLayerType::Monster);
		LayerObjectClear(eLayerType::Monster_Attack);
		LayerObjectClear(eLayerType::Player);
		LayerObjectClear(eLayerType::Mouse);
		LayerObjectClear(eLayerType::Fog);
		LayerObjectClear(eLayerType::Ground);
		LayerObjectClear(eLayerType::Ground_Light);
		LayerObjectClear(eLayerType::Ground_Parts);
		LayerObjectClear(eLayerType::Ground_Shadows);
		LayerObjectClear(eLayerType::Object);
		LayerObjectClear(eLayerType::UI);
		LayerObjectClear(eLayerType::Gold_Ui);
		LayerObjectClear(eLayerType::Shop_UI);


		Destroy();


	}

	void PlayScene::loadAnimation()
	{


		Animator* attack_animator = mPlayer->AddComponent<Animator>();
		std::shared_ptr<Texture> Player_State_Texture = Resources::Load<Texture>(L"Player_State", L"Player_State.png");
		
		//휴식 모션

		mNumbers.push_back(218);
		mNumbers.push_back(219);
		mNumbers.push_back(220);
		mNumbers.push_back(138);
		mNumbers.push_back(139);
		mNumbers.push_back(140);
		mNumbers.push_back(141);

		CreateAnimation(L"Sit_Down", Player_State_Texture, attack_animator, Vector2(100.0f, 100.0f), Vec2::Zero, mNumbers, 0.4f);
		mNumbers.clear();

		attack_animator->Create(L"Sit_Pray", Player_State_Texture, Vector2(0.0f, 2200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.3f);

		//죽었을때 모션??
		attack_animator->Create(L"Death_UpLeft", Player_State_Texture, Vector2(400.0f, 2300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.3f);


		





		//기본 모션
		attack_animator->Create(L"Idle_Down", Player_State_Texture, Vector2(400.0f, 0.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Idle_DownLeft", Player_State_Texture, Vector2(100.0f, 0.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Idle_DownRight", Player_State_Texture, Vector2(100.0f, 100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Idle_Left", Player_State_Texture, Vector2(400.0f, 100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Idle_Right", Player_State_Texture, Vector2(100.0f, 200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Idle_Up", Player_State_Texture, Vector2(100.0f, 300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Idle_UpLeft", Player_State_Texture, Vector2(400.0f, 200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Idle_UpRight", Player_State_Texture, Vector2(400.0f, 300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);


		//뛰는 모션
		attack_animator->Create(L"Run_DownLeft", Player_State_Texture, Vector2(0.0f, 3200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 4, 0.1f);
		attack_animator->Create(L"Run_Down", Player_State_Texture, Vector2(0.0f, 2800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 4, 0.1f);
		attack_animator->Create(L"Run_Right", Player_State_Texture, Vector2(0.0f, 3000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 4, 0.1f);
		attack_animator->Create(L"Run_UpLeft", Player_State_Texture, Vector2(0.0f, 3400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 4, 0.1f);
		attack_animator->Create(L"Run_Left", Player_State_Texture, Vector2(0.0f, 2900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 4, 0.1f);
		attack_animator->Create(L"Run_Up", Player_State_Texture, Vector2(0.0f, 3100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 4, 0.1f);
		attack_animator->Create(L"Run_UpRight", Player_State_Texture, Vector2(0.0f, 3500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 4, 0.1f);
		attack_animator->Create(L"Run_DownRight", Player_State_Texture, Vector2(0.0f, 3300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 4, 0.1f);
		//걷는 모션
		
		mNumbers.push_back(0);
		mNumbers.push_back(2);
		CreateAnimation(L"Move_DownLeft", Player_State_Texture, attack_animator, Vector2(100.0f, 100.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();


		mNumbers.push_back(3);
		mNumbers.push_back(5);
		CreateAnimation(L"Move_Down", Player_State_Texture, attack_animator, Vector2(100.0f, 100.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(6);
		mNumbers.push_back(8);
		CreateAnimation(L"Move_DownRight", Player_State_Texture, attack_animator, Vector2(100.0f, 100.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(9);
		mNumbers.push_back(11);
		CreateAnimation(L"Move_Left", Player_State_Texture, attack_animator, Vector2(100.0f, 100.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(12);
		mNumbers.push_back(14);
		CreateAnimation(L"Move_Right", Player_State_Texture, attack_animator, Vector2(100.0f, 100.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();


		mNumbers.push_back(15);
		mNumbers.push_back(17);
		CreateAnimation(L"Move_UpLeft", Player_State_Texture, attack_animator, Vector2(100.0f, 100.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(18);
		mNumbers.push_back(20);
		CreateAnimation(L"Move_Up", Player_State_Texture, attack_animator, Vector2(100.0f, 100.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();

		mNumbers.push_back(21);
		mNumbers.push_back(23);
		CreateAnimation(L"Move_UpRight", Player_State_Texture, attack_animator, Vector2(100.0f, 100.0f), Vec2::Zero, mNumbers, 0.2f);
		mNumbers.clear();


		//회피 모션
		attack_animator->Create(L"Evade_DownLeft", Player_State_Texture, Vector2(0.0f, 4000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		attack_animator->Create(L"Evade_Down", Player_State_Texture, Vector2(0.0f, 4100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		attack_animator->Create(L"Evade_DownRight", Player_State_Texture, Vector2(0.0f, 4200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		attack_animator->Create(L"Evade_Left", Player_State_Texture, Vector2(0.0f, 4300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		attack_animator->Create(L"Evade_Right", Player_State_Texture, Vector2(0.0f, 4400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		attack_animator->Create(L"Evade_UpLeft", Player_State_Texture, Vector2(0.0f, 4500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		attack_animator->Create(L"Evade_Up", Player_State_Texture, Vector2(0.0f, 4600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);
		attack_animator->Create(L"Evade_UpRight", Player_State_Texture, Vector2(0.0f, 4700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.075f);



		//피격 모션
		attack_animator->Create(L"Hit_DownLeft", Player_State_Texture, Vector2(0.0f, 800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Hit_Down", Player_State_Texture, Vector2(300.0f, 800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Hit_DownRight", Player_State_Texture, Vector2(0.0f, 900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Hit_Left", Player_State_Texture, Vector2(300.0f, 900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Hit_Right", Player_State_Texture, Vector2(0.0f, 1000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Hit_UpLeft", Player_State_Texture, Vector2(300.0f, 1000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Hit_Up", Player_State_Texture, Vector2(0.0f, 1100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Hit_UpRight", Player_State_Texture, Vector2(300.0f, 1100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);



		//공격 모션


		//스킬

		//마나의 지팡이 스킬 모션
		attack_animator->Create(L"Skil_Staff_DownLeft", Player_State_Texture, Vector2(0.0f, 400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Staff_Down", Player_State_Texture, Vector2(300.0f, 400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Staff_DownRight", Player_State_Texture, Vector2(0.0f, 500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Staff_Left", Player_State_Texture, Vector2(300.0f, 500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Staff_Right", Player_State_Texture, Vector2(0.0f, 600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Staff_UpLeft", Player_State_Texture, Vector2(300.0f, 600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Staff_Up", Player_State_Texture, Vector2(0.0f, 700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Staff_UpRight", Player_State_Texture, Vector2(300.0f, 700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);


		//손앞으로 뻗는 스킬 모션
		attack_animator->Create(L"Skil_Magic_DownLeft", Player_State_Texture, Vector2(0.0f, 1400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Magic_Down", Player_State_Texture, Vector2(300.0f, 1400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Magic_DownRight", Player_State_Texture, Vector2(0.0f, 1500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Magic_Left", Player_State_Texture, Vector2(300.0f, 1500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Magic_Right", Player_State_Texture, Vector2(0.0f, 1600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Magic_UpLeft", Player_State_Texture, Vector2(300.0f, 1600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Magic_Up", Player_State_Texture, Vector2(0.0f, 1700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Skil_Magic_UpRight", Player_State_Texture, Vector2(300.0f, 1700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);



		//기본 공격
		attack_animator->Create(L"Attack_Staffcharge_DownLeft", Player_State_Texture, Vector2(0.0f, 1800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.1f);
		attack_animator->Create(L"Attack_Staffcharge_Down", Player_State_Texture, Vector2(300.0f, 1800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.1f);
		attack_animator->Create(L"Attack_Staffcharge_DownRight", Player_State_Texture, Vector2(0.0f, 1900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.1f);
		attack_animator->Create(L"Attack_Staffcharge_Left", Player_State_Texture, Vector2(300.0f, 1900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.1f);
		attack_animator->Create(L"Attack_Staffcharge_Right", Player_State_Texture, Vector2(0.0f, 2000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.1f);
		attack_animator->Create(L"Attack_Staffcharge_UpLeft", Player_State_Texture, Vector2(300.0f, 2000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.1f);
		attack_animator->Create(L"Attack_Staffcharge_Up", Player_State_Texture, Vector2(0.0f, 2100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.1f);
		attack_animator->Create(L"Attack_Staffcharge_UpRight", Player_State_Texture, Vector2(300.0f, 2100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.1f);

		//서서 활 공격
		attack_animator->Create(L"Attack_Stand_Bow_DownLeft", Player_State_Texture, Vector2(200.0f, 1800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Attack_Stand_Bow_Down", Player_State_Texture, Vector2(500.0f, 1800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Attack_Stand_Bow_DownRight", Player_State_Texture, Vector2(200.0f, 1900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Attack_Stand_Bow_Left", Player_State_Texture, Vector2(500.0f, 1900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Attack_Stand_Bow_Right", Player_State_Texture, Vector2(200.0f, 2000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Attack_Stand_Bow_UpLeft", Player_State_Texture, Vector2(500.0f, 2000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Attack_Stand_Bow_Up", Player_State_Texture, Vector2(200.0f, 2100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);
		attack_animator->Create(L"Attack_Stand_Bow_UpRight", Player_State_Texture, Vector2(500.0f, 2100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 1, 0.1f);

		//걸어가며 활 공격
		attack_animator->Create(L"Attack_Walk_Bow_DownLeft", Player_State_Texture, Vector2(0.0f, 2400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.15f);
		attack_animator->Create(L"Attack_Walk_Bow_Down", Player_State_Texture, Vector2(300.0f, 2400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.15f);
		attack_animator->Create(L"Attack_Walk_Bow_DownRight", Player_State_Texture, Vector2(0.0f, 2500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.15f);
		attack_animator->Create(L"Attack_Walk_Bow_Left", Player_State_Texture, Vector2(300.0f, 2500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.15f);
		attack_animator->Create(L"Attack_Walk_Bow_Right", Player_State_Texture, Vector2(0.0f, 2600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.15f);
		attack_animator->Create(L"Attack_Walk_Bow_UpLeft", Player_State_Texture, Vector2(300.0f, 2600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.15f);
		attack_animator->Create(L"Attack_Walk_Bow_Up", Player_State_Texture, Vector2(0.0f, 2700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.15f);
		attack_animator->Create(L"Attack_Walk_Bow_UpRight", Player_State_Texture, Vector2(300.0f, 2700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.15f);


		//검 대쉬 공격
		attack_animator->Create(L"Attack_Dash_DownLeft", Player_State_Texture, Vector2(0.0f, 7200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Attack_Dash_Down", Player_State_Texture, Vector2(300.0f, 7200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Attack_Dash_DownRight", Player_State_Texture, Vector2(0.0f, 7300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Attack_Dash_Left", Player_State_Texture, Vector2(300.0f, 7300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Attack_Dash_Right", Player_State_Texture, Vector2(0.0f, 7400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Attack_Dash_UpLeft", Player_State_Texture, Vector2(300.0f, 7400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Attack_Dash_Up", Player_State_Texture, Vector2(0.0f, 7500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);
		attack_animator->Create(L"Attack_Dash_UpRight", Player_State_Texture, Vector2(300.0f, 7500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.1f);



		//기본 검 공격	
		attack_animator->Create(L"Attack_None_DownLeft", Player_State_Texture, Vector2(0.0f, 5300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.05f);
		attack_animator->Create(L"Attack_None_Down", Player_State_Texture, Vector2(0.0f, 5400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.05f);
		attack_animator->Create(L"Attack_None_DownRight", Player_State_Texture, Vector2(0.0f, 5500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.05f);
		attack_animator->Create(L"Attack_None_Left", Player_State_Texture, Vector2(0.0f, 5600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.05f);
		attack_animator->Create(L"Attack_None_Right", Player_State_Texture, Vector2(0.0f, 5700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.05f);
		attack_animator->Create(L"Attack_None_UpLeft", Player_State_Texture, Vector2(0.0f, 5800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.05f);
		attack_animator->Create(L"Attack_None_Up", Player_State_Texture, Vector2(0.0f, 5900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.05f);
		attack_animator->Create(L"Attack_None_UpRight", Player_State_Texture, Vector2(0.0f, 6000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 6, 0.05f);

		attack_animator->Create(L"Attack1_Sword_DownLeft", Player_State_Texture, Vector2(0.0f, 6100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack2_Sword_DownLeft", Player_State_Texture, Vector2(200.0f, 6100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack3_Sword_DownLeft", Player_State_Texture, Vector2(400.0f, 6100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack4_Sword_DownLeft", Player_State_Texture, Vector2(0.0f, 6200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		attack_animator->Create(L"Attack1_Sword_Down", Player_State_Texture, Vector2(200.0f, 6200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack2_Sword_Down", Player_State_Texture, Vector2(400.0f, 6200.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack3_Sword_Down", Player_State_Texture, Vector2(0.0f, 6300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack4_Sword_Down", Player_State_Texture, Vector2(200.0f, 6300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		attack_animator->Create(L"Attack1_Sword_DownRight", Player_State_Texture, Vector2(400.0f, 6300.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack2_Sword_DownRight", Player_State_Texture, Vector2(0.0f, 6400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack3_Sword_DownRight", Player_State_Texture, Vector2(200.0f, 6400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack4_Sword_DownRight", Player_State_Texture, Vector2(400.0f, 6400.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		attack_animator->Create(L"Attack1_Sword_Right", Player_State_Texture, Vector2(0.0f, 6500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack2_Sword_Right", Player_State_Texture, Vector2(200.0f, 6500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack3_Sword_Right", Player_State_Texture, Vector2(400.0f, 6500.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack4_Sword_Right", Player_State_Texture, Vector2(0.0f, 6600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		attack_animator->Create(L"Attack1_Sword_Left", Player_State_Texture, Vector2(200.0f, 6600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack2_Sword_Left", Player_State_Texture, Vector2(400.0f, 6600.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack3_Sword_Left", Player_State_Texture, Vector2(0.0f, 6700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack4_Sword_Left", Player_State_Texture, Vector2(200.0f, 6700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		attack_animator->Create(L"Attack1_Sword_UpLeft", Player_State_Texture, Vector2(400.0f, 6700.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack2_Sword_UpLeft", Player_State_Texture, Vector2(0.0f, 6800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack3_Sword_UpLeft", Player_State_Texture, Vector2(200.0f, 6800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack4_Sword_UpLeft", Player_State_Texture, Vector2(400.0f, 6800.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		attack_animator->Create(L"Attack1_Sword_Up", Player_State_Texture, Vector2(0.0f, 6900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack2_Sword_Up", Player_State_Texture, Vector2(200.0f, 6900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack3_Sword_Up", Player_State_Texture, Vector2(400.0f, 6900.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack4_Sword_Up", Player_State_Texture, Vector2(0.0f, 7000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

		attack_animator->Create(L"Attack1_Sword_UpRight", Player_State_Texture, Vector2(200.0f, 7000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack2_Sword_UpRight", Player_State_Texture, Vector2(400.0f, 7000.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack3_Sword_UpRight", Player_State_Texture, Vector2(0.0f, 7100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);
		attack_animator->Create(L"Attack4_Sword_UpRight", Player_State_Texture, Vector2(200.0f, 7100.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 2, 0.07f);

	}

	void PlayScene::loadGround(eLayerType layer, eGroundStage stage, const std::wstring name, Vec3 pos)
	{
		{
			mStage = object::Instantiate<Stage1_1>(layer);
			mStage->SetName(name);
			mStage->SetTarget(mPlayer);
			mStage->SetTextureName(name);
			mStage->GetComponent<Transform>()->SetPosition(pos);
			mStage->SetGroundStage(stage);
			mStage->SetFairy(mForest_Fairy);
			mStage->SetSnake(mSnake_Green);
			mStage->SetSnake_Two(mSnake_Green_Two);
			mStage->SetSlime(mSlime_Green);			
			mStage->SetSlime_Two(mSlime_Green_Two);
			mStage->SetFlime(mBoss_Flime);
			mStage->SetEnt(mBoss_Ent);		

		}
	}

	void PlayScene::loadShadows(eLayerType layer, eGroundStage stage, const std::wstring name, Vec3 pos)
	{		
		{
			mStageShadows = object::Instantiate<Stage1_1Shadows>(layer);
			mStageShadows->SetName(name);
			mStageShadows->SetTarget(mPlayer);
			mStageShadows->SetTextureName(name);
			mStageShadows->GetComponent<Transform>()->SetPosition(pos);
			mStageShadows->SetGroundStage(stage);
		}
	}

	void PlayScene::loadParts(eLayerType layer, eGroundStage stage, const std::wstring name, Vec3 pos)
	{
		{
			mStageParts = object::Instantiate<Stage1_1Parts>(layer);
			mStageParts->SetName(name);
			mStageParts->SetTarget(mPlayer);
			mStageParts->SetTextureName(name);
			mStageParts->GetComponent<Transform>()->SetPosition(pos);
			mStageParts->SetGroundStage(stage);
		}
	}


	void PlayScene::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr
		, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration)
	{

		// 이중 포문 		
		Vec2 value = Vec2(texture->GetWidth() / scale.x, texture->GetHeight() / scale.y);
		UINT Col = (UINT)value.x;					//3개?
		UINT Row = (UINT)value.y;					//10개?

		UINT textureeLegth = (UINT)(value.x * value.y);		//총 개수 30개

		//이중 포문 이건 10행
		for (UINT i = 0; i < Row; i++)
		{
			//이중 포문 이건 3열
			for (UINT j = 0; j < Col; j++)
			{
				Sprite animation;

				animation.AnimationName = name;
				animation.atlasSize = scale;
				animation.duration = duration;
				animation.leftTop = Vec2(j * scale.x, i * scale.y);
				animation.offset = offset;
				//animation.pos = mTransform->GetPosition(); // 이건 필요 없는듯 ? 필요할떄 사용예정 포지션을 받아와야함
				animation.size = scale;


				mSvaeSprite.push_back(animation);
			}
		}

		for (size_t i = 0; i < numbers.size(); i++)
		{
			std::vector<UINT>::iterator iter = numbers.begin();

			mSprites.push_back(mSvaeSprite[iter[i]]);
		}


		for (size_t i = 0; i < mSprites.size(); i++)
		{
			mSprites[i].leftTop = Vector2((mSprites[i].leftTop.x / texture->GetWidth()), (mSprites[i].leftTop.y) / texture->GetHeight());
			mSprites[i].size = Vector2(mSprites[i].size.x / texture->GetWidth(), mSprites[i].size.y / texture->GetHeight());
			mSprites[i].offset = mSprites[i].offset;
			mSprites[i].duration = mSprites[i].duration;
			mSprites[i].atlasSize = Vector2(400.0f / texture->GetWidth(), 400.0f / texture->GetHeight());
			mSprites[i].AnimationName = mSprites[i].AnimationName;
		}



		animaotr->CreateAfter(mSprites, texture);
		mSvaeSprite.clear();
		mSprites.clear();


	}






}

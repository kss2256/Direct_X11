#include "ksShop_Ui.h"
#include "ksSpriteRenderer.h"
#include "ksMaterial.h"
#include "ksMesh.h"
#include "ksResources.h"
#include "ksTransform.h"
#include "ksObject.h"
#include "ksTime.h"
#include "ksPlayerItem.h"

#include "ksInput.h"


namespace ks
{

	Shop_Ui::Shop_Ui()
	{
		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		loadAnimation();


		SpriteRenderer* sr = AddComponent<SpriteRenderer>();


		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"CoinMaterial");
		sr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMesh(mesh);

		mAnimator->Play(L"Shop", true);



		
		PlayerItem* LegendSword = object::Instantiate<PlayerItem>(eLayerType::Shop_Item);
		LegendSword->SetName(L"Shop_Item_Sword");
		LegendSword->SetTarget(mTarget);
		LegendSword->SetPlayerItem(eItem::Legend_Sword);
		LegendSword->SetShopItem(true);

		Collider2D* swordcollider = LegendSword->AddComponent<Collider2D>();
		swordcollider->SetType(eColliderType::Rect);
		swordcollider->SetSize(Vector2(0.07f, 0.09f));

		Transform* Swordtr = LegendSword->GetComponent<Transform>();
		Swordtr->SetPosition(Vector3(103.0f, 0.3f, 2.0f));
		Swordtr->SetScale(Vector3(11.0f, 11.0f, 1.0f));
		
		LegendSword->Initalize();


		PlayerItem* LegendBow = object::Instantiate<PlayerItem>(eLayerType::Shop_Item);
		LegendBow->SetName(L"Shop_Item_Bow");
		LegendBow->SetTarget(mTarget);
		LegendBow->SetPlayerItem(eItem::Legend_Bow);
		LegendBow->SetShopItem(true);

		Collider2D* bowcollider = LegendBow->AddComponent<Collider2D>();
		bowcollider->SetType(eColliderType::Rect);
		bowcollider->SetSize(Vector2(0.07f, 0.09f));

		Transform* Bowtr = LegendBow->GetComponent<Transform>();
		Bowtr->SetPosition(Vector3(105.0f, 0.3f, 2.0f));
		Bowtr->SetScale(Vector3(11.0f, 11.0f, 1.0f));

		LegendBow->Initalize();


		PlayerItem* LegendStaff = object::Instantiate<PlayerItem>(eLayerType::Shop_Item);
		LegendStaff->SetName(L"Shop_Item_Staff");
		LegendStaff->SetTarget(mTarget);
		LegendStaff->SetPlayerItem(eItem::Legend_Staff);
		LegendStaff->SetShopItem(true);

		Collider2D* staffcollider = LegendStaff->AddComponent<Collider2D>();
		staffcollider->SetType(eColliderType::Rect);
		staffcollider->SetSize(Vector2(0.07f, 0.09f));

		Transform* Stafftr = LegendStaff->GetComponent<Transform>();
		Stafftr->SetPosition(Vector3(107.0f, 0.3f, 2.0f));
		Stafftr->SetScale(Vector3(11.0f, 11.0f, 1.0f));

		LegendStaff->Initalize();




	}

	Shop_Ui::~Shop_Ui()
	{
	}

	void Shop_Ui::Initalize()
	{

		GameObject::Initalize();
	}

	void Shop_Ui::Update()
	{
		if (Input::GetKeyDown(eKeyCode::H))
		{
			mAnimator->Play(L"Shop", true);
		}





		UIBase::Update();

	}

	void Shop_Ui::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Shop_Ui::Render()
	{
		GameObject::Render();
	}

	void Shop_Ui::loadAnimation()
	{

		std::shared_ptr<Texture> shop = Resources::Load<Texture>(L"Mery_Shop", L"Shop_Ui\\Mery_Shop.png");

		mNumbers.push_back(0);
		mNumbers.push_back(3);
		mNumbers.push_back(6);
		mNumbers.push_back(7);
		mNumbers.push_back(4);
		mNumbers.push_back(1);
		mNumbers.push_back(2);
		mNumbers.push_back(5);
		mNumbers.push_back(8);
		CreateAnimation(L"Shop", shop, mAnimator, Vector2(210.0f, 122.0f), Vec2::Zero, mNumbers, 2.0f);
		mNumbers.clear();

	}

	void Shop_Ui::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> texture, Animator* animaotr, Vec2 scale, Vector2 offset, std::vector<UINT> numbers, float duration)
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
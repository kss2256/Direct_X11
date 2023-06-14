#pragma once

namespace ks::enums
{
	enum class eGroundStage
	{
		None,	
		Ground1,
		Ground2,
		Ground3,
		Ground4,
		Ground5,
		Ground6,
		Ground7,
		Ground8,
		Ground9,
		Start,
		Boss,
	};


	enum class eSceneType
	{
		Tilte,
		Play,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Ground,
		Ground_Shadows,
		Ground_Light,
		Player_Afterimage,
		Monster_Attack,
		Monster,
		Shop_UI,
		Shop_Item,
		Player,
		Player_Attack,
		Object,
		Player_Effect,
		Ground_Parts,
		Fog,
		UI,
		Gold_Ui,
		Mouse,
		End,
	};

	enum class eComponentType
	{
		None,
		Status,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Camera,
		Mesh,		
		//Collider2,
		MeshRenerer,
		SpriteRenderer,
		Animator,
		AudioListener,
		AudioSource,
		Light,
		Line,		///TEST
		UI,
		Cursor,
		FadeEffect,
		Script,
		Afterimage,
		Collider,	
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		/*Font,*/
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		AudioClip,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	enum class eUIType
	{
		HP,
		LIFE,
		MP,
		SHOP,
		INVENTORY,
		OPTION,
		START,
		GROUNDBUTTON,
		SAVEBUTTON,
		LOADBUTTON,
		GROUND_OBJECT,
		ANIMATIONPANEL,



		END,
	};


	//struct Ray
	//{
	//	Vector3 origin;
	//	Vector3 dest;
	//};

}
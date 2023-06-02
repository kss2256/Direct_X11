#pragma once
#include "ksComponent.h"

namespace ks
{
	using namespace math;
	class Boss_Flime;
	class Boss_Ent;
	class Player;
	class GameObject;
	class Camera : public Component
	{
	public:
		enum eProjectionType
		{
			Perspective,
			Orthographic,
		};

		__forceinline static Matrix& GetGpuViewMatrix() { return View; }
		__forceinline static Matrix& GetGpuProjectionMatrix() { return Projection; }
		__forceinline static void SetGpuViewMatrix(Matrix view) { View = view; }
		__forceinline static void SetGpuProjectionMatrix(Matrix projection) { Projection = projection; }

		Camera();
		virtual ~Camera();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix();
		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType layer, bool enable = true);
		void EnableLayerMasks() { mLayerMasks.set(); }
		void DisableLayerMasks() { mLayerMasks.reset(); }

		void SetProjectionType(eProjectionType type) { mType = type; }
		float GetScale() { return mScale; }
		Matrix& GetViewMatrix() { return mView; }
		Matrix& GetProjectionMatrix() { return mProjection; }

		Player* GetTarget() { return mTarget; }
		void SetTarget(Player* target) { mTarget = target; }
		void SetFlimeTraget(Boss_Flime* flime) { mFlime = flime; }
		void SetEntTarget(Boss_Ent* ent) { mEnt = ent; }
		void SetFixCam(bool fix) { mFixCam = fix; }
		static Vector3 CalculatePos(Vector3 pos) { return pos - mDistance; }
		static Vector3 CalRealPos(Vector3 pos) { return pos + mDistance; }
		static Vector3 CameraPos() { return mDistance; }
		static Vector3 GetMovePos() { return m_vMovePos; }

		static bool GetShock() { return m_bShockCheak; }
		static void SetShock(bool cheak) { m_bShockCheak = cheak; }
		static void SetShockDuration(float time) { m_fShockDuration = time; }


	private:
		void sortGameObjects();
		void renderOpaque();
		void renderCutout();
		void renderTransparent();
		void pushGameObjectToRenderingModes(GameObject* gameObj);

	private:
		static Matrix View;
		static Matrix Projection;

		static Vector3 mResolution;			// 화면 해상도
		static Vector3 mLookPosition;
		static Vector3 mDistance;			// 해상도 중심좌표와 현제 카메라의 간격차
		static Vector3 m_vShockPos;			
		static Vector3 m_vMovePos;			

		static bool		m_bShockCheak;
		static float	m_fShockTime;
		static float	m_fShockDuration;

		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;

		float mNear;
		float mFar;
		float mScale;
		float mFixCam;


		Player*			mTarget;
		Boss_Flime*		mFlime;
		Boss_Ent*		mEnt;

		std::bitset<(UINT)eLayerType::End> mLayerMasks;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutoutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;
	};
}

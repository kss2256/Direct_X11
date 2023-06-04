#include "ksCamera.h"
#include "ksTransform.h"
#include "ksGameObject.h"
#include "ksApplication.h"
#include "ksRenderer.h"
#include "ksScene.h"
#include "ksSceneManager.h"
#include "ksMaterial.h"
#include "ksBaseRenderer.h"
#include "ksSceneManager.h"
#include "ksTime.h"
#include "ksPlayer.h"

extern ks::Application application;

namespace ks
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;
	Vector3 Camera::mResolution = Vector3::Zero;
	Vector3 Camera::mLookPosition = Vector3::Zero;
	Vector3 Camera::mDistance = Vector3::Zero;
	Vector3 Camera::m_vShockPos = Vector3::Zero;
	Vector3 Camera::m_vMovePos = Vector3::Zero;
	bool Camera::m_bShockCheak = false;
	float Camera::m_fShockTime = 0.0f;
	float Camera::m_fShockDuration = 0.0f;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Perspective)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mScale(1.0f)
		, mFixCam(false)
	{
		EnableLayerMasks();
		m_fShockDuration = 0.7f;
	}

	Camera::~Camera()
	{
	}

	void Camera::Initalize()
	{
		RegisterCameraInRenderer();
	}

	void Camera::Update()
	{



	}

	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();

		RegisterCameraInRenderer();
	}

	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		sortGameObjects();

		renderOpaque();
		renderCutout();
		renderTransparent();
	}

	void Camera::CreateViewMatrix()
	{

		//쇼크는 보스 라운드 스테이지에서 다시 수정 할거 m_vMovePos 를 이동하자
		Transform* tr = GetOwner()->GetComponent<Transform>();
		

		if(mFixCam)
		{

			if (m_bShockCheak)
			{
				tr->SetPosition(m_vMovePos);
			}
			else
				tr->SetPosition(mTarget->GetComponent<Transform>()->GetPosition());

				switch (mTarget->GetGroundStage())
				{
				case ks::enums::eGroundStage::Ground1:
				{
					Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();

					if (playerpos.x <= 30.0f && playerpos.x >= 40.67f &&
						playerpos.y <= -6.24f && playerpos.y >= 6.24f)
						return;
					Vec3 fixedpos = playerpos;
					if (playerpos.x <= 30.0f)
					{
						fixedpos.x = 30.0f;
						m_vMovePos.x = 31.f;
					}
					if (playerpos.x >= 40.67f)
					{
						fixedpos.x = 40.67f;
						m_vMovePos.x = 39.67f;
					}
					if (playerpos.y >= 6.24f)
					{
						fixedpos.y = 6.24f;
						m_vMovePos.y = 5.24f;
					}
					if (playerpos.y <= -6.24f)
					{
						fixedpos.y = -6.24f;
						m_vMovePos.y = -5.24f;
					}
					tr->SetPosition(fixedpos);
				}
				break;
				case ks::enums::eGroundStage::Ground2:
				{
					Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();

					if (playerpos.x <= 64.3f && playerpos.x >= 75.7f &&
						playerpos.y <= -6.4f && playerpos.y >= 6.2f)
						return;
					Vec3 fixedpos = playerpos;
					if (playerpos.x <= 64.3f)
						fixedpos.x = 64.3f;
					if (playerpos.x >= 75.7f)
						fixedpos.x = 75.7f;
					if (playerpos.y >= 6.2f)
						fixedpos.y = 6.2f;
					if (playerpos.y <= -6.4f)
						fixedpos.y = -6.4f;
					tr->SetPosition(fixedpos);
				}
				break;
				case ks::enums::eGroundStage::Ground3:
				{
					Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();

					if (playerpos.x <= 99.4f && playerpos.x >= 110.7f &&
						playerpos.y <= -6.3f && playerpos.y >= 6.2f)
						return;
					Vec3 fixedpos = playerpos;
					if (playerpos.x <= 99.4f)
						fixedpos.x = 99.4f;
					if (playerpos.x >= 110.7f)
						fixedpos.x = 110.7f;
					if (playerpos.y >= 6.2f)
						fixedpos.y = 6.2f;
					if (playerpos.y <= -6.3f)
						fixedpos.y = -6.3f;
					tr->SetPosition(fixedpos);
				}
				break;
				case ks::enums::eGroundStage::Ground4:
				{
					Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();

					if (playerpos.x <= 134.4f && playerpos.x >= 145.6f &&
						playerpos.y <= -6.3f && playerpos.y >= 6.18f)
						return;
					Vec3 fixedpos = playerpos;
					if (playerpos.x <= 134.4f)
						fixedpos.x = 134.4f;
					if (playerpos.x >= 145.6f)
						fixedpos.x = 145.6f;
					if (playerpos.y >= 6.18f)
						fixedpos.y = 6.18f;
					if (playerpos.y <= -6.3f)
						fixedpos.y = -6.3f;
					tr->SetPosition(fixedpos);
				}
				break;
				case ks::enums::eGroundStage::Ground5:
				{
					Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();

					if (playerpos.x <= 169.4f && playerpos.x >= 180.6f &&
						playerpos.y <= -6.2f && playerpos.y >= 6.18f)
						return;
					Vec3 fixedpos = playerpos;
					if (playerpos.x <= 169.4f)
						fixedpos.x = 169.4f;
					if (playerpos.x >= 180.6f)
						fixedpos.x = 180.6f;
					if (playerpos.y >= 6.18f)
						fixedpos.y = 6.18f;
					if (playerpos.y <= -6.2f)
						fixedpos.y = -6.2f;
					tr->SetPosition(fixedpos);
				}
				break;
				case ks::enums::eGroundStage::Ground6:
				{
					Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();

					if (playerpos.x <= 204.3f && playerpos.x >= 215.6f &&
						playerpos.y <= -6.2f && playerpos.y >= 6.12f)
						return;
					Vec3 fixedpos = playerpos;
					if (playerpos.x <= 204.3f)
						fixedpos.x = 204.3f;
					if (playerpos.x >= 215.6f)
						fixedpos.x = 215.6f;
					if (playerpos.y >= 6.12f)
						fixedpos.y = 6.12f;
					if (playerpos.y <= -6.2f)
						fixedpos.y = -6.2f;
					tr->SetPosition(fixedpos);
				}
				break;
				case ks::enums::eGroundStage::Ground7:
				{
					Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();

					if (playerpos.x <= 239.4f && playerpos.x >= 250.5f &&
						playerpos.y <= -6.1f && playerpos.y >= 6.15f)
						return;
					Vec3 fixedpos = playerpos;
					if (playerpos.x <= 239.4f)
						fixedpos.x = 239.4f;
					if (playerpos.x >= 250.5f)
						fixedpos.x = 250.5f;
					if (playerpos.y >= 6.15f)
						fixedpos.y = 6.15f;
					if (playerpos.y <= -6.1f)
						fixedpos.y = -6.1f;
					tr->SetPosition(fixedpos);
				}
				break;
				case ks::enums::eGroundStage::Ground8:
				{
					Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();

					if (playerpos.x <= 274.6f && playerpos.x >= 285.5f &&
						playerpos.y <= -6.2f && playerpos.y >= 6.15f)
						return;
					Vec3 fixedpos = playerpos;
					if (playerpos.x <= 274.6f)
						fixedpos.x = 274.6f;
					if (playerpos.x >= 285.5f)
						fixedpos.x = 285.5f;
					if (playerpos.y >= 6.15f)
						fixedpos.y = 6.15f;
					if (playerpos.y <= -6.2f)
						fixedpos.y = -6.2f;
					tr->SetPosition(fixedpos);
				}
				break;
				case ks::enums::eGroundStage::Ground9:
				{
					Vec3 playerpos = mTarget->GetComponent<Transform>()->GetPosition();

					if (playerpos.x <= 309.6f && playerpos.x >= 320.6f &&
						playerpos.y <= -6.2f && playerpos.y >= 6.15f)
						return;
					Vec3 fixedpos = playerpos;
					if (playerpos.x <= 309.6f)
						fixedpos.x = 309.6f;
					if (playerpos.x >= 320.6f)
						fixedpos.x = 320.6f;
					if (playerpos.y >= 6.15f)
						fixedpos.y = 6.15f;
					if (playerpos.y <= -6.2f)
						fixedpos.y = -6.2f;
					tr->SetPosition(fixedpos);
				}
				break;
				}

				if (m_bShockCheak)
				{
					tr->SetPosition(m_vMovePos);
				}

		}		



		Vector3 pos = tr->GetPosition();

		// Crate Translate view matrix
		mView = Matrix::Identity;
		Matrix matr = (mView *= Matrix::CreateTranslation(-pos));
		//회전 정보

		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 foward = tr->Foward();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = foward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = foward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = foward.z;

		mView *= viewRotate;

		

		//if (m_bShockCheak)
		//{

		//	m_fShockTime += Time::DeltaTime();

		//	if (m_fShockTime < 0.1)
		//	{
		//		if (mTarget != nullptr)
		//		{
		//			m_vShockPos = mTarget->GetComponent<Transform>()->GetPosition();
		//			m_vMovePos = m_vShockPos;
		//		}

		//	}
		//	if (m_fShockTime >= 0.1 && m_fShockTime <= 0.7)
		//	{
		//		if (m_vShockPos.x + 0.4f > m_vMovePos.x)
		//		{

		//			m_vMovePos.x += 100.0f * Time::DeltaTime();
		//		}
		//		else
		//		{

		//			m_vMovePos.x -= 100.0f * Time::DeltaTime();
		//		}


		//		tr->SetPosition(m_vMovePos);
		//	}

		//	if (m_fShockTime > 0.7)
		//	{
		//		m_bShockCheak = false;
		//		m_vShockPos = {};
		//		m_fShockTime = 0.f;
		//	}
		//}

		if (m_bShockCheak)
		{
			m_fShockTime += Time::DeltaTime();

			if (mTarget != nullptr)
			{
				m_vShockPos = mTarget->GetComponent<Transform>()->GetPosition();
				m_vMovePos = m_vShockPos;
			}

			if (m_fShockTime >= 0.1 && m_fShockTime <= m_fShockDuration)
			{
				if (m_vShockPos.x + 0.2f > m_vMovePos.x)
				{
					m_vMovePos.x += 100.0f * Time::DeltaTime();
					m_vMovePos.y += 100.0f * Time::DeltaTime();
				}
				else
				{
					m_vMovePos.x -= 100.0f * Time::DeltaTime();
					m_vMovePos.y -= 100.0f * Time::DeltaTime();
				}

				tr->SetPosition(m_vMovePos);
			}

			if (m_fShockTime > m_fShockDuration)
			{
				m_bShockCheak = false;
				m_vShockPos = {};
				m_fShockTime = 0.f;
			}
		}

	}

	void Camera::CreateProjectionMatrix()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = (winRect.right - winRect.left) * mScale;
		float height = (winRect.bottom - winRect.top) * mScale;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH
			(
				XM_2PI / 6.0f
				, mAspectRatio
				, mNear
				, mFar
			);
		}
		else
		{
			mProjection = Matrix::CreateOrthographicLH(width / 100.0f, height / 100.0f, mNear, mFar);
		}
	}

	void Camera::RegisterCameraInRenderer()
	{
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		renderer::cameras[(UINT)type].push_back(this);
	}

	void Camera::TurnLayerMask(eLayerType layer, bool enable)
	{
		mLayerMasks.set((UINT)layer, enable);
	}

	void Camera::sortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutoutGameObjects.clear();
		mTransparentGameObjects.clear();

		Scene* scene = SceneManager::GetActiveScene();
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMasks[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				GameObjects gameObjects = layer.GetGameObjects();
				if (gameObjects.size() == 0)
					continue;

				for (GameObject* obj : gameObjects)
				{
					pushGameObjectToRenderingModes(obj);
				}
			}
		}
	}

	void Camera::renderOpaque()
	{
		for (GameObject* obj : mOpaqueGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::renderCutout()
	{
		for (GameObject* obj : mCutoutGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::renderTransparent()
	{
		for (GameObject* obj : mTransparentGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::pushGameObjectToRenderingModes(GameObject* gameObj)
	{
		BaseRenderer* renderer
			= gameObj->GetComponent<BaseRenderer>();
		if (renderer == nullptr)
			return;

		std::shared_ptr<Material> material = renderer->GetMaterial();
		//if (material == nullptr)
		//	continue;

		eRenderingMode mode = material->GetRenderingMode();

		switch (mode)
		{
		case ks::graphics::eRenderingMode::Opaque:
			mOpaqueGameObjects.push_back(gameObj);
			break;
		case ks::graphics::eRenderingMode::CutOut:
			mCutoutGameObjects.push_back(gameObj);
			break;
		case ks::graphics::eRenderingMode::Transparent:
			mTransparentGameObjects.push_back(gameObj);
			break;
		default:
			break;
		}
	}
}

#include "ksUiMgr.h"
#include "ksInput.h"
#include "ksScene.h"
#include "ksSceneManager.h"
#include "ksLayer.h"
#include "ksUIBase.h"


namespace ks
{

	UIBase* UiMgr::mCurUI = nullptr;
	UIBase* UiMgr::mPriorityUI = nullptr;

	void UiMgr::Update()
	{

		bool lbtnpressed = Input::GetKey(eKeyCode::LBTN);
		bool Lbtndown = Input::GetKeyDown(eKeyCode::LBTN);
		bool Lbtnup = Input::GetKeyUp(eKeyCode::LBTN);
		
		Scene* curscene = SceneManager::GetActiveScene();

		Layer& layer = curscene->GetLayer(eLayerType::UI);
		const std::vector<GameObject*>& gameobject = layer.GetGameObjects();
		

		

		for (size_t i = 0; i < gameobject.size(); ++i)
		{
			mCurUI = ((UIBase*)gameobject[i]);
			

			if (nullptr == mCurUI)
				continue;
			//���콺 �� üũ�� ���÷� ���ָ鼭 true�� ������ false�� �ٲ���� ��
			if (mCurUI->mLbtnUp)
				mCurUI->mLbtnUp = false;

			// ���콺�� �ö��ִٸ� Ŭ�� ����� Ȯ�� �Ұ���			
			if(mCurUI->IsMouseOn())	
			{
				// �̹��� LBTN �� ������ 
				if (Lbtndown)
				{
					// LbtnDown true
					mCurUI->MouseLbtnDown();
					//�������� �����־���.
					if (mCurUI->IsLbtnDown())
					{
						// LbtnPressed true
						mCurUI->MousePressed();
					}
				}

				// �̹��� LBTN �� ������
				else if (Lbtnup)
				{

					// ������ �������� �ִ�.
					if (mCurUI->IsLbtnDown())
					{
						// Ŭ�� �̺�Ʈ ȣ��
						mCurUI->MouseLbtnUp();
						
					}
					mCurUI->mLbtnDown = false;
					mCurUI->mLbtnPressed = false;
					
				}
			}
		}

	}

	UIBase* UiMgr::getPriorityUI(UIBase* ui)
	{




		return nullptr;
	}

}
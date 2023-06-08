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
			//마우스 업 체크는 수시로 해주면서 true면 무조건 false로 바꿔줘야 함
			if (mCurUI->mLbtnUp)
				mCurUI->mLbtnUp = false;

			// 마우스가 올라가있다면 클릭 됬는지 확인 할거임			
			if(mCurUI->IsMouseOn())	
			{
				// 이번에 LBTN 이 눌리면 
				if (Lbtndown)
				{
					// LbtnDown true
					mCurUI->MouseLbtnDown();
					//이전에도 눌려있었다.
					if (mCurUI->IsLbtnDown())
					{
						// LbtnPressed true
						mCurUI->MousePressed();
					}
				}

				// 이번에 LBTN 이 떼졌다
				else if (Lbtnup)
				{

					// 이전에 눌린적이 있다.
					if (mCurUI->IsLbtnDown())
					{
						// 클릭 이벤트 호출
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
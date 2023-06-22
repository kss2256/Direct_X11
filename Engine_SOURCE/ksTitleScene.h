#pragma once
#include "ksScene.h"

namespace ks
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void SetChangeScene(bool change) { m_bChangeScene = change; }

	private:

		bool			m_BgmSound;
		bool			m_bChangeScene;



	};
}

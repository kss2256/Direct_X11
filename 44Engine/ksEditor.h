#pragma once
#include "ksDebugObject.h"
#include "ksEditorObject.h"
#include "ksWidget.h"
#include "ksGraphics.h"

namespace ks
{
	class Editor
	{
	public:
		void Initalize();
		void Run();

		void Update();
		void FixedUpdate();
		void Render();
		void Release();
		void DebugRender(graphics::DebugMesh& mehs);

	private:
		std::vector<Widget*> mWidgets;
		std::vector<EditorObject*> mEditorObjects;
		std::vector<DebugObject*> mDebugObjects;


	};
}

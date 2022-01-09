#pragma once

#include "../Base/IEditorElement.h"

class ToolBar : public  IEditorElement  {

public:
	ToolBar();
	~ToolBar();

	void Show() override;

};
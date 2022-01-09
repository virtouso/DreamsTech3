#pragma once

#include "../Base/IEditorElement.h"

class EditBar : public  IEditorElement  {

public:
	EditBar();
	~EditBar();

	void Show() override;

};
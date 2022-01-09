#include <vector>
#include "../Elements/Base/IEditorElement.h"



class  EditorManager
{
public:
	 EditorManager();
	~ EditorManager();
	void Show();
private:
	std::vector<IEditorElement*> *MainElements;

};


#include <iostream>

class TopBarCreateFunctions
{
public:
    static TopBarCreateFunctions& getInstance()
    {
    
        static TopBarCreateFunctions    instance; 
        return instance;
    }

    void CreateDefaultShapeRendererObject();

private:
    TopBarCreateFunctions() {}                    

public:
    TopBarCreateFunctions(TopBarCreateFunctions const&) = delete;
    void operator=(TopBarCreateFunctions const&) = delete;


};

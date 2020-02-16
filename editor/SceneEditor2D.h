//
//  SceneEditor2D.hpp
//  Voxyc
//
//  Created by Dimitri Lozovoy on 2/13/20.
//  Copyright © 2020 Dimitri Lozovoy. All rights reserved.
//

#ifndef SceneEditor2D_hpp
#define SceneEditor2D_hpp

#include <stdio.h>
#include "../engine/Engine2.h"

class SceneEditor2D
{
public:
    void init();
    void load();
    void tick();
    void touchEvent(int count, int action1, float x1, float y1, int action2, float x2, float y2, int actionIndex, bool ndcCoods = false);
    float scrToGlX(float screenX);
    float scrToGlY(float screenY);
    float glToScrX(float glX);
    float glToScrY(float glY);

private:
    Engine2 *en;
    
    bool modified = false;
    int screenWidth = 1;
    int screenHeight = 1;
    std::string fileSelectorAction = "";
};

#endif /* SceneEditor2D_hpp */

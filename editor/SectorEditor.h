//
//  SectorEditor.hpp
//  Voxyc
//
//  Created by Dimitri Lozovoy on 2/11/20.
//  Copyright © 2020 Dimitri Lozovoy. All rights reserved.
//

#ifndef SectorEditor_hpp
#define SectorEditor_hpp

#include <stdio.h>
#include "../engine/Engine2.h"

class SectorEditor
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
    Engine2 *engine;
    
    bool modified = false;
    int screenWidth = 1;
    int screenHeight = 1;
    std::string fileSelectorAction = "";
};

#endif /* SectorEditor_hpp */

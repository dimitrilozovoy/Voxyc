//
//  SectorEditor.cpp
//  Voxyc
//
//  Created by Dimitri Lozovoy on 2/11/20.
//  Copyright © 2020 Dimitri Lozovoy. All rights reserved.
//

#include "SectorEditor.h"
#include "../engine/Engine2.h"

void SectorEditor::init()
{
    g_engine2->init();
    this->engine = g_engine2;
}

void SectorEditor::load()
{
    engine->setControlsVisible(false);
        
    // Button dimensions
    int numbtns = 6;
    float bw = 0.3;
    float hbw = 0.15;
    float bs = 0.25;
    float bsv = 0.25;
    float hw = 1.0 / numbtns;

//    if (touchControls)
//    {
        // Top buttons
//        engine->addWg("filebtn", WG_BTN, "file.png", "", "filebtnclicked", "", -hw * 5, 0.85, hw, hw);
//        engine->addWg("objbtn", WG_BTN, "shapes.png", "", "objbtnclicked", "", -hw * 3, 0.85, hw, hw);
//        engine->addWg("orthobtn", WG_BTN, "pixels.png", "", "orthobtnclicked", "", -hw, 0.85, hw, hw);

}

void SectorEditor::tick()
{
    GUI *gui = g_engine2->getGUI();
    
    
        // File menu

/*        if (engine->getExtraInt("filebtnclicked") == 1
            || engine->getExtraInt("filebtnclicked") == 3)
        {
//            if (!gui->nonNativeWidgetsShown())
//            {
                gui->clearListMenu();
//                gui->addListMenuOption("New Scene", "");
//                gui->addListMenuOption("Load Scene", "");
//                gui->addListMenuOption("Save Scene", "");
//                gui->addListMenuOption("Run script", "");
//                gui->addListMenuOption("Clear and run script", "");
//                gui->addListMenuOption("README", "");
#ifdef PLATFORM_ANDROID
//                gui->addListMenuOption("Run Sample", "");
//                gui->addListMenuOption("Toggle Map Location", "");
#endif
                gui->showListMenuInDialog("File", "");
//            }

            engine->setExtraInt("filebtnclicked", 0);
        }
        
        if (engine->getExtraStr("listmenuoptionclicked") == "Clear and run script") {
            std::string fname = PLAT_LoadPref("main", "script", "");
            if (fname == "")
                fname = g_assetsDir;

            gui->showFileSelector("lua", fname);
            engine->setExtraStr("listmenuoptionclicked", "");
            fileSelectorAction = "clearandrunscript";
        }
        
                if (engine->getExtraStr("fileselected") != "")
                {
        if (fileSelectorAction == "clearandrunscript") {
                PLAT_SavePref("main", "script", engine->getExtraStr("fileselected"));
                engine->setExtraInt("switchmodule", 1);
                engine->setExtraStr("nextmodule", "luaprogram");
                engine->setExtraStr("loadscript", GetFileName(engine->getExtraStr("fileselected")));
                engine->setExtraStr("assetsdir", GetPath(engine->getExtraStr("fileselected")));
                engine->setExtraStr("fileselected", "");
        }
        }
    
        // 2D voxel editor button
        
        if (engine->getExtraInt("orthobtnclicked") == 1
            || engine->getExtraInt("orthobtnclicked") == 3) {

            if (!modified)
            {
                engine->setExtraInt("switchmodule", 1);
                engine->setExtraStr("nextmodule", "orthoeditor");
                
            }
            else
            {
                gui->clearListMenu();
                gui->addListMenuOption("Discard and Enter 2D Voxel Editor", "");
                gui->addListMenuOption("Cancel", "");
                gui->showListMenuInDialog("Scene not saved!", "");
            }

            engine->setExtraInt("orthobtnclicked", 0);
        }*/
}

void SectorEditor::touchEvent(int count, int action1, float x1, float y1, int action2, float x2, float y2, int actionIndex, bool ndcCoords)
{
    float aspect = (float)screenWidth / (float)screenHeight;
    
    float glx = x1;
    float gly = y1;

    if (!ndcCoords)
    {
        glx = scrToGlX(x1);
        gly = -scrToGlY(y1);
    }
}

float SectorEditor::scrToGlX(float screenX) {
    return 2.0f * screenX / screenWidth - 1.0f;
}

float SectorEditor::scrToGlY(float screenY) {
    return -(2.0f * screenY / screenHeight - 1.0f);
}

float SectorEditor::glToScrX(float glX) {
    return ((glX + 1.0f) / 2.0f) * screenWidth;
}

float SectorEditor::glToScrY(float glY) {
    return screenHeight - abs(((glY + 1.0f) / 2.0f) * screenHeight);
}


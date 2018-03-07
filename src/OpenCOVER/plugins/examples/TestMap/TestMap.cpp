/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#include "TestMap.h"
#include <cover/coVRTui.h>
using namespace osg;

TestMap::TestMap()
{
}

//Constructor of TestMap
bool TestMap::init()
{
    fprintf(stderr, "TestMap::TestMap\n");


    testMapTab = new coTUITab("TestMap", coVRTui::instance()->mainFolder->getID());
    testMapTab->setPos(0, 0);
    tuiMap = new coTUIMap("testMap", testMapTab->getID());
    tuiMap->setPos(0, 0);
	tuiMap->addMap("c:\\tmp\\multi3.jpg", 600.0, 1620.0, 3072.0, 2048.0, 0.0); // TODO

    return true;
}

// this is called if the plugin is removed at runtime
// which currently never happens

// Destructor delets all functions and selections, which have been made, while closing plugin
TestMap::~TestMap()
{
    
    delete testMapTab;
    delete tuiMap;
}

// if a tablet event happened, than the program will look which event it was
void TestMap::tabletEvent(coTUIElement *tUIItem)
{
    if (tUIItem == tuiMap)
    {
    }
}

void TestMap::tabletPressEvent(coTUIElement *tUIItem)
{
    if (tUIItem == tuiMap)
    {
    }
}

void TestMap::preFrame()
{
}

COVERPLUGIN(TestMap)

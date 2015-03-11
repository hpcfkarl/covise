/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl-2.1.txt.

* License: LGPL 2+ */

#ifndef _Car_NODE_PLUGIN_H
#define _Car_NODE_PLUGIN_H

#include <util/common.h>
#include <Thyssen.h>

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

#include <cover/VRViewer.h>
#include <cover/coVRPluginSupport.h>
#include <cover/coVRMSController.h>
#include <cover/coVRPluginSupport.h>
#include <config/CoviseConfig.h>
#include <util/byteswap.h>
#include <net/covise_connect.h>

#include <util/coTypes.h>

#include <vrml97/vrml/config.h>
#include <vrml97/vrml/VrmlNodeType.h>
#include <vrml97/vrml/coEventQueue.h>
#include <vrml97/vrml/MathUtils.h>
#include <vrml97/vrml/System.h>
#include <vrml97/vrml/Viewer.h>
#include <vrml97/vrml/VrmlScene.h>
#include <vrml97/vrml/VrmlNamespace.h>
#include <vrml97/vrml/VrmlNode.h>
#include <vrml97/vrml/VrmlSFBool.h>
#include <vrml97/vrml/VrmlSFFloat.h>
#include <vrml97/vrml/VrmlMFFloat.h>
#include <vrml97/vrml/VrmlSFInt.h>
#include <vrml97/vrml/VrmlSFTime.h>
#include <vrml97/vrml/VrmlMFInt.h>
#include <vrml97/vrml/VrmlNodeChild.h>
#include <vrml97/vrml/VrmlScene.h>
#include <vrml97/vrml/VrmlSFVec3f.h>

#include <net/tokenbuffer.h>

using namespace vrui;
using namespace vrml;
using namespace opencover;
using covise::ServerConnection;
using covise::SimpleServerConnection;
using covise::TokenBuffer;

class VrmlNodeElevator;

class PLUGINEXPORT VrmlNodeCar : public VrmlNodeChild
{
public:
    enum carState {Idle=0,DoorOpening, DoorOpen, DoorClosing, Moving, Rotating, Uninitialized};
    // Define the fields of Car nodes
    static VrmlNodeType *defineType(VrmlNodeType *t = 0);
    virtual VrmlNodeType *nodeType() const;

    VrmlNodeCar(VrmlScene *scene = 0);
    VrmlNodeCar(const VrmlNodeCar &n);
    virtual ~VrmlNodeCar();

    virtual VrmlNode *cloneMe() const;

    virtual VrmlNodeCar *toCar() const;

    virtual ostream &printFields(ostream &os, int indent);

    virtual void setField(const char *fieldName, const VrmlField &fieldValue);
    const VrmlField *getField(const char *fieldName);

    void eventIn(double timeStamp, const char *eventName,
        const VrmlField *fieldValue);

    virtual void render(Viewer *);
    void update();
    void setElevator(VrmlNodeElevator *);
    enum carState getState(){return state;}
    int getLandingNumber(){return landingNumber;};
    void setDestination(int landing, int shaft);
    VrmlSFInt   d_carNumber;
    VrmlSFVec3f d_carPos;
    VrmlSFTime  d_carDoorClose;
    VrmlSFTime  d_carDoorOpen;
    VrmlSFFloat d_doorTimeout;


private:

    VrmlSFFloat d_carAngle;
    float v;
    float a;
    float aMax;
    float vMax;
    float destinationY;
    float destinationX;
    int doorState;
    int landingNumber;
    int shaftNumber;
    double doorTime;
    VrmlNodeElevator *elevator;
    enum carState state;
    double timeoutStart;
};

#endif

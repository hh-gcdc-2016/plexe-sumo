/****************************************************************************/
/// @file    RORouteDef_OrigDest.cpp
/// @author  Daniel Krajzewicz
/// @date    Sept 2002
/// @version $Id$
///
// A route where only the origin and the destination edges are known
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
// copyright : (C) 2001-2007
//  by DLR (http://www.dlr.de/) and ZAIK (http://www.zaik.uni-koeln.de/AFS)
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <string>
#include <iostream>
#include <cassert>
#include "ROEdge.h"
#include "RORouteDef.h"
#include "RORoute.h"
#include "RORouteDef_OrigDest.h"
#include "ROAbstractRouter.h"
#include "ROVehicle.h"
#include "ROVehicleType.h"
#include <utils/common/MsgHandler.h>

#ifdef CHECK_MEMORY_LEAKS
#include <foreign/nvwa/debug_new.h>
#endif // CHECK_MEMORY_LEAKS


// ===========================================================================
// used namespaces
// ===========================================================================
using namespace std;


// ===========================================================================
// member method definitions
// ===========================================================================
RORouteDef_OrigDest::RORouteDef_OrigDest(const std::string &id,
        const RGBColor &color,
        const ROEdge *from,
        const ROEdge *to,
        bool removeFirst)
        : RORouteDef(id, color), myFrom(from), myTo(to), myCurrent(0),
        myRemoveFirst(removeFirst)
{}


RORouteDef_OrigDest::~RORouteDef_OrigDest()
{
    delete myCurrent;
}


const ROEdge * const
RORouteDef_OrigDest::getFrom() const
{
    return myFrom;
}


const ROEdge * const
RORouteDef_OrigDest::getTo() const
{
    return myTo;
}


RORoute *
RORouteDef_OrigDest::buildCurrentRoute(ROAbstractRouter &router,
                                       SUMOTime begin, ROVehicle &veh) const
{
    std::vector<const ROEdge*> edges;
    router.compute(myFrom, myTo, &veh, begin, edges);
    if (myRemoveFirst&&edges.size()>1) {
        edges.erase(edges.begin());
        edges.erase(edges.end()-1);
    }
    return new RORoute(myID, 0, 1, edges);
}


void
RORouteDef_OrigDest::addAlternative(const ROVehicle *const, RORoute *current, SUMOTime begin)
{
    myCurrent = current;
    myStartTime = begin;
}


RORouteDef *
RORouteDef_OrigDest::copy(const std::string &id) const
{
    return new RORouteDef_OrigDest(id, myColor, myFrom, myTo,
                                   myRemoveFirst);
}


const ROEdgeVector &
RORouteDef_OrigDest::getCurrentEdgeVector() const
{
    return myCurrent->getEdgeVector();
}



/****************************************************************************/


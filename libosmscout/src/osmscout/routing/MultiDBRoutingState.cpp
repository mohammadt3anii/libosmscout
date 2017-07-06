/*
  This source is part of the libosmscout library
  Copyright (C) 2016  Tim Teulings
  Copyright (C) 2017  Lukas Karas

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/

#include <osmscout/routing/RoutingService.h>
#include <osmscout/routing/MultiDBRoutingState.h>

namespace osmscout {

  MultiDBRoutingState::MultiDBRoutingState(DatabaseId dbId1,
                                           DatabaseId dbId2,
                                           RoutingProfileRef profile1,
                                           RoutingProfileRef profile2,
                                           std::unordered_map<Id,osmscout::RouteNodeRef> overlapNodes1,
                                           std::unordered_map<Id,osmscout::RouteNodeRef> overlapNodes2):
    dbId1(dbId1),
    dbId2(dbId2),
    profile1(profile1),
    profile2(profile2),
    overlapNodes1(overlapNodes1),
    overlapNodes2(overlapNodes2)
  {
  }

  MultiDBRoutingState::~MultiDBRoutingState()
  {
  }

  Vehicle MultiDBRoutingState::GetVehicle() const
  {
    return profile1->GetVehicle();
  }

  RoutingProfileRef MultiDBRoutingState::GetProfile(DatabaseId database) const
  {
    if (database==dbId1){
      return profile1;
    }else if (database==dbId2){
      return profile2;
    }
    assert(false);
  }

  std::vector<DBFileOffset> MultiDBRoutingState::GetNodeTwins(const DatabaseId database,
                                                              const Id id) const
  {
    std::vector<DBFileOffset> result;
    if (database==dbId1){
      auto it=overlapNodes2.find(id);
      if (it!=overlapNodes2.end()){
        result.push_back(DBFileOffset(dbId2,it->second->GetFileOffset()));
      }
    } else if (database==dbId2){
      auto it=overlapNodes1.find(id);
      if (it!=overlapNodes1.end()){
        result.push_back(DBFileOffset(dbId1,it->second->GetFileOffset()));
      }
    }
    return result;
  }
}

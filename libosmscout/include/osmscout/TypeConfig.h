#ifndef OSMSCOUT_TYPECONFIG_H
#define OSMSCOUT_TYPECONFIG_H

/*
  This source is part of the libosmscout library
  Copyright (C) 2009  Tim Teulings

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

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <osmscout/Tag.h>
#include <osmscout/Types.h>

namespace osmscout {

  const static TagId tagIgnore        = 0;

  const static TypeId typeIgnore      = 0;

  class OSMSCOUT_API Condition
  {
  public:
    virtual ~Condition();

    virtual Condition* Copy() const = 0;
    virtual bool Evaluate(const std::map<TagId,std::string>& tagMap) = 0;
  };

  class OSMSCOUT_API TagEquals : public Condition
  {
  private:
    TagId       tag;
    std::string tagValue;

  public:
    TagEquals(TagId tag,
              const std::string& tagValue);

    Condition* Copy() const;
    bool Evaluate(const std::map<TagId,std::string>& tagMap);
  };

  class OSMSCOUT_API TagNotEquals : public Condition
  {
  private:
    TagId       tag;
    std::string tagValue;

  public:
    TagNotEquals(TagId tag,
                 const std::string& tagValue);

    Condition* Copy() const;
    bool Evaluate(const std::map<TagId,std::string>& tagMap);
  };

  class OSMSCOUT_API TagInfo
  {
  private:
    TagId       id;
    std::string name;
    bool        internalOnly;

  public:
    TagInfo();
    TagInfo(const std::string& name,
            bool internalOnly);

    TagInfo& SetId(TagId id);

    inline std::string GetName() const
    {
      return name;
    }

    inline TagId GetId() const
    {
      return id;
    }

    inline bool IsInternalOnly() const
    {
      return internalOnly;
    }
  };

  class OSMSCOUT_API TypeInfo
  {
  private:
    TypeId      id;
    std::string name;

    Condition   *condition;

    bool        canBeNode;
    bool        canBeWay;
    bool        canBeArea;
    bool        canBeRelation;
    bool        canBeOverview;
    bool        canBeRoute;
    bool        canBeIndexed;

  public:
    TypeInfo();
    TypeInfo(const TypeInfo& other);
    virtual ~TypeInfo();

    void operator=(const TypeInfo& other);

    TypeInfo& SetId(TypeId id);

    TypeInfo& SetType(const std::string& name,
                      Condition* condition);

    inline TypeId GetId() const
    {
      return id;
    }

    inline std::string GetName() const
    {
      return name;
    }

    inline Condition* GetCondition() const
    {
      return condition;
    }

    inline TypeInfo& CanBeNode(bool canBeNode)
    {
      this->canBeNode=canBeNode;

      return *this;
    }

    inline bool CanBeNode() const
    {
      return canBeNode;
    }

    inline TypeInfo& CanBeWay(bool canBeWay)
    {
      this->canBeWay=canBeWay;

      return *this;
    }

    inline bool CanBeWay() const
    {
      return canBeWay;
    }

    inline TypeInfo& CanBeArea(bool canBeArea)
    {
      this->canBeArea=canBeArea;

      return *this;
    }

    inline bool CanBeArea() const
    {
      return canBeArea;
    }

    inline TypeInfo& CanBeRelation(bool canBeRelation)
    {
      this->canBeRelation=canBeRelation;

      return *this;
    }

    inline bool CanBeRelation() const
    {
      return canBeRelation;
    }

    inline TypeInfo& CanBeOverview(bool canBeOverview)
    {
      this->canBeOverview=canBeOverview;

      return *this;
    }

    inline bool CanBeOverview() const
    {
      return canBeOverview;
    }

    inline TypeInfo& CanBeRoute(bool canBeRoute)
    {
      this->canBeRoute=canBeRoute;

      return *this;
    }

    inline bool CanBeRoute() const
    {
      return canBeRoute;
    }

    inline TypeInfo& CanBeIndexed(bool canBeIndexed)
    {
      this->canBeIndexed=canBeIndexed;

      return *this;
    }

    inline bool CanBeIndexed() const
    {
      return canBeIndexed;
    }
  };

  class OSMSCOUT_API TypeConfig
  {
  private:
    std::vector<TagInfo>                            tags;
    std::vector<TypeInfo>                           types;

    TagId                                           nextTagId;
    TypeId                                          nextTypeId;

    std::map<std::string,TagId>                     stringToTagMap;
    std::map<std::string,TypeInfo>                  nameToTypeMap;
    std::map<TypeId,TypeInfo>                       idToTypeMap;

  public:
    TagId                                           tagAdminLevel;
    TagId                                           tagBoundary;
    TagId                                           tagBuilding;
    TagId                                           tagBridge;
    TagId                                           tagLayer;
    TagId                                           tagName;
    TagId                                           tagOneway;
    TagId                                           tagPlace;
    TagId                                           tagPlaceName;
    TagId                                           tagRef;
    TagId                                           tagTunnel;
    TagId                                           tagType;
    TagId                                           tagWidth;

  public:
    TypeConfig();
    virtual ~TypeConfig();

    void RestoreTagInfo(const TagInfo& tagInfo);

    TagId RegisterTagForInternalUse(const std::string& tagName);
    TagId RegisterTagForExternalUse(const std::string& tagName);

    TypeConfig& AddTypeInfo(TypeInfo& typeInfo);

    const std::vector<TagInfo>& GetTags() const;
    const std::vector<TypeInfo>& GetTypes() const;

    TypeId GetMaxTypeId() const;

    TagId GetTagId(const char* name) const;

    const TagInfo& GetTagInfo(TagId id) const;
    const TypeInfo& GetTypeInfo(TypeId id) const;

    void ResolveTags(const std::map<TagId,std::string>& map,
                     std::vector<Tag>& tags) const;

    bool GetNodeTypeId(const std::map<TagId,std::string>& tagMap,
                       TypeId &typeId) const;
    bool GetWayAreaTypeId(const std::map<TagId,std::string>& tagMap,
                          TypeId &wayType,
                          TypeId &areaType) const;
    bool GetRelationTypeId(const std::map<TagId,std::string>& tagMap,
                           TypeId &typeId) const;

    TypeId GetNodeTypeId(const std::string& name) const;
    TypeId GetWayTypeId(const std::string& name) const;
    TypeId GetAreaTypeId(const std::string& name) const;
    TypeId GetRelationTypeId(const std::string& name) const;

    void GetRoutables(std::set<TypeId>& types) const;

    void GetIndexables(std::set<TypeId>& types) const;
  };
}

#endif

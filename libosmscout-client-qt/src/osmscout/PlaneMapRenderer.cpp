/*
  OSMScout - a Qt backend for libosmscout and libosmscout-map
  Copyright (C) 2010  Tim Teulings
  Copyright (C) 2017  Lukáš Karas

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

#include <osmscout/PlaneMapRenderer.h>

PlaneMapRenderer::PlaneMapRenderer(SettingsRef settings,
            DBThreadRef dbThread):
  MapRenderer(settings,dbThread)
{
}

PlaneMapRenderer::~PlaneMapRenderer()
{
}

void PlaneMapRenderer::InvalidateVisualCache()
{
}

/**
 * Render map defined by request to painter
 * @param painter
 * @param request
 * @return true if rendered map is complete
 */
bool PlaneMapRenderer::RenderMap(QPainter& painter,
                                 const RenderMapRequest& request)
{
}

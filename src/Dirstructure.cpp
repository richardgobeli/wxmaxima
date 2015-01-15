//
//  Copyright (C) 2004-2015 Andrej Vodopivec <andrej.vodopivec@gmail.com>
//            (C) 2015      Gunter Königsmann <wxMaxima@physikbuch.de>
//            (C) 2008-2009 Ziga Lenarcic <zigalenarcic@users.sourceforge.net>
//            (C) 2011-2011 cw.ahbong <cw.ahbong@gmail.com>
//            (C) 2012-2013 Doug Ilijev <doug.ilijev@gmail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "Dirstructure.h"

Dirstructure::Dirstructure()
{
  Prefix=wxT(PREFIX);
  UserConfDir=wxGetHomeDir()+wxT("/");
  #if defined __WXMSW__
  RessourcesDir=wxStandardPaths::GetExecutablePath()+wxT("/");
  #elif defined __WXMAC__
  RessourcesDir=wxStandardPaths::GetExecutablePath()+wxT("/wxMaxima.app/Contents/Resources/");
  #else
  RessourcesDir=Prefix+wxT("/share/wxMaxima/");
  #endif  
}

wxString Dirstructure::MaximaDefaultLocation()
{
  #if defined __WXMSW__
  return wxStandardPaths::GetExecutablePath()+wxT("../bin/maxima.bat");
  #elif defined __WXMAC__
  return wxT("/Applications/Maxima.app");
  #else
  return wxT("maxima");
  #endif

  
}

//! If we don't instantiate a Dirstructure the static variables won't exist.
wxString Dirstructure::RessourcesDir;
wxString Dirstructure::Prefix;
wxString Dirstructure::UserConfDir;
Dirstructure dirstruct;

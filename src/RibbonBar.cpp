// -*- mode: c++; c-file-style: "linux"; c-basic-offset: 2; indent-tabs-mode: nil -*-
//
//  Copyright (C) 2004-2015 Andrej Vodopivec <andrej.vodopivec@gmail.com>
//            (C) 2008-2009 Ziga Lenarcic <zigalenarcic@users.sourceforge.net>
//            (C) 2011-2011 cw.ahbong <cw.ahbong@gmail.com>
//            (C) 2012-2013 Doug Ilijev <doug.ilijev@gmail.com>
//            (C) 2014-2016 Gunter Königsmann <wxMaxima@physikbuch.de>
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

/*!\file
  This file defines the contents of the class wxMaxima that contains most of the program's logic. 

  The worksheet is defined in the class MathCtrl instead and 
  everything surrounding it in wxMaximaFrame.
 */

#include "RibbonBar.h"
#include "ToolBar.h"
#include <wx/artprov.h>

RibbonBar::RibbonBar(wxWindow *parent, int id):wxRibbonBar(
  parent,id
  // ,wxDefaultPosition, wxDefaultSize,
  // wxRIBBON_BAR_FLOW_HORIZONTAL
  // | wxRIBBON_BAR_SHOW_PAGE_LABELS
  // | wxRIBBON_BAR_SHOW_PANEL_EXT_BUTTONS
  // | wxRIBBON_BAR_SHOW_TOGGLE_BUTTON
  // | wxRIBBON_BAR_SHOW_HELP_BUTTON
  )
{
  wxRibbonPage* home = new wxRibbonPage(this, wxID_ANY, _("Home"));
  
  wxRibbonPanel *list_panel = new wxRibbonPanel(home, wxID_ANY, _("List"));
  wxRibbonButtonBar *listitems = new wxRibbonButtonBar(list_panel);
  wxBitmap nullBitmap = wxBitmap(10,10);
  listitems->AddButton(ToolBar::tb_find, _("create"),ToolBar::GetImage(wxT("list_new")));
  listitems->AddButton(ToolBar::tb_find, _("first"),ToolBar::GetImage(wxT("list_first")));
  listitems->AddButton(ToolBar::tb_find, _("last"),ToolBar::GetImage(wxT("list_last")));
  listitems->AddButton(ToolBar::tb_find, _("first n"),ToolBar::GetImage(wxT("list_firstn")));
  listitems->AddButton(ToolBar::tb_find, _("last n"),ToolBar::GetImage(wxT("list_lastn")));
  listitems->AddButton(ToolBar::tb_find, _("nth"),ToolBar::GetImage(wxT("list_nth")));
  listitems->AddButton(ToolBar::tb_find, _("append"),ToolBar::GetImage(wxT("list_append")));
  listitems->AddButton(ToolBar::tb_find, _("sort"),ToolBar::GetImage(wxT("list_sort")));
  listitems->AddButton(ToolBar::tb_find, _("extract value"),ToolBar::GetImage(wxT("list_extract")));
  listitems->AddButton(ToolBar::tb_find, _("reverse"),ToolBar::GetImage(wxT("list_reverse")));

  wxRibbonPanel *simplify_panel = new wxRibbonPanel(home, wxID_ANY, _("Simplify"));
  wxRibbonButtonBar *simplify = new wxRibbonButtonBar(simplify_panel);
  simplify->AddButton(ToolBar::tb_find, _("simplify"),nullBitmap);
  simplify->AddButton(ToolBar::tb_find, _("simplify radicals"),nullBitmap);
  simplify->AddButton(ToolBar::tb_find, _("factor"),nullBitmap);
  simplify->AddButton(ToolBar::tb_find, _("factor complex"),nullBitmap);
  simplify->AddButton(ToolBar::tb_find, _("expand"),nullBitmap);
  simplify->AddButton(ToolBar::tb_find, _("expand trigonometric"),nullBitmap);
  simplify->AddButton(ToolBar::tb_find, _("collect terms"),nullBitmap);
  simplify->AddButton(ToolBar::tb_find, _("expand logarithms"),nullBitmap);
  simplify->AddButton(ToolBar::tb_find, _("collect logarithms"),nullBitmap);

  wxRibbonPanel *maxima_panel = new wxRibbonPanel(home, wxID_ANY, _("Maxima"));
  wxRibbonToolBar *maximaBar = new wxRibbonToolBar(maxima_panel);
  maximaBar->AddTool(ToolBar::menu_restart_id,
                     ToolBar::GetImage(wxT("view-refresh")),
                     _("Completely stop maxima and restart it"));
  maximaBar->AddTool(ToolBar::tb_interrupt,
                     ToolBar::GetImage(wxT("gtk-stop")),
                     _("Interrupt current computation. To completely restart maxima press the button left to this one."));
  maximaBar->AddSeparator();
  maximaBar->AddTool(ToolBar::tb_evaltillhere, 
                     ToolBar::GetImage(wxT("go-bottom")),
                     _("Evaluate the file from its beginning to the cell above the cursor"));
  maximaBar->AddSeparator();
  m_followIcon = ToolBar::GetImage(wxT("weather-clear"));
  m_needsInformationIcon = ToolBar::GetImage(wxT("software-update-urgent"));
  maximaBar->AddTool(ToolBar::tb_follow, m_followIcon,
                     _("Return to the cell that is currently being evaluated"));
  maximaBar->EnableTool(ToolBar::tb_follow, false);

  maximaBar->AddTool(ToolBar::tb_hideCode,
                     ToolBar::GetImage(wxT("weather-few-clouds")),
                     _("Toggle the visibility of code cells"));
  maximaBar->SetRows(2,3);
  wxRibbonPanel *edit_panel = new wxRibbonPanel(home, wxID_ANY, _("Edit"));
  wxRibbonToolBar *editBar = new wxRibbonToolBar(edit_panel);
  editBar->AddTool(ToolBar::tb_cut,
                   ToolBar::GetImage(wxT("gtk-cut")),
                   _("Cut selection"));
  editBar->AddTool(ToolBar::tb_copy,
                   ToolBar::GetImage(wxT("gtk-copy")),
                   _("Copy selection"));
  editBar->AddTool(ToolBar::tb_paste, 
                   ToolBar::GetImage(wxT("gtk-paste")),
                   _("Paste from clipboard"));
  editBar->AddSeparator();
  editBar->AddTool(ToolBar::tb_select_all,
                   ToolBar::GetImage(wxT("gtk-select-all")),
                   _("Select all"));
  editBar->AddTool(ToolBar::tb_find,
                   ToolBar::GetImage(wxT("gtk-find")),
                   _("Find and replace"));
  editBar->AddSeparator();
  editBar->SetRows(2,3);
  Realize();
}

#if defined (__WXMSW__) || defined (__WXMAC__)

wxImage RibbonBar::GetImage(wxString name)
{
  Dirstructure dirstructure;
  wxImage img = wxImage(dirstructure.ConfigToolbarDir() + name + wxT(".png"));
  return img;
}

#else
wxBitmap RibbonBar::GetImage(wxString name)
{
  Dirstructure dirstructure;
  wxImage img;
  img = wxArtProvider::GetBitmap(name,wxART_TOOLBAR).ConvertToImage();
  if(!img.IsOk())
    img = wxImage(dirstructure.ConfigToolbarDir() + name + wxT(".png"));
  return img;
}
#endif

/*
 *  Copyright (C) 2004-2005 Andrej Vodopivec <andrejv@users.sourceforge.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "SqrtCell.h"

SqrtCell::SqrtCell() : MathCell()
{
  m_innerCell = NULL;
}


SqrtCell::~SqrtCell()
{
  if (m_innerCell != NULL)
    delete m_innerCell;
  if (m_next != NULL)
    delete m_next;
}

MathCell* SqrtCell::Copy(bool all)
{
  SqrtCell* tmp = new SqrtCell;
  tmp->SetInner(m_innerCell->Copy(true));
  tmp->m_style = m_style;
  if (all && m_nextToDraw!=NULL)
    tmp->AppendCell(m_nextToDraw->Copy(all));
  return tmp;
}

void SqrtCell::Destroy()
{
  if (m_innerCell != NULL)
    delete m_innerCell;
  m_innerCell = NULL;
  m_next = NULL;
}

void SqrtCell::SetInner(MathCell *inner)
{
  if (inner == NULL)
    return;
  if (m_innerCell != NULL)
    delete m_innerCell;
  m_innerCell = inner;
}

void SqrtCell::RecalculateWidths(CellParser& parser, int fontsize, bool all)
{
  double scale = parser.GetScale();
  m_innerCell->RecalculateWidths(parser, fontsize, true);
  m_width = m_innerCell->GetFullWidth(scale) + SCALE_PX(10, scale) +
            3*SCALE_PX(1, scale);
  MathCell::RecalculateWidths(parser, fontsize, all);
}

void SqrtCell::RecalculateSize(CellParser& parser, int fontsize, bool all)
{
  double scale = parser.GetScale();
  m_innerCell->RecalculateSize(parser, fontsize, true);
  m_height = m_innerCell->GetMaxHeight() + SCALE_PX(3, scale);
  m_center = m_innerCell->GetMaxCenter() + SCALE_PX(3, scale);
  MathCell::RecalculateSize(parser, fontsize, all);
}

void SqrtCell::Draw(CellParser& parser, wxPoint point, int fontsize, bool all)
{
  if (DrawThisCell(parser, point)) {
    wxDC& dc = parser.GetDC();
    double scale = parser.GetScale();
    
    wxPoint in(point);
    in.x += SCALE_PX(10, scale) + SCALE_PX(1, scale);
    m_innerCell->Draw(parser, in, fontsize, true);
  
    SetPen(parser);
    dc.DrawLine(point.x,
                point.y,
                point.x + SCALE_PX(3, scale),
                point.y - SCALE_PX(1, scale));
    dc.DrawLine(point.x + SCALE_PX(3, scale),
                point.y - SCALE_PX(1, scale),
                point.x + SCALE_PX(5, scale),
                point.y + m_height - m_center - SCALE_PX(4, scale));
    dc.DrawLine(point.x + SCALE_PX(3, scale) + 1,
                point.y - SCALE_PX(1, scale),
                point.x + SCALE_PX(5, scale) + 1,
                point.y + m_height - m_center - SCALE_PX(4, scale));
    dc.DrawLine(point.x + SCALE_PX(5, scale) + 1,
                point.y + m_height - m_center - SCALE_PX(4, scale),
                point.x + SCALE_PX(10, scale),
                point.y - m_center + SCALE_PX(2, scale));
    dc.DrawLine(point.x + SCALE_PX(10, scale),
                point.y - m_center + SCALE_PX(2, scale),
                point.x + m_width - SCALE_PX(1, scale),
                point.y - m_center + SCALE_PX(2, scale));
    dc.DrawLine(point.x + m_width - SCALE_PX(1, scale),
                point.y - m_center + SCALE_PX(2, scale),
                point.x + m_width - SCALE_PX(1, scale),
                point.y - m_center + SCALE_PX(6, scale));
    UnsetPen(parser);
  }
  MathCell::Draw(parser, point, fontsize, all);
}

wxString SqrtCell::ToString(bool all)
{
  return wxT("sqrt(") + m_innerCell->ToString(true) + wxT(")") +
         MathCell::ToString(all);
}

void SqrtCell::SelectInner(wxRect& rect, MathCell **first, MathCell **last)
{
  *first = NULL;
  *last = NULL;
  
  if (m_innerCell->ContainsRect(rect))
    m_innerCell->SelectRect(rect, first, last);
  
  if (*first == NULL || *last == NULL) {
    *first = this;
    *last = this;
  }
}

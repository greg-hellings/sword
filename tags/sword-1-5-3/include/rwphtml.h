/***************************************************************************
                          rwphtml.h  -  description
                             -------------------
    begin                : Tue Jun 15 15:34:26 CEST 1999

    copyright            : (C) 1999 by Torsten Uhlmann
    email                : TUhlmann@gmx.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/* $Header: /space/oldserver/cvsroot/core/sword/include/Attic/rwphtml.h,v 1.7 2001/12/11 22:35:10 scribe Exp $ */
/* $Revision: 1.7 $ */

#ifndef RWPHTML_H
#define RWPHTML_H

#include <swfilter.h>

#include <defs.h>

  /** this filter converts RWP text to HTML text
  */
class SWDLLEXPORT RWPHTML:public SWFilter
{
public:
  RWPHTML ();
  virtual char ProcessText (char *text, int maxlen, const SWKey * key, const SWModule * = 0);
};

#endif

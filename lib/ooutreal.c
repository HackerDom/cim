/* $Id: $ */

/* Copyright (C) 1997 Sverre Hvammen Johansen,
 * Department of Informatics, University of Oslo.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#define INCLUDE_SIMFILE_H
#include "cim.h"
#include "config.h"

/******************************************************************************
                                       PROCEDURE OUTREAL(r,i,w)              */

__dhp __rooutreal (__bs2FILE *p, double r, long i, long w)
{
  __txt ti;
  long k;
  if (w == 0)
    {
      /* Bruker ikke IMAGE, men oppretter et midlertidig tekstobjekt  og
       * sender den som parameter til __rtputreal */
      static char th[sizeof (__th) + __RTPUTTEXTLENGTH + 1];
      __tobj *tob = (__tobj *) th;
      __txt tv;
      tob->h.konstant = 0;
      tv.obj = tob;
      tv.length = __RTPUTTEXTLENGTH;
      tv.pos = 1;
      tv.start = 1;
      __rtputreal (&tv, r, i);
      __rfield (p, __rputlen);
      p->IMAGE.pos += __rputlen;
      for (k = 0; k < __rputlen; k++)
	__et.obj->string[__et.start - 1 + k] 
	  = tob->string[__RTPUTTEXTLENGTH - __rputlen + k];
    }
  else if (w < 0)
    {
      __rfield (p, -w);		/* Returverdier i __et. */
      ti.obj = __et.obj;
      ti.length = __et.length;
      ti.pos = __et.pos;
      ti.start = __et.start;
      __rtputreal (&ti, r, i);
      __rleftshift (&ti, -w - __rputlen);
      p->IMAGE.pos -= w;
    }
  else
    {
      __rfield (p, w);		/* Returverdier i __et. */
      ti.obj = __et.obj;
      ti.length = __et.length;
      ti.pos = __et.pos;
      ti.start = __et.start;
      (void) __rtputreal (&ti, r, i);
      p->IMAGE.pos += w;
    }
  return ((__dhp) p);
}

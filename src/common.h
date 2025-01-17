/****************************************************************************************
 *
 *  Sapec-NG, Next Generation Symbolic Analysis Program for Electric Circuit
 *  Copyright (C)  2007  Michele Caini
 *
 *
 *  This file is part of Sapec-NG.
 *
 *  Sapec-NG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 *  To contact me:   skypjack@gmail.com
 *
 ***************************************************************************************/

/**
 * \file common.h
 *
 * \brief Common macros, libraries and useful exported functions.
 *
 * This file contains definitions that aim to include some common libraries,
 * define common macros (like memory related functions with errors management),
 * and export prototype for some common functions (like error handling related
 * functions).
 */

/**
 * \brief Useful to manage multiple inclusions
 */
#ifndef COMMON_H
#define COMMON_H 1

#include "config.h"

#include <stdio.h>
#include <sys/types.h>

#ifdef STDC_HEADERS
#  include <stdlib.h>
#  include <string.h>
#elif HAVE_STRINGS_H
#  include <strings.h>
#endif /* STDC_HEADERS */

#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif /* HAVE_UNISTD_H */

#ifdef HAVE_ERRNO_H
#  include <errno.h>
#endif /* HAVE_ERRNO_H */
#ifndef errno
/* Some systems #define this! */
extern int errno;
#endif


#ifndef EXIT_SUCCESS
/** \brief Exit with success */
#  define EXIT_SUCCESS  0
/** \brief Exit with failure */
#  define EXIT_FAILURE  1
#endif

#ifndef NULL
/** \brief NULL */
#  define NULL 0
#endif

#if !HAVE_BZERO && HAVE_MEMSET
# define bzero(buf, bytes) ((void) memset (buf, 0, bytes))
#endif
# define BZERO(buf, bytes) ((void) memset (buf, 0, bytes))

// Flags (Environment Management)

/** \brief Simply, some flags (only 8 bits) */
unsigned short int flags;

/** \brief Used to clear the flags (reset environment) */
#define CLEAR_FLAGS() \
  ( flags &= 0x00 )

/** \brief sets runnable flag */
#define SET_RUNNABLE() \
  ( flags |= 0x01 )

/** \brief gets runnable flag */
#define RUNNABLE() \
  ( flags & 0x01 )

/** \brief sets verbose flag */
#define SET_VERBOSE() \
  ( flags |= 0x02 )

/** \brief gets verbose flag */
#define VERBOSE(str) \
  if( flags & 0x02 ) fprintf(stderr,str)

/** \brief sets info flag */
#define SET_INFO() \
  ( flags |= 0x04 )

/** \brief gets info flag */
#define INFO() \
  ( flags & 0x04 )

/** \brief sets help flag */
#define SET_HELP() \
  ( flags |= 0x08 )

/** \brief gets help flag */
#define HELP() \
  ( flags & 0x08 )

/** \brief sets SapWin compatibility flag */
#define SET_SAPWIN() \
  ( flags |= 0x10 )

/** \brief gets Sapwin compatibility flag */
#define SAPWIN() \
  ( flags & 0x10 )

/** \brief sets binary file flag */
#define SET_BINARY() \
  ( flags |= 0x20 )

/** \brief gets binary file flag */
#define BINARY() \
  ( flags & 0x20 )


// Memory management related functions

extern void*
xcalloc (const size_t num, const size_t size);

extern void*
xmalloc (const size_t num);

extern void*
xrealloc (void *p, const size_t num);

extern char*
xstrdup (const char* str);

/** \brief xcalloc with automatic parameters management */
#define XALLOC(type, num) \
  ((type *) xcalloc ((num), sizeof(type)))
/** \brief xmalloc with automatic parameters management */
#define XMALLOC(type, num) \
  ((type *) xmalloc ((num) * sizeof(type)))
/** \brief xrealloc with automatic parameters management */
#define XREALLOC(type, p, num) \
  ((type *) xrealloc ((p), (num) * sizeof(type)))
/** \brief xfree managed invocation */
#define XFREE(ref) \
  do { if (ref) { free (ref);  ref = 0; } } while (0)


// Error management related function

extern void
warning (const char*);

extern void
error (const char*);

extern void
fatal (const char*);

#endif /* COMMON_H */

//******************************************************************************
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose: logging allocations and releases of memory to a file,
//   especially for use-cases, where Visual-Leeak-Detector
//   or DEBUG_NEW are not appropriate (DLL used by AutoIT-application).
//
//******************************************************************************

#ifndef INC_MEMORYLOG_H
#define INC_MEMORYLOG_H

void log_malloc(int object_type);
void log_delete(int object_type);
void print_log_to_file();

#endif INC_MEMORYLOG_H
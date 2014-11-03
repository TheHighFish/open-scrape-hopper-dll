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
//   or DEBUG_NEW are not appropriate (DLL used by AutoIT-application)
//
//******************************************************************************

#include "stdafx.h"
#include "memory_log.h"

const int kMaxObjectTypesToLog = 100;
int n_allocations[kMaxObjectTypesToLog];
int n_releases[kMaxObjectTypesToLog];

const char *log_filename = "memory.log";

void log_malloc(int object_type) {
  if (object_type < 0) return;
  if (object_type >= kMaxObjectTypesToLog) return;
  ++n_allocations[object_type];
}

void log_delete(int object_type) {
  if (object_type < 0) return;
  if (object_type >= kMaxObjectTypesToLog) return;
  ++n_releases[object_type];
}

void print_log_to_file() {
  FILE *memory_log_file;
  // Open file in append-mode
  memory_log_file = fopen(log_filename, "a");
  if (memory_log_file == NULL) {
    MessageBox(0, "Can't open \"memory.log\" for writing", "ERROR", 0);  
    return;
  }
  fprintf(memory_log_file, "Type    Allocationss        Releases\n");
  fprintf(memory_log_file, "====================================\n");
  for (int i=0; i<kMaxObjectTypesToLog; ++i) {
    if ((n_allocations[i] <= 0) && (n_releases[i] <= 0)) {
      // Skip unused types
      continue;
    }
    fprintf(memory_log_file, "%4i%16i%16i\n", i, n_allocations[i], n_releases[i]);
  }
  fprintf(memory_log_file, "\n\n");
}


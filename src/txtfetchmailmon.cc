/*
 *  Copyright (C) 2003 Guilhem Bonnefille <guilhem.bonnefille@free.fr>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <unistd.h>

#include "version.h"
#include "Controller.h"
#include "ControllerText.h"
#include "MailLogScanner.h"
#include "SyslogReader.h"

const char *file = NULL;

/// Print the usage
/// @param out file the usage must be printed.
/// @param progName the name of the program.
static void
usage(FILE *out, const char *progName)
{
  fprintf(out, "USAGE: %s [-v] [-h] [file]\n", progName);
}

/**
 *@param argc number of arguments
 *@param argv arguments
 */
static void
processArgs(int argc, char *argv[])
{
  extern int optind;
  int c;
  int nbErrors = 0;

  while ((c = getopt(argc, argv, "vh")) != -1)
    {
      switch (c)
        {
        case 'v': // Version is requested
          version(stdout);
          exit(EXIT_SUCCESS);
          break;
        case 'h': // Help is requested
          usage(stdout, argv[0]);
          exit(EXIT_SUCCESS);
          break;
        case '?':
        default:
          nbErrors++;
          break;
        }
    }
  
  if (nbErrors > 0)
    {
      usage(stderr, argv[0]);
      exit(EXIT_FAILURE);
    }

  if (optind < argc)
    {
      file = argv[optind];
      optind++;
    }

  while (optind < argc)
    {
      std::cerr << "Warning: argument ignored: "<<  argv[optind]
           << std::endl;
      optind++;
    }
}

int
main(int argc, char *argv[])
{
  Controller *controller = new ControllerText();
  MailLogScanner *scanner;
  SyslogReader *reader;

  processArgs(argc, argv);

  scanner = new MailLogScanner();
  scanner->setController(controller);
  
  if (file != NULL)
    reader = new SyslogReader(file, SyslogReader::FROM_BEGIN);
  else
    reader = new SyslogReader();

  reader->setScanner(scanner);

  while (1)
  {
    reader->proceed();
    usleep(10000);
  }
  
  return EXIT_SUCCESS;
}

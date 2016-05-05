#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>

#include "config.h"

#include "files.h"
#include "error.h"
#include "stringstore.h"

/* number of infiles in array */
int infilecount;
extern int use_force;

extern void assemble(void);

/* parse commandline arguments */
static void
parse_commandline (int argc, char **argv)
{
  const struct option opts[] = {
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'V'},
    {"verbose", no_argument, NULL, 'v'},
    {"list", optional_argument, NULL, 'l'},
    {"label", optional_argument, NULL, 'L'},
    {"input", required_argument, NULL, 'i'},
    {"output", required_argument, NULL, 'o'},
    {"label-prefix", required_argument, NULL, 'p'},
    {"includepath", required_argument, NULL, 'I'},
    {"force", no_argument, NULL, 'f'},
    {NULL, 0, NULL, 0}
  };
  const char *short_opts = "hVvl::L::i:o:p:I:f";
  int done = 0, i, out = 0;
  infile = NULL;
  while (!done)
    {
      switch (getopt_long (argc, argv, short_opts, opts, NULL))
	{
	case 'h':
	  /* split in two, to avoid too long string constant */
	  printf ("Usage: %s [options] [input files]\n"
		  "\n"
		  "Possible options are:\n"
		  "-h\t--help\t\tDisplay this help text and exit.\n"
		  "-V\t--version\tDisplay version information and exit.\n"
		  "-v\t--verbose\tBe verbose.  "
		  "Specify again to be more verbose.\n"
		  "-l\t--list\t\tWrite a list file.\n"
		  "-L\t--label\t\tWrite a label file.\n", argv[0]);
	  printf ("-p\t--label-prefix\tprefix all labels with this prefix.\n"
		  "-i\t--input\t\tSpecify an input file (-i may be omitted).\n"
		  "-o\t--output\tSpecify the output file.\n"
		  "-I\t--includepath\tAdd a directory to the include path.\n"
		  "Please send bug reports and feature requests to "
		  "<shevek@fmf.nl>\n");
	  exit (0);
	case 'V':
	  printf ("Z80 assembler version " VERSION "\n"
		  "Copyright (C) 2002-2007 Bas Wijnen "
		  "<shevek@fmf.nl>.\n"
		  "Copyright (C) 2005 Jan Wilmans "
		  "<jw@dds.nl>.\n"
		  "Contributors\n"
		  "2016 Peter Kollner <peter@asgalon.net>\n"
		  "\n"
		  "This program comes with ABSOLUTELY NO WARRANTY.\n"
		  "You may distribute copies of the program under the terms\n"
		  "of the GNU General Public License as published by\n"
		  "the Free Software Foundation; either version 2 of the\n"
		  "License, or (at your option) any later version.\n\n"
		  "The complete text of the GPL can be found in\n"
		  "/usr/share/common-licenses/GPL.\n");
	  exit (0);
	case 'v':
	  verbose++;
	  if (verbose >= 5)
	    fprintf (stderr, "Verbosity increased to level %d\n", verbose);
	  break;
	case 'o':
	  realoutputfile
	    = openfile (&out, "output file", stdout, optarg, "wb");
	  realoutputfilename = optarg;
	  if (verbose >= 5)
	    fprintf (stderr, "Opened outputfile\n");
	  break;
	case 'i':
	  open_infile (optarg);
	  break;
	case 'l':
	  reallistfile
	    = openfile (&havelist, "list file", stderr, optarg, "w");
	  if (verbose >= 5)
	    fprintf (stderr, "Opened list file\n");
	  break;
	case 'L':
	  labelfile = openfile (&label, "label file", stderr, optarg, "w");
	  labelfilename = optarg;
	  if (verbose >= 5)
	    fprintf (stderr, "Opened label file\n");
	  break;
	case 'p':
	  labelprefix = optarg;
	  break;
	case 'I':
	  add_include (optarg);
	  break;
	case 'f':
	  use_force = 1;
	  break;
	case -1:
	  done = 1;
	  break;
	default:
	  /* errors are handled by getopt_long */
	  break;
	}
    }
  for (i = optind; i < argc; ++i)
    open_infile (argv[i]);
  if (!infilecount)
    open_infile ("-");
  if (!out)
    realoutputfile = openfile (&out, "output file", stdout, "a.bin", "wb");
  try_use_real_file (realoutputfile, &outfile);
  if (havelist)
    try_use_real_file (reallistfile, &listfile);
}

int
main (int argc, char **argv)
{
  int ret;

  stringstore_init();

  /* default include file location */
  add_include (PKGDATADIR "/headers/");
  parse_commandline (argc, argv);
  if (verbose >= 1)
    fprintf (stderr, "Assembling....\n");
  assemble ();
  if (errors)
    {
      if (errors == 1)
	fprintf (stderr, "*** 1 error found ***\n");
      else
	fprintf (stderr, "*** %d errors found ***\n", errors);
      if (realoutputfile == outfile && !use_force)
	{
	  unlink (realoutputfilename);
	  unlink (labelfilename);
	}
      ret = 1;
    }
  else
    {
      if (verbose >= 1)
	fprintf (stderr, "Assembly succesful.\n");
      ret = 0;
    }

  return ret;
}

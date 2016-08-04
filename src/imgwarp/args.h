/*********************************************************************
ImageWarp - Warp images using projective mapping.
ImageWarp is part of GNU Astronomy Utilities (Gnuastro) package.

Original author:
     Mohammad Akhlaghi <akhlaghi@gnu.org>
Contributing author(s):
Copyright (C) 2015, Free Software Foundation, Inc.

Gnuastro is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

Gnuastro is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with Gnuastro. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/
#ifndef ARGS_H
#define ARGS_H

#include <argp.h>

#include <gnuastro/commonargs.h>
#include <gnuastro/fixedstringmacros.h>










/**************************************************************/
/**************        argp.h definitions       ***************/
/**************************************************************/




/* Definition parameters for the argp: */
const char *argp_program_version=SPACK_STRING"\n"GAL_STRINGS_COPYRIGHT
  "\n\nWritten by Mohammad Akhlaghi";
const char *argp_program_bug_address=PACKAGE_BUGREPORT;
static char args_doc[] = "[matrix.txt] ASTRdata ...";





const char doc[] =
  /* Before the list of options: */
  GAL_STRINGS_TOP_HELP_INFO
  SPACK_NAME" will warp/transform the input image using an input coordinate "
  "matrix. Currently it accepts any general projective mapping (which "
  "includes affine mappings as a subset). \n"
  GAL_STRINGS_MORE_HELP_INFO
  /* After the list of options: */
  "\v"
  PACKAGE_NAME" home page: "PACKAGE_URL;





/* Available letters for short options:

   a c e f g i j k l p r s t u v w x y
   A B C E F G H I J L M O Q R T U W X Y Z

   Number keys used: <=502

   Options with keys (second structure element) larger than 500 do not
   have a short version.
 */
static struct argp_option options[] =
  {
    {
      0, 0, 0, 0,
      "Input:",
      1
    },
    {
      "matrix",
      'm',
      "STR",
      0,
      "Warp/Transform matrix elements.",
      1
    },
    {
      "hstartwcs",
      501,
      "INT",
      0,
      "Header keyword number to start reading WCS.",
      1
    },
    {
      "hendwcs",
      502,
      "INT",
      0,
      "Header keyword number to stop reading WCS.",
      1
    },





    {
      0, 0, 0, 0,
      "Output:",
      2
    },
    {
      "nowcscorrection",
      'n',
      0,
      0,
      "Do not correct input image WCS.",
      2
    },
    {
      "zerofornoinput",
      'z',
      0,
      0,
      "Set pixels with no input to zero not blank.",
      2
    },
    {
      "doubletype",
      'd',
      0,
      0,
      "Do not convert output to input image type.",
      2
    },
    {
      "maxblankfrac",
      'b',
      "FLT",
      0,
      "Maximum fraction of area covered by blank.",
      2
    },



    {
      0, 0, 0, 0,
      "Operating modes:",
      -1
    },


    {0}
  };





/* Parse a single option: */
static error_t
parse_opt(int key, char *arg, struct argp_state *state)
{
  /* Save the arguments structure: */
  struct imgwarpparams *p = state->input;

  /* Set the pointer to the common parameters for all programs
     here: */
  state->child_inputs[0]=&p->cp;

  /* In case the user incorrectly uses the equal sign (for example
     with a short format or with space in the long format, then `arg`
     start with (if the short version was called) or be (if the long
     version was called with a space) the equal sign. So, here we
     check if the first character of arg is the equal sign, then the
     user is warned and the program is stopped: */
  if(arg && arg[0]=='=')
    argp_error(state, "incorrect use of the equal sign (`=`). For short "
               "options, `=` should not be used and for long options, "
               "there should be no space between the option, equal sign "
               "and value");

  switch(key)
    {


    /* Input: */
    case 'm':
      p->up.matrixstring=arg;
      p->up.matrixstringset=1;
      break;
    case 501:
      gal_checkset_sizet_el_zero(arg, &p->hstartwcs, "hstartwcs", key, SPACK,
                                 NULL, 0);
      p->up.hstartwcsset=1;
      break;
    case 502:
      gal_checkset_sizet_el_zero(arg, &p->hendwcs, "hendwcs", key, SPACK,
                                 NULL, 0);
      p->up.hendwcsset=1;
      break;


    /* Output: */
    case 'n':
      p->correctwcs=0;
      break;
    case 'z':
      p->zerofornoinput=1;
      break;
    case 'd':
      p->doubletype=1;
      break;
    case 'b':
      gal_checkset_float_l_0_s_1(arg, &p->maxblankfrac, "maxblankfrac", key,
                                 SPACK, NULL, 0);
      p->up.maxblankfracset=1;
      break;



    /* Read the non-option arguments: */
    case ARGP_KEY_ARG:

      /* See what type of input value it is and put it in. */
      if( gal_fits_name_is_fits(arg) )
        {
          if(p->up.inputname)
            argp_error(state, "only one input image should be given");
          else
            p->up.inputname=arg;
        }
      else
        {
          if(p->up.matrixname)
            argp_error(state, "only one warp/transformation matrix "
                       "should be given");
          else
            p->up.matrixname=arg;
        }
      break;





    /* The command line options and arguments are finished. */
    case ARGP_KEY_END:
      if(p->cp.setdirconf==0 && p->cp.setusrconf==0
         && p->cp.printparams==0)
        {
          if(state->arg_num==0)
            argp_error(state, "no argument given");
          if(p->up.inputname==NULL)
            argp_error(state, "no input FITS image(s) provided");
        }
      break;





    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}





/* Specify the children parsers: */
struct argp_child children[]=
  {
    {&commonargp, 0, NULL, 0},
    {0, 0, 0, 0}
  };





/* Basic structure defining the whole argument reading process. */
static struct argp thisargp = {options, parse_opt, args_doc,
                               doc, children, NULL, NULL};

#endif

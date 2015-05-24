/*********************************************************************
NoiseChisel - Detect and segment signal in noise.
NoiseChisel is part of GNU Astronomy Utilities (Gnuastro) package.

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
along with gnuastro. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/
#include <config.h>

#include <math.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include <fitsio.h>

#include "timing.h"	/* Includes time.h and sys/time.h   */
#include "checkset.h"
#include "txtarrayvv.h"
#include "commonargs.h"
#include "arraymanip.h"
#include "statistics.h"
#include "configfiles.h"
#include "fitsarrayvv.h"

#include "main.h"

#include "ui.h"		        /* Needs main.h                   */
#include "args.h"	        /* Needs main.h, includes argp.h. */


/* Set the file names of the places where the default parameters are
   put. */
#define CONFIG_FILE SPACK CONF_POSTFIX
#define SYSCONFIG_FILE SYSCONFIG_DIR "/" CONFIG_FILE
#define USERCONFIG_FILEEND USERCONFIG_DIR CONFIG_FILE
#define CURDIRCONFIG_FILE CURDIRCONFIG_DIR CONFIG_FILE










/**************************************************************/
/**************       Options and parameters    ***************/
/**************************************************************/
void
readconfig(char *filename, struct noisechiselparams *p)
{
  FILE *fp;
  size_t lineno=0, len=200;
  char *line, *name, *value;
  struct uiparams *up=&p->up;
  struct commonparams *cp=&p->cp;
  char key='a';	/* Not used, just a place holder. */

  /* When the file doesn't exist or can't be opened, it is ignored. It
     might be intentional, so there is no error. If a parameter is
     missing, it will be reported after all defaults are read. */
  fp=fopen(filename, "r");
  if (fp==NULL) return;


  /* Allocate some space for `line` with `len` elements so it can
     easily be freed later on. The value of `len` is arbitarary at
     this point, during the run, getline will change it along with the
     pointer to line. */
  errno=0;
  line=malloc(len*sizeof *line);
  if(line==NULL)
    error(EXIT_FAILURE, errno, "ui.c: %lu bytes in readdefaults",
	  len * sizeof *line);

  /* Read the tokens in the file:  */
  while(getline(&line, &len, fp) != -1)
    {
      /* Prepare the "name" and "value" strings, also set lineno. */
      STARTREADINGLINE;


      /* Inputs: */
      if(strcmp(name, "hdu")==0)
	{
	  if(cp->hduset) continue;
	  errno=0;
	  cp->hdu=malloc(strlen(value)+1);
	  if(cp->hdu==NULL)
	    error(EXIT_FAILURE, errno, "Space for HDU.");
	  strcpy(cp->hdu, value);
	  cp->hduset=1;
	}
      else if(strcmp(name, "mask")==0)
	{
	  if(up->masknameset) continue;
	  errno=0;
	  up->maskname=malloc(strlen(value)+1);
	  if(up->maskname==NULL)
	    error(EXIT_FAILURE, errno, "Space for mask name.");
	  strcpy(up->maskname, value);
	  up->masknameset=1;
	}
      else if(strcmp(name, "mhdu")==0)
	{
	  if(up->mhduset) continue;
	  errno=0;
	  up->mhdu=malloc(strlen(value)+1);
	  if(up->mhdu==NULL)
	    error(EXIT_FAILURE, errno, "Space for mask HDU.");
	  strcpy(up->mhdu, value);
	  up->mhduset=1;
	}
      else if(strcmp(name, "kernel")==0)
	{
	  if(up->kernelnameset) continue;
	  errno=0;
	  up->kernelname=malloc(strlen(value)+1);
	  if(up->kernelname==NULL)
	    error(EXIT_FAILURE, errno, "Space for kernel name.");
	  strcpy(up->kernelname, value);
	  up->kernelnameset=1;
	}
      else if(strcmp(name, "khdu")==0)
	{
	  if(up->khduset) continue;
	  errno=0;
	  up->khdu=malloc(strlen(value)+1);
	  if(up->khdu==NULL)
	    error(EXIT_FAILURE, errno, "Space for kernel HDU.");
	  strcpy(up->khdu, value);
	  up->khduset=1;
	}



      /* Outputs */
      else if(strcmp(name, "output")==0)
	{
	  if(cp->outputset) continue;
	  errno=0;
	  cp->output=malloc(strlen(value)+1);
	  if(cp->output==NULL)
	    error(EXIT_FAILURE, errno, "Space for output");
	  strcpy(cp->output, value);
	  cp->outputset=1;
	}


      /* Mesh grid: */
      else if(strcmp(name, "smeshsize")==0)
	{
	  if(up->smeshsizeset) continue;
          sizetlzero(value, &p->smp.meshsize, name, key, SPACK,
                     filename, lineno);
	  up->smeshsizeset=1;
	}
      else if(strcmp(name, "lmeshsize")==0)
	{
	  if(up->lmeshsizeset) continue;
          sizetlzero(value, &p->lmp.meshsize, name, key, SPACK,
                     filename, lineno);
	  up->lmeshsizeset=1;
	}
      else if(strcmp(name, "nch1")==0)
	{
	  if(up->nch1set) continue;
          sizetlzero(value, &p->smp.nch1, name, key, SPACK,
                     filename, lineno);
	  up->nch1set=1;
	}
      else if(strcmp(name, "nch2")==0)
	{
	  if(up->nch2set) continue;
          sizetlzero(value, &p->smp.nch2, name, key, SPACK,
                     filename, lineno);
	  up->nch2set=1;
	}
      else if(strcmp(name, "lastmeshfrac")==0)
	{
	  if(up->lastmeshfracset) continue;
          floatl0s1(value, &p->smp.lastmeshfrac, name, key, SPACK,
                    filename, lineno);
	  up->lastmeshfracset=1;
	}
      else if(strcmp(name, "numnearest")==0)
	{
	  if(up->numnearestset) continue;
          sizetlzero(value, &p->smp.numnearest, name, key, SPACK,
                     filename, lineno);
	  up->numnearestset=1;
	}
      else if(strcmp(name, "smoothwidth")==0)
	{
	  if(up->smoothwidthset) continue;
          sizetpodd(value, &p->smp.smoothwidth, name, key, SPACK,
                    filename, lineno);
	  up->smoothwidthset=1;
	}


      /* Detection: */
      else if(strcmp(name, "mirrordist")==0)
	{
	  if(up->mirrordistset) continue;
          floatl0(value, &p->smp.mirrordist, name, key, SPACK,
                  filename, lineno);
	  up->mirrordistset=1;
	}
      else if(strcmp(name, "minmodeq")==0)
	{
	  if(up->minmodeqset) continue;
          floatl0s1(value, &p->smp.minmodeq, name, key, SPACK,
                  filename, lineno);
	  up->minmodeqset=1;
	}
      else if(strcmp(name, "qthresh")==0)
	{
	  if(up->qthreshset) continue;
          floatl0s1(value, &p->qthresh, name, key, SPACK,
                  filename, lineno);
	  up->qthreshset=1;
	}
      else if(strcmp(name, "sigclipmultip")==0)
	{
	  if(up->sigclipmultipset) continue;
          floatl0(value, &p->smp.sigclipmultip, name, key, SPACK,
                  filename, lineno);
	  up->sigclipmultipset=1;
	}
      else if(strcmp(name, "sigcliptolerance")==0)
	{
	  if(up->sigcliptoleranceset) continue;
          floatl0s1(value, &p->smp.sigcliptolerance, name, key, SPACK,
                  filename, lineno);
	  up->sigcliptoleranceset=1;
	}


      /* Operating modes: */
      else if(strcmp(name, "numthreads")==0)
	{
	  if(cp->numthreadsset) continue;
	  sizetlzero(value, &cp->numthreads, name, key, SPACK,
		     filename, lineno);
	  cp->numthreadsset=1;
	}


      else
	error_at_line(EXIT_FAILURE, 0, filename, lineno,
		      "`%s` not recognized.\n", name);
    }

  free(line);
  fclose(fp);
}





void
printvalues(FILE *fp, struct noisechiselparams *p)
{
  struct uiparams *up=&p->up;
  struct commonparams *cp=&p->cp;
  struct meshparams *smp=&p->smp, *lmp=&p->lmp;

  /* Print all the options that are set. Separate each group with a
     commented line explaining the options in that group. */
  fprintf(fp, "\n# Input:\n");
  if(cp->hduset)
    {
      if(stringhasspace(cp->hdu))
	fprintf(fp, CONF_SHOWFMT"\"%s\"\n", "hdu", cp->hdu);
      else
	fprintf(fp, CONF_SHOWFMT"%s\n", "hdu", cp->hdu);
    }
  if(up->masknameset)
    {
      if(stringhasspace(up->maskname))
	fprintf(fp, CONF_SHOWFMT"\"%s\"\n", "mask", up->maskname);
      else
	fprintf(fp, CONF_SHOWFMT"%s\n", "mask", up->maskname);
    }
  if(up->mhdu)
    {
      if(stringhasspace(up->mhdu))
	fprintf(fp, CONF_SHOWFMT"\"%s\"\n", "mhdu", up->mhdu);
      else
	fprintf(fp, CONF_SHOWFMT"%s\n", "mhdu", up->mhdu);
    }
  if(up->kernelnameset)
    {
      if(stringhasspace(up->kernelname))
	fprintf(fp, CONF_SHOWFMT"\"%s\"\n", "kernel", up->kernelname);
      else
	fprintf(fp, CONF_SHOWFMT"%s\n", "kernel", up->kernelname);
    }
  if(up->khdu)
    {
      if(stringhasspace(up->khdu))
	fprintf(fp, CONF_SHOWFMT"\"%s\"\n", "khdu", up->khdu);
      else
	fprintf(fp, CONF_SHOWFMT"%s\n", "khdu", up->khdu);
    }


  fprintf(fp, "\n# Output:\n");
  if(cp->outputset)
    fprintf(fp, CONF_SHOWFMT"%s\n", "output", cp->output);


  fprintf(fp, "\n# Mesh grid:\n");
  if(up->smeshsizeset)
    fprintf(fp, CONF_SHOWFMT"%lu\n", "smeshsize", smp->meshsize);
  if(up->lmeshsizeset)
    fprintf(fp, CONF_SHOWFMT"%lu\n", "lmeshsize", lmp->meshsize);
  if(up->nch1set)
    fprintf(fp, CONF_SHOWFMT"%lu\n", "nch1", smp->nch1);
  if(up->nch2set)
    fprintf(fp, CONF_SHOWFMT"%lu\n", "nch2", smp->nch2);
  if(up->lastmeshfracset)
    fprintf(fp, CONF_SHOWFMT"%.3f\n", "lastmeshfrac", smp->lastmeshfrac);
  if(up->numnearestset)
    fprintf(fp, CONF_SHOWFMT"%lu\n", "numnearest", smp->numnearest);
  if(up->smoothwidthset)
    fprintf(fp, CONF_SHOWFMT"%lu\n", "smoothwidth", smp->smoothwidth);


  fprintf(fp, "\n# Detection:\n");
  if(up->mirrordistset)
    fprintf(fp, CONF_SHOWFMT"%.3f\n", "mirrordist", smp->mirrordist);
  if(up->minmodeqset)
    fprintf(fp, CONF_SHOWFMT"%.3f\n", "minmodeq", smp->minmodeq);
  if(up->qthreshset)
    fprintf(fp, CONF_SHOWFMT"%.3f\n", "qthresh", p->qthresh);
  if(up->sigclipmultipset)
    fprintf(fp, CONF_SHOWFMT"%.3f\n", "sigclipmultip", smp->sigclipmultip);
  if(up->sigcliptoleranceset)
    fprintf(fp, CONF_SHOWFMT"%.3f\n", "sigcliptolerance",
            smp->sigcliptolerance);
}






/* Note that numthreads will be used automatically based on the
   configure time. */
void
checkifset(struct noisechiselparams *p)
{
  struct uiparams *up=&p->up;
  struct commonparams *cp=&p->cp;

  int intro=0;
  if(cp->hduset==0)
    REPORT_NOTSET("hdu");
  if(up->khduset==0)
    REPORT_NOTSET("khdu");
  if(up->numnearestset==0)
    REPORT_NOTSET("numnearest");
  if(up->smoothwidthset==0)
    REPORT_NOTSET("smoothwidth");

  /* Mesh grid: */
  if(up->smeshsizeset==0)
    REPORT_NOTSET("smeshsize");
  if(up->lmeshsizeset==0)
    REPORT_NOTSET("lmeshsize");
  if(up->nch1set==0)
    REPORT_NOTSET("nch1");
  if(up->nch2set==0)
    REPORT_NOTSET("nch2");
  if(up->lastmeshfracset==0)
    REPORT_NOTSET("lastmeshfrac");

  /* Detection: */
  if(up->mirrordistset==0)
    REPORT_NOTSET("mirrordist");
  if(up->minmodeqset==0)
    REPORT_NOTSET("minmodeq");
  if(up->qthreshset==0)
    REPORT_NOTSET("qthresh");
  if(up->sigclipmultipset==0)
    REPORT_NOTSET("sigclipmultip");
  if(up->sigcliptoleranceset==0)
    REPORT_NOTSET("sigcliptolerance");

  END_OF_NOTSET_REPORT;
}




















/**************************************************************/
/***************       Sanity Check         *******************/
/**************************************************************/
void
sanitycheck(struct noisechiselparams *p)
{
  struct meshparams *smp=&p->smp, *lmp=&p->lmp;

  /* Set the maskname and mask hdu accordingly: */
  CHECKMASKNAMEANDHDU(SPACK);

  /* Set the output name: */
  if(p->cp.output)
    checkremovefile(p->cp.output, p->cp.dontdelete);
  else
    automaticoutput(p->up.inputname, "_detected.fits", p->cp.removedirinfo,
		p->cp.dontdelete, &p->cp.output);

  /* Set the check image names: */
  if(p->meshname)
    {
      p->meshname=NULL;           /* Was not allocated before!  */
      automaticoutput(p->up.inputname, "_meshs.fits", p->cp.removedirinfo,
                      p->cp.dontdelete, &p->meshname);
    }
  if(p->detectionname)
    {
      p->detectionname=NULL;           /* Was not allocated before!  */
      automaticoutput(p->up.inputname, "_det.fits", p->cp.removedirinfo,
                      p->cp.dontdelete, &p->detectionname);
    }

  /* Other checks: */
  if(smp->numnearest<MINACCEPTABLENEAREST)
    error(EXIT_FAILURE, 0, "The smallest possible number for `--numnearest' "
          "(`-n') is %d. You have asked for: %lu.", MINACCEPTABLENEAREST,
          smp->numnearest);

  /* Set the parameters for both mesh grids. */
  lmp->nch1=smp->nch1;
  lmp->nch2=smp->nch2;
  lmp->fullsmooth=smp->fullsmooth;
  lmp->numnearest=smp->numnearest;
  lmp->smoothwidth=smp->smoothwidth;
  lmp->lastmeshfrac=smp->lastmeshfrac;
  lmp->fullinterpolation=smp->fullinterpolation;
  lmp->numthreads=smp->numthreads=p->cp.numthreads;
}



















/**************************************************************/
/***************       Preparations         *******************/
/**************************************************************/
/* The default PSF. It was created with the following set of
   commands. The crop is because the first and last rows of all PSFs
   made by MakeProfiles is blank (zero).

      $ cat tmp.txt
      0    0.0    0.0   2   2   0   0   1   1   5
      $ export GSL_RNG_TYPE=ranlxs2
      $ export GSL_RNG_SEED=1
      $ astmkprof tmp.txt --oversample=1 --envseed            \
                  --numrandom=10000 --tolerance=0.01
      $ astimgcrop 0.fits --section=2:*,2:* --zeroisnotblank
      $ astconvertt 0_crop.fits --output=fwhm2.txt
*/
size_t defaultkernel_s0=11;
size_t defaultkernel_s1=11;
float defaultkernel[121]=
  {
    0, 0, 0, 0, 0, 2.58073e-08, 0, 0, 0, 0, 0,

    0, 0, 2.90237e-08, 6.79851e-07, 4.4435e-06, 8.31499e-06,
    4.50166e-06, 6.97185e-07, 3.00904e-08, 0, 0,

    0, 2.87873e-08, 2.48435e-06, 5.81339e-05, 0.000379508, 0.000709334,
    0.000383714, 5.94125e-05, 2.56498e-06, 3.00032e-08, 0,

    0, 6.70501e-07, 5.77826e-05, 0.00134992, 0.00879665, 0.0164126,
    0.00886609, 0.00137174, 5.92134e-05, 6.92853e-07, 0,

    0, 4.3798e-06, 0.000376616, 0.00877689, 0.0570404, 0.106142, 0.0572108,
    0.00883846, 0.000381257, 4.46059e-06, 0,

    2.54661e-08, 8.24845e-06, 0.00070725, 0.0164287, 0.10639, 0.19727,
    0.106003, 0.0163402, 0.000703951, 8.23152e-06, 2.55057e-08,

    0, 4.5229e-06, 0.000386632, 0.00894947, 0.0577282, 0.106614, 0.0570877,
    0.00877699, 0.000377496, 4.41036e-06, 0,

    0, 7.1169e-07, 6.0678e-05, 0.00140013, 0.00899917, 0.0165582, 0.00883658,
    0.00135509, 5.81823e-05, 6.79067e-07, 0,

    0, 3.12002e-08, 2.65502e-06, 6.11192e-05, 0.000391739, 0.000718637,
    0.000382453, 5.85194e-05, 2.50864e-06, 2.9249e-08, 0,

    0, 0, 3.14197e-08, 7.22146e-07, 4.61954e-06, 8.45613e-06, 4.49082e-06,
    6.85919e-07, 2.9364e-08, 0, 0,

    0, 0, 0, 0, 0, 2.63305e-08, 0, 0, 0, 0, 0
  };





void
preparearrays(struct noisechiselparams *p)
{
  int kbitpix;
  size_t knumblank;
  float *f, *ff, *fp, sum;
  struct meshparams *smp=&p->smp;

  /* Read the input image in. Note that the pointer to the image is
     also kept in p->img. Since some of the mesh operations should be
     done on the convolved image and some on the actual image, we will
     need to change the mesh's img value some times and the p->img
     will be used to keep its actual value. */
  filetofloat(p->up.inputname, p->up.maskname, p->cp.hdu, p->up.mhdu,
              &smp->img, &p->bitpix, &p->numblank, &smp->s0, &smp->s1);
  readfitswcs(p->up.inputname, p->cp.hdu, &p->nwcs, &p->wcs);
  p->lmp.s0=smp->s0;
  p->lmp.s1=smp->s1;
  p->img=p->lmp.img=smp->img;

  /* make sure the channel sizes fit the channel sizes. */
  if( smp->s0%smp->nch2 || smp->s1%smp->nch1 )
    error(EXIT_FAILURE, 0, "The input image size (%lu x %lu) is not an "
          "exact multiple of the number of the given channels (%lu, %lu) "
          "in the respective axis.", smp->s1, smp->s0, smp->nch1, smp->nch2);

  /* Read the kernel: */
  if(p->up.kernelnameset)
    {
      filetofloat(p->up.kernelname, NULL, p->up.khdu, 0, &smp->kernel,
                  &kbitpix, &knumblank, &smp->ks0, &smp->ks1);
      if(knumblank)
        {
          fp=(f=smp->kernel)+smp->ks0*smp->ks1;
          do if(isnan(*f)) *f=0.0f; while(++f<fp);
        }
      sum=floatsum(smp->kernel, smp->ks0*smp->ks1);
      fmultipconst(smp->kernel, smp->ks0*smp->ks1, 1/sum);
    }
  else
    {
      errno=0;
      smp->ks0=defaultkernel_s0;
      smp->ks1=defaultkernel_s1;
      smp->kernel=malloc(smp->ks0*smp->ks1*sizeof *smp->kernel);
      if(smp->kernel==NULL)
        error(EXIT_FAILURE, errno, "%lu bytes for default kernel",
              smp->ks0*smp->ks1);
      ff=defaultkernel;
      fp=(f=smp->kernel)+smp->ks0*smp->ks1;
      do *f=*ff++; while(++f<fp);
    }
}



















/**************************************************************/
/************         Set the parameters          *************/
/**************************************************************/
void
setparams(int argc, char *argv[], struct noisechiselparams *p)
{
  struct commonparams *cp=&p->cp;

  /* Set the non-zero initial values, the structure was initialized to
     have a zero value for all elements. */
  cp->spack         = SPACK;
  cp->verb          = 1;
  cp->numthreads    = DP_NUMTHREADS;
  cp->removedirinfo = 1;

  /* Read the arguments. */
  errno=0;
  if(argp_parse(&thisargp, argc, argv, 0, 0, p))
    error(EXIT_FAILURE, errno, "Parsing arguments");

  /* Add the user default values and save them if asked. */
  CHECKSETCONFIG;

  /* Check if all the required parameters are set. */
  checkifset(p);

  /* Print the values for each parameter. */
  if(cp->printparams)
    REPORT_PARAMETERS_SET;

  /* Do a sanity check. */
  sanitycheck(p);

  /* Make the array of input images. */
  preparearrays(p);

  /* Everything is ready, notify the user of the program starting. */
  if(cp->verb)
    {
      printf(SPACK_NAME" started on %s", ctime(&p->rawtime));
      printf("  - Input read: %s (hdu: %s)\n", p->up.inputname, p->cp.hdu);
      if(p->up.maskname)
        printf("  - Mask read: %s (hdu: %s)\n", p->up.maskname, p->up.mhdu);
      if(p->up.kernelnameset)
        printf("  - Kernel read: %s (hdu: %s)\n", p->up.kernelname,
               p->up.khdu);
      else
        printf("  - Kernel: FWHM=2 pixel Gaussian.\n");
    }
}




















/**************************************************************/
/************      Free allocated, report         *************/
/**************************************************************/
void
freeandreport(struct noisechiselparams *p, struct timeval *t1)
{
  /* Free the allocated arrays: */
  free(p->img);
  free(p->cp.hdu);
  free(p->up.mhdu);
  free(p->up.khdu);
  free(p->cp.output);
  free(p->smp.kernel);
  if(p->up.maskname && p->up.maskname!=p->up.inputname)
    free(p->up.maskname);
  free(p->up.kernelname);

  /* Free all the allocated names: */
  if(p->meshname) free(p->meshname);
  if(p->detectionname) free(p->detectionname);

  /* Free the WCS structure: */
  if(p->wcs)
    wcsvfree(&p->nwcs, &p->wcs);

  /* Print the final message. */
  reporttiming(t1, SPACK_NAME" finished in: ", 0);
}
/*********************************************************************
Spectral lines.
This is part of GNU Astronomy Utilities (Gnuastro) package.

Original author:
     Mohammad Akhlaghi <mohammad@akhlaghi.org>
Contributing author(s):
Copyright (C) 2019-2022 Free Software Foundation, Inc.

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
#ifndef __GAL_SPECLINES_H__
#define __GAL_SPECLINES_H__

/* Include other headers if necessary here. Note that other header files
   must be included before the C++ preparations below */
#include <gnuastro/error.h>

/* C++ Preparations */
#undef __BEGIN_C_DECLS
#undef __END_C_DECLS
#ifdef __cplusplus
# define __BEGIN_C_DECLS extern "C" {
# define __END_C_DECLS }
#else
# define __BEGIN_C_DECLS                /* empty */
# define __END_C_DECLS                  /* empty */
#endif
/* End of C++ preparations */



/* Actual header contants (the above were for the Pre-processor). */
__BEGIN_C_DECLS  /* From C++ preparations */


/* Spectral line internal codes (SORT BY WAVELENGTH). */
enum gal_speclines_line_codes
{
  /* Allowing '0' to be identied as a known-non-line. */
  GAL_SPECLINES_INVALID=0,

  /* Main list of recognized lines. */
  GAL_SPECLINES_SIIRED,
  GAL_SPECLINES_SII,
  GAL_SPECLINES_SIIBLUE,
  GAL_SPECLINES_NIIRED,
  GAL_SPECLINES_NII,
  GAL_SPECLINES_HALPHA,
  GAL_SPECLINES_NIIBLUE,
  GAL_SPECLINES_OIIIRED_VIS,
  GAL_SPECLINES_OIII_VIS,
  GAL_SPECLINES_OIIIBLUE_VIS,
  GAL_SPECLINES_HBETA,
  GAL_SPECLINES_HEII_VIS,
  GAL_SPECLINES_HGAMMA,
  GAL_SPECLINES_HDELTA,
  GAL_SPECLINES_HEPSILON,
  GAL_SPECLINES_NEIII,
  GAL_SPECLINES_OIIRED,
  GAL_SPECLINES_OII,
  GAL_SPECLINES_OIIBLUE,
  GAL_SPECLINES_BLIMIT,
  GAL_SPECLINES_MGIIRED,
  GAL_SPECLINES_MGII,
  GAL_SPECLINES_MGIIBLUE,
  GAL_SPECLINES_CIIIRED,
  GAL_SPECLINES_CIII,
  GAL_SPECLINES_CIIIBLUE,
  GAL_SPECLINES_SiIIIRED,
  GAL_SPECLINES_SiIII,
  GAL_SPECLINES_SiIIIBLUE,
  GAL_SPECLINES_OIIIRED_UV,
  GAL_SPECLINES_OIII_UV,
  GAL_SPECLINES_OIIIBLUE_UV,
  GAL_SPECLINES_HEII_UV,
  GAL_SPECLINES_CIVRED,
  GAL_SPECLINES_CIV,
  GAL_SPECLINES_CIVBLUE,
  GAL_SPECLINES_NV,
  GAL_SPECLINES_LYALPHA,
  GAL_SPECLINES_LYBETA,
  GAL_SPECLINES_LYGAMMA,
  GAL_SPECLINES_LYDELTA,
  GAL_SPECLINES_LYEPSILON,
  GAL_SPECLINES_LYLIMIT,

  /* This should be the last element (to keep the total number of
     lines). */
  GAL_SPECLINES_INVALID_MAX,
};


/* Spectral lines wavelengths in Angstroms (SORT BY WAVELENGTH). */
#define GAL_SPECLINES_ANGSTROM_SIIRED    6731
#define GAL_SPECLINES_ANGSTROM_SII       6724
#define GAL_SPECLINES_ANGSTROM_SIIBLUE   6717
#define GAL_SPECLINES_ANGSTROM_NIIRED    6584
#define GAL_SPECLINES_ANGSTROM_NII       6566
#define GAL_SPECLINES_ANGSTROM_HALPHA    6562.8
#define GAL_SPECLINES_ANGSTROM_NIIBLUE   6548
#define GAL_SPECLINES_ANGSTROM_OIIIRED_VIS 5007
#define GAL_SPECLINES_ANGSTROM_OIII_VIS  4983
#define GAL_SPECLINES_ANGSTROM_OIIIBLUE_VIS 4959
#define GAL_SPECLINES_ANGSTROM_HBETA     4861.36
#define GAL_SPECLINES_ANGSTROM_HEII_VIS  4686
#define GAL_SPECLINES_ANGSTROM_HGAMMA    4340.46
#define GAL_SPECLINES_ANGSTROM_HDELTA    4101.74
#define GAL_SPECLINES_ANGSTROM_HEPSILON  3970.07
#define GAL_SPECLINES_ANGSTROM_NEIII     3869
#define GAL_SPECLINES_ANGSTROM_OIIRED    3729
#define GAL_SPECLINES_ANGSTROM_OII       3727.5
#define GAL_SPECLINES_ANGSTROM_OIIBLUE   3726
#define GAL_SPECLINES_ANGSTROM_BLIMIT    3646
#define GAL_SPECLINES_ANGSTROM_MGIIRED   2803
#define GAL_SPECLINES_ANGSTROM_MGII      2799.5
#define GAL_SPECLINES_ANGSTROM_MGIIBLUE  2796
#define GAL_SPECLINES_ANGSTROM_CIIIRED   1909
#define GAL_SPECLINES_ANGSTROM_CIII      1908
#define GAL_SPECLINES_ANGSTROM_CIIIBLUE  1907
#define GAL_SPECLINES_ANGSTROM_SiIIIRED  1892
#define GAL_SPECLINES_ANGSTROM_SiIII     1887.5
#define GAL_SPECLINES_ANGSTROM_SiIIIBLUE 1883
#define GAL_SPECLINES_ANGSTROM_OIIIRED_UV 1666
#define GAL_SPECLINES_ANGSTROM_OIII_UV   1663.5
#define GAL_SPECLINES_ANGSTROM_OIIIBLUE_UV 1661
#define GAL_SPECLINES_ANGSTROM_HEII_UV   1640
#define GAL_SPECLINES_ANGSTROM_CIVRED    1551
#define GAL_SPECLINES_ANGSTROM_CIV       1549.5
#define GAL_SPECLINES_ANGSTROM_CIVBLUE   1548
#define GAL_SPECLINES_ANGSTROM_NV        1240
#define GAL_SPECLINES_ANGSTROM_LYALPHA   1215.67
#define GAL_SPECLINES_ANGSTROM_LYBETA    1025.7
#define GAL_SPECLINES_ANGSTROM_LYGAMMA   972.54
#define GAL_SPECLINES_ANGSTROM_LYDELTA   949.74
#define GAL_SPECLINES_ANGSTROM_LYEPSILON 937.80
#define GAL_SPECLINES_ANGSTROM_LYLIMIT   912


/* Spectral line name strings (SORT BY WAVELENGTH). */
#define GAL_SPECLINES_NAME_SIIRED    "siired"
#define GAL_SPECLINES_NAME_SII       "sii"
#define GAL_SPECLINES_NAME_SIIBLUE   "siiblue"
#define GAL_SPECLINES_NAME_NIIRED    "niired"
#define GAL_SPECLINES_NAME_NII       "nii"
#define GAL_SPECLINES_NAME_HALPHA    "halpha"
#define GAL_SPECLINES_NAME_NIIBLUE   "niiblue"
#define GAL_SPECLINES_NAME_OIIIRED_VIS "oiiired-vis"
#define GAL_SPECLINES_NAME_OIII_VIS  "oiii-vis"
#define GAL_SPECLINES_NAME_OIIIBLUE_VIS "oiiiblue-vis"
#define GAL_SPECLINES_NAME_HBETA     "hbeta"
#define GAL_SPECLINES_NAME_HEII_VIS  "heii-vis"
#define GAL_SPECLINES_NAME_HGAMMA    "hgamma"
#define GAL_SPECLINES_NAME_HDELTA    "hdelta"
#define GAL_SPECLINES_NAME_HEPSILON  "hepsilon"
#define GAL_SPECLINES_NAME_NEIII     "neiii"
#define GAL_SPECLINES_NAME_OIIRED    "oiired"
#define GAL_SPECLINES_NAME_OII       "oii"
#define GAL_SPECLINES_NAME_OIIBLUE   "oiiblue"
#define GAL_SPECLINES_NAME_BLIMIT    "blimit"
#define GAL_SPECLINES_NAME_MGIIRED   "mgiired"
#define GAL_SPECLINES_NAME_MGII      "mgii"
#define GAL_SPECLINES_NAME_MGIIBLUE  "mgiiblue"
#define GAL_SPECLINES_NAME_CIIIRED   "ciiired"
#define GAL_SPECLINES_NAME_CIII      "ciii"
#define GAL_SPECLINES_NAME_CIIIBLUE  "ciiiblue"
#define GAL_SPECLINES_NAME_SiIIIRED  "si_iiired"
#define GAL_SPECLINES_NAME_SiIII     "si_iii"
#define GAL_SPECLINES_NAME_SiIIIBLUE "si_iiiblue"
#define GAL_SPECLINES_NAME_OIIIRED_UV "oiiired-uv"
#define GAL_SPECLINES_NAME_OIII_UV   "oiii-uv"
#define GAL_SPECLINES_NAME_OIIIBLUE_UV "oiiiblue-uv"
#define GAL_SPECLINES_NAME_HEII_UV   "heii-uv"
#define GAL_SPECLINES_NAME_CIVRED    "civred"
#define GAL_SPECLINES_NAME_CIV       "civ"
#define GAL_SPECLINES_NAME_CIVBLUE   "civblue"
#define GAL_SPECLINES_NAME_NV        "nv"
#define GAL_SPECLINES_NAME_LYALPHA   "lyalpha"
#define GAL_SPECLINES_NAME_LYBETA    "lybeta"
#define GAL_SPECLINES_NAME_LYGAMMA   "lygamma"
#define GAL_SPECLINES_NAME_LYDELTA   "lydelta"
#define GAL_SPECLINES_NAME_LYEPSILON "lyepsilon"
#define GAL_SPECLINES_NAME_LYLIMIT   "lylimit"





/*********************************************************************/
/*************        Internal names and codes         ***************/
/*********************************************************************/
char *
gal_speclines_line_name(int linecode);

int
gal_speclines_line_code(char *name);

double
gal_speclines_line_angstrom(int linecode);





/*********************************************************************/
/*************             Redshifted lines            ***************/
/*********************************************************************/
double
gal_speclines_line_redshift(double obsline, double restline);

double
gal_speclines_line_redshift_code(double obsline, int linecode);


__END_C_DECLS    /* From C++ preparations */

#endif           /* __GAL_COSMOLOGY_H__ */

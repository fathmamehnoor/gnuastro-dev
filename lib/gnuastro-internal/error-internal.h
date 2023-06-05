/*********************************************************************
Function to abort the program when an error occurs.
This is part of GNU Astronomy Utilities (Gnuastro) package.

Original author:
     Fathma Mehnoor <fathmamehnoor@gmail.com>

Copyright (C) 2015-2022 Free Software Foundation, Inc.

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
void
errorـinternal_check_abort(gal_error_t *err)
{
    if(err)
      {
         error(EXIT_FAILURE, 0, "%s: Error!." 
         "Aborting the program", __func__);
         abort();
      }
}
/*********************************************************************
Functions for linked lists.
This is part of GNU Astronomy Utilities (Gnuastro) package.

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
#ifndef __GAL_SLL_H__
#define __GAL_SLL_H__



/******************* Two doubles (for coordinates) */
struct gal_linkedlist_tdll
{
    double a;
    double b;
    struct gal_linkedlist_tdll *next;
};

void
gal_linkedlist_add_to_tdll(struct gal_linkedlist_tdll **list,
                           double a, double b);

void
gal_linkedlist_pop_from_tdll(struct gal_linkedlist_tdll **list,
                             double *a, double *b);

size_t
gal_linkedlist_num_int_dll(struct gal_linkedlist_tdll *list);

void
gal_linkedlist_tdll_to_array_inv(struct gal_linkedlist_tdll *list,
                                 double **d, size_t *num);

void
gal_linkedlist_free_tdll(struct gal_linkedlist_tdll *list);




















/******************* float: */
struct gal_linkedlist_fll
{
    float v;
    struct gal_linkedlist_fll *next;
};

void
gal_linkedlist_print_fll_array(struct gal_linkedlist_fll **afll, size_t num);

void
gal_linkedlist_add_to_fll(struct gal_linkedlist_fll **list, float value);

void
gal_linkedlist_pop_from_fll(struct gal_linkedlist_fll **list, float *value);

size_t
gal_linkedlist_num_in_fll(struct gal_linkedlist_fll *list);

void
gal_linkedlist_fll_to_array(struct gal_linkedlist_fll *list,
                            float **f, size_t *num);

void
gal_linkedlist_free_fll(struct gal_linkedlist_fll *list);

void
gal_linkedlist_free_fll_array(struct gal_linkedlist_fll **afll, size_t num);




















/******************* String: */
struct gal_linkedlist_stll
{
    char *v;
    struct gal_linkedlist_stll *next;
};
void
gal_linkedlist_add_to_stll(struct gal_linkedlist_stll **list, char *value);

void
gal_linkedlist_pop_from_stll(struct gal_linkedlist_stll **list, char **value);

void
gal_linkedlist_print_stll(struct gal_linkedlist_stll *list);

size_t
gal_linkedlist_num_in_stll(struct gal_linkedlist_stll *list);

















/******************* size_t: */
struct gal_linkedlist_sll
{
    size_t v;
    struct gal_linkedlist_sll *next;
};

void
add_to_sll(struct gal_linkedlist_sll **list, size_t value);

void
pop_from_sll(struct gal_linkedlist_sll **list, size_t *value);

size_t
numinsll(struct gal_linkedlist_sll *list);

void
gal_linkedlist_print_sll(struct gal_linkedlist_sll *list);

void
gal_linkedlist_sll_to_array(struct gal_linkedlist_sll *list,
                            size_t **f, size_t *num);

void
gal_linkedlist_free_sll(struct gal_linkedlist_sll *list);




















/******************* Two way size_t: */
struct gal_linkedlist_tsll
{
  size_t v;
  struct gal_linkedlist_tsll *next;
  struct gal_linkedlist_tsll *prev;
};

void
gal_linkedlist_add_to_tsll_end(struct gal_linkedlist_tsll **last,
                               size_t value);

void
gal_linkedlist_pop_from_tsll_start(struct gal_linkedlist_tsll **first,
                                   size_t *value);




















/******************* Ordered size_t: */
struct gal_linkedlist_osll
{
  size_t v;			/* The actual value. */
  float s;			/* The parameter to sort by. */
  struct gal_linkedlist_osll *next;
};

void
gal_linkedlist_add_to_osll(struct gal_linkedlist_osll **list,
                           size_t value, float tosort);

void
gal_linkedlist_pop_from_osll(struct gal_linkedlist_osll **list,
                             size_t *value, float *sortvalue);

void
gal_linkedlist_osll_into_sll(struct gal_linkedlist_osll *in,
                             struct gal_linkedlist_sll **out);




















/******************* Two way ordered size_t: */
struct gal_linkedlist_tosll
{
  size_t v;
  float s;
  struct gal_linkedlist_tosll *prev;
  struct gal_linkedlist_tosll *next;
};

void
gal_linkedlist_print_tosll(struct gal_linkedlist_tosll *l,
                           struct gal_linkedlist_tosll *s);

void
gal_linkedlist_add_to_tosll_end(struct gal_linkedlist_tosll **largest,
                                struct gal_linkedlist_tosll **smallest,
                                size_t value, float tosort);

void
gal_linkedlist_pop_from_tosll_start(struct gal_linkedlist_tosll **lartest,
                                    struct gal_linkedlist_tosll **smallest,
                                    size_t *value, float *tosort);

void
gal_linkedlist_smallest_tosll(struct gal_linkedlist_tosll *largest,
                              struct gal_linkedlist_tosll **smallest);

void
gal_linkedlist_tosll_into_sll(struct gal_linkedlist_tosll *in,
                              struct gal_linkedlist_sll **out);

void
gal_linkedlist_tosll_free(struct gal_linkedlist_tosll *largest);

#endif

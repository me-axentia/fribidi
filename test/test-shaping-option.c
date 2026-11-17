/* FriBidi
 * test-shaping-option.c - check fribidi_log2vis() against the shaping
 * build option
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library, in a file named COPYING; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA
 *
 * For licensing issues, contact <fribidi.license@gmail.com>.
 */

/* With shaping support, brackets in a right-to-left run are mirrored.
 * Built with -Dshaping=false / --disable-shaping, the visual string is
 * only reordered.  Levels and position maps must be the same either way,
 * and must not depend on whether a visual string is requested. */

#include <stdio.h>
#include <string.h>
#include <fribidi.h>

#define LEN 3

int
main (void)
{
  /* "(" ALEF ")" in a right-to-left paragraph */
  const FriBidiChar input[LEN] = { 0x0028, 0x05D0, 0x0029 };
#ifdef FRIBIDI_NO_SHAPING
  const FriBidiChar expected_visual[LEN] = { 0x0029, 0x05D0, 0x0028 };
#else
  const FriBidiChar expected_visual[LEN] = { 0x0028, 0x05D0, 0x0029 };
#endif
  const FriBidiStrIndex expected_l2v[LEN] = { 2, 1, 0 };
  const FriBidiLevel expected_levels[LEN] = { 1, 1, 1 };
  FriBidiChar visual[LEN];
  FriBidiStrIndex l2v[LEN], v2l[LEN], l2v_nv[LEN], v2l_nv[LEN];
  FriBidiLevel levels[LEN], levels_nv[LEN];
  FriBidiParType base_dir;
  int failed = 0;

  base_dir = FRIBIDI_PAR_RTL;
  if (!fribidi_log2vis (input, LEN, &base_dir, visual, l2v, v2l, levels))
    {
      fprintf (stderr, "fribidi_log2vis() failed\n");
      return 1;
    }

  base_dir = FRIBIDI_PAR_RTL;
  if (!fribidi_log2vis (input, LEN, &base_dir, NULL, l2v_nv, v2l_nv,
			levels_nv))
    {
      fprintf (stderr, "fribidi_log2vis() without visual_str failed\n");
      return 1;
    }

  if (memcmp (visual, expected_visual, sizeof visual) != 0)
    {
      fprintf (stderr, "unexpected visual string: %04X %04X %04X\n",
	       (unsigned) visual[0], (unsigned) visual[1],
	       (unsigned) visual[2]);
      failed = 1;
    }
  if (memcmp (l2v, expected_l2v, sizeof l2v) != 0
      || memcmp (levels, expected_levels, sizeof levels) != 0)
    {
      fprintf (stderr, "unexpected levels or L2V map\n");
      failed = 1;
    }
  if (memcmp (l2v, l2v_nv, sizeof l2v) != 0
      || memcmp (v2l, v2l_nv, sizeof v2l) != 0
      || memcmp (levels, levels_nv, sizeof levels) != 0)
    {
      fprintf (stderr, "results differ with and without visual_str\n");
      failed = 1;
    }

  return failed;
}

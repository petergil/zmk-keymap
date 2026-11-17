/*
 * Kyria (rev1-rev3, stock 50-key "6 Column" layout) layout for the 34-key
 * keymap. Key positions follow zmk-helpers' key-labels/kyria.h.
 *
 * The 34 keys go on the inner 5 columns and the middle two of the five thumb
 * keys per side (LH2 LH1 | RH1 RH2). Every other key is bound to &none on all
 * layers:
 *   - outer pinky column (LT5 LM5 LB5 / RT5 RM5 RB5)
 *   - the four inner bottom-row keys (LF1 LF0 | RF0 RF1)
 *   - the innermost thumb key per side (LH0 | RH0)
 *   - the two outer thumb keys per side (LH4 LH3 | RH3 RH4)
 *
 * See layout.h for the PG_LAYOUT / PG_THUMB_* contract.
 */

#pragma once

#include "zmk-helpers/key-labels/kyria.h"

// Logical 34-key thumbs -> physical Kyria thumb positions.
#define PG_THUMB_L_OUTER LH2
#define PG_THUMB_L_INNER LH1
#define PG_THUMB_R_INNER RH1
#define PG_THUMB_R_OUTER RH2

#define PG_LAYOUT(                                                            \
    k0,  k1,  k2,  k3,  k4,       k5,  k6,  k7,  k8,  k9,                     \
    k10, k11, k12, k13, k14,      k15, k16, k17, k18, k19,                    \
    k20, k21, k22, k23, k24,      k25, k26, k27, k28, k29,                    \
                   k30, k31,      k32, k33)                                   \
    &none k0  k1  k2  k3  k4                          k5  k6  k7  k8  k9  &none \
    &none k10 k11 k12 k13 k14                         k15 k16 k17 k18 k19 &none \
    &none k20 k21 k22 k23 k24 &none &none &none &none k25 k26 k27 k28 k29 &none \
          &none &none k30 k31 &none                   &none k32 k33 &none &none

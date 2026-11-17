/*
 * Default layout: conventional 34-key split (5x3 per side + 2 thumbs per
 * side), e.g. cradio, zaphod. Key positions follow zmk-helpers'
 * key-labels/34.h, and PG_LAYOUT is the identity mapping.
 *
 * See layout.h for the PG_LAYOUT contract.
 */

#pragma once

#include "zmk-helpers/key-labels/34.h"

#define PG_THUMB_L_OUTER LH1
#define PG_THUMB_L_INNER LH0
#define PG_THUMB_R_INNER RH0
#define PG_THUMB_R_OUTER RH1

#define PG_LAYOUT(                                                            \
    k0,  k1,  k2,  k3,  k4,       k5,  k6,  k7,  k8,  k9,                     \
    k10, k11, k12, k13, k14,      k15, k16, k17, k18, k19,                    \
    k20, k21, k22, k23, k24,      k25, k26, k27, k28, k29,                    \
                   k30, k31,      k32, k33)                                   \
    k0  k1  k2  k3  k4            k5  k6  k7  k8  k9                          \
    k10 k11 k12 k13 k14           k15 k16 k17 k18 k19                         \
    k20 k21 k22 k23 k24           k25 k26 k27 k28 k29                         \
                k30 k31           k32 k33

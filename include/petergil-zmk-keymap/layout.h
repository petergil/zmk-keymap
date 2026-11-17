/*
 * Physical layout selection.
 *
 * The layers in keymap.dtsi are written as 34 logical keys (5x3 per side,
 * then thumbs LH1 LH0 RH0 RH1) passed to PG_LAYOUT(...), which expands them
 * into the board's actual `bindings` order. combos.dtsi uses the PG_THUMB_*
 * positions defined by the same layout header, so bindings and combos always
 * agree.
 *
 * A layout header must:
 *   - include the matching zmk-helpers key-labels header,
 *   - define PG_LAYOUT(k0, ..., k33), expanding to that board's bindings in
 *     position order, with &none (or anything else) in the extra positions,
 *     and
 *   - define PG_THUMB_L_OUTER, PG_THUMB_L_INNER, PG_THUMB_R_INNER,
 *     PG_THUMB_R_OUTER as the physical key positions that PG_LAYOUT puts
 *     k30, k31, k32, k33 on.
 *
 * Default is layouts/34.h. To use another layout, include it before
 * keymap.dtsi (or combos.dtsi), e.g.:
 *
 *   #include "petergil-zmk-keymap/layouts/kyria.h"
 *   #include "petergil-zmk-keymap/keymap.dtsi"
 */

#pragma once

#ifndef PG_LAYOUT
#include "petergil-zmk-keymap/layouts/34.h"
#endif

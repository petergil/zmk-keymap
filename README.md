# petergil-zmk-keymap

A generic, board-agnostic ZMK keymap for 34-key split keyboards (5 columns x 3
rows per side, plus 4 thumb keys), extracted from
[zaphod-config](https://github.com/petejohanson/zaphod-config)'s
`boards/arm/zaphod/zaphod.keymap`. Meant to be pulled in via west by a
board/shield-specific `*-config` repo (e.g. `cradio-config`) and combined with
that board's own `.conf`/`.overlay`/`build.yaml`.

Provides, via a single `#include "petergil-zmk-keymap/keymap.dtsi"`:
- 7 layers: Base, Nav, Other, Num, Sym, Media, Fun
- Home-row mod behavior `&hm`
- Two thumb-cluster combos for the Media/Fun layers
- A handful of custom Unicode characters, including Swedish letters:
  `&euro_sign`, `&bang`, `&irony`, `&checkmark`, `&cross`, `&shamrock`,
  `&rad`, `&bio`, `&CCCP`, `&lighting`, `&sv_ae`, `&sv_ao`, `&sv_oe`

Individual pieces (`layers.h`, `behaviors.dtsi`, `chars.dtsi`, `combos.dtsi`)
can also be included standalone if you only want part of this.

## Layouts

The keymap is written as 34 logical keys per layer (5 columns x 3 rows per
side, then thumbs `LH1 LH0 RH0 RH1`), passed to a `PG_LAYOUT(...)` macro that
expands them into the board's physical `bindings` order. A layout header
provides both that macro and the matching
[zmk-helpers](https://github.com/urob/zmk-helpers) key-labels header, so the
combos in `combos.dtsi` always use positions that match the bindings.

| Header | Boards | Notes |
|---|---|---|
| `layouts/34.h` (default) | cradio, zaphod, other 34-key splits | identity mapping |
| `layouts/kyria.h` | Kyria rev1–rev3 (50-key) | inner 5 columns + middle two of the five thumbs per side; all other keys `&none` |

To use a non-default layout, include it before `keymap.dtsi` (see Usage).
Adding a board means writing a new `layouts/<board>.h`; see `layout.h` for
what it must define.

If the layout header doesn't match the board (e.g. a 50-key board with the
default 34-key layout), keys and combos will **silently** land on the wrong
positions rather than fail to build.

## Dependency: zmk-helpers

This repo depends on [urob/zmk-helpers](https://github.com/urob/zmk-helpers)
(the project formerly known as `zmk-nodefree-config`) for `helper.h` (used by
`chars.dtsi`) and `key-labels/34.h` (used by `combos.dtsi`), declared as a
west project in this repo's own `west.yml`. For a consumer to pick this up
transitively, its west manifest must `import` this repo's `west.yml` (see
below) — a plain project entry without `import` will *not* pull in
zmk-helpers, and the build will fail loudly with missing-include errors.

Both this repo and zmk-helpers are real Zephyr modules (`zephyr/module.yml`
with `dts_root: .`), so all includes — ours and zmk-helpers' — are
root-relative (e.g. `"zmk-helpers/helper.h"`, `"petergil-zmk-keymap/keymap.dtsi"`)
rather than relative paths. This means, unlike a plain vendored/relative-path
setup, it does **not** depend on where west happens to check out each project
in the workspace.

## Usage

In the consumer's west manifest (e.g. `config/west.yml`), add a project entry
that imports this repo's manifest:

```yaml
projects:
  - name: petergil-zmk-keymap
    url: https://github.com/petergil/zmk-keymap
    revision: main
    import: west.yml
```

Use `https://`, not `git@github.com:...` — ZMK builds typically run in CI (e.g.
GitHub Actions) without your personal SSH key, so an SSH URL will fail to
clone there.

In the board/shield's `.keymap` file:

```c
#include <behaviors.dtsi>
#include <dt-bindings/zmk/keys.h>
#include <dt-bindings/zmk/bt.h>
#include <dt-bindings/zmk/pointing.h>

#define HOST_OS 1  // see zmk-helpers' README for values
// #include "petergil-zmk-keymap/layouts/kyria.h"  // only for non-34-key boards
#include "petergil-zmk-keymap/keymap.dtsi"
```

And in the board/shield's `.conf`, enable mouse support (used by the Nav
layer's `&mmv`/`&mkp`/`&msc` bindings):

```
CONFIG_ZMK_POINTING=y
```

## Known gaps / not yet done

- Swedish letters and the emoji/symbol Unicode characters are personal to
  Peter and not really "generic" — they're included here for now but are
  candidates for splitting out once it's confirmed how a consumer should
  selectively opt in/out of extras like this.
- Not build-tested with `west` (unavailable in the environment this was
  written in) — verify with an actual `west update && west build` before
  relying on it.

# petergil-zmk-keymap

A generic, board-agnostic ZMK keymap for 34-key split keyboards (5 columns x 3
rows per side, plus 4 thumb keys), extracted from
[zaphod-config](https://github.com/petejohanson/zaphod-config)'s
`boards/arm/zaphod/zaphod.keymap`. Meant to be pulled in via west by a
board/shield-specific `*-config` repo (e.g. `cradio-config`) and combined with
that board's own `.conf`/`.overlay`/`build.yaml`.

Provides:
- 7 layers: Base, Nav, Other, Num, Sym, Media, Fun (`keymap.dtsi`)
- Home-row mod behavior `&hm` (`behaviors.dtsi`)
- Two thumb-cluster combos for the Media/Fun layers (`combos.dtsi`)
- A handful of custom Unicode characters: `&euro_sign`, `&bang`, `&irony`,
  `&checkmark`, `&cross`, `&shamrock`, `&rad`, `&bio`, `&CCCP`, `&lighting`
  (`chars.dtsi`)

## Layout assumption

Everything here assumes the consuming board's keymap `bindings` list uses the
conventional 34-key ordering documented in
[zmk-nodefree-config](https://github.com/urob/zmk-nodefree-config)'s
`keypos_def/keypos_34keys.h`: 5 columns x 3 rows per side, then 4 thumb keys
ordered `LH1 LH0 RH0 RH1`. Both `zaphod` and `cradio` follow this. If a board's
thumb ordering or key count differs, the combos in `combos.dtsi` will
**silently** bind to the wrong physical keys rather than fail to build —
verify against that board's actual bindings order before reusing this module.

## Dependency: zmk-nodefree-config

This repo depends on [urob/zmk-nodefree-config](https://github.com/urob/zmk-nodefree-config)
for `helper.h` (used by `chars.dtsi`) and `keypos_def/keypos_34keys.h` (used
by `combos.dtsi`), declared as a west project in this repo's own `west.yml`.
For a consumer to pick this up transitively, its west manifest must `import`
this repo's `west.yml` (see below) — a plain project entry without `import`
will *not* pull in zmk-nodefree-config, and the build will fail loudly with
missing-include errors.

All includes in this repo use relative paths (e.g. `../zmk-nodefree-config/helper.h`),
matching zmk-nodefree-config's own documented convention. This assumes the
default west layout, where every project is checked out as a sibling
directory directly under the workspace topdir (no project uses a custom
`path:` override). If a consumer's manifest overrides paths, these relative
includes break at compile time (a loud, not silent, failure).

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

Note: the `name:` field controls the local checkout directory name (and thus
the relative include paths below), independent of the GitHub repo name
(`zmk-keymap`). Keep it as `petergil-zmk-keymap` unless you also update the
`../petergil-zmk-keymap/...` includes throughout this repo and consumers.

In the board/shield's `.keymap` file, include in this order:

```c
#include <behaviors.dtsi>
#include <dt-bindings/zmk/keys.h>
#include <dt-bindings/zmk/bt.h>
#include <dt-bindings/zmk/pointing.h>

#define HOST_OS 1  // see zmk-nodefree-config's README for values
#include "../zmk-nodefree-config/helper.h"
#include "../zmk-nodefree-config/international_chars/swedish.dtsi"
#include "../zmk-nodefree-config/keypos_def/keypos_34keys.h"

#include "../petergil-zmk-keymap/layers.h"
#include "../petergil-zmk-keymap/behaviors.dtsi"
#include "../petergil-zmk-keymap/chars.dtsi"
#include "../petergil-zmk-keymap/combos.dtsi"
#include "../petergil-zmk-keymap/keymap.dtsi"
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

---
description: NXP i.MX95 15x15 FRDM board with Mali-G310 GPU
authors: Nguyen Minh Tien <zizuzacker@gmail.com>
---

### Machine frdm-imx95

NXP FRDM i.MX95 (15x15, LPDDR4x) board support.

GPU rendering uses NXP's proprietary Mali stack (mali-imx) on the Mali-G310,
providing virtual/egl, virtual/libgbm and virtual/libgles*. To fall back to
Mesa software rendering, see the render-path notes in agl_frdm-imx95.inc.

#### Required: clone NXP's meta-imx layer first

This board is not present in AGL's scarthgap meta-freescale, so it depends on
NXP's vendor meta-imx layer (walnascar), which is NOT part of the AGL repo
manifest. Clone it before running aglsetup.sh:

    git clone --depth=1 -b walnascar-6.12.49-2.2.0 \
      https://github.com/nxp-imx/meta-imx.git \
      bsp/meta-imx

Only its meta-imx-bsp sub-layer is used; the machine template adds it to
bblayers automatically. aglsetup.sh will stop with an error if it is missing.

The companion machine config conf/machine/frdm-imx95.conf lives in
meta-freescale (a separate git repo) and is also required.

#### Setup

    git clone -b walnascar-6.12.49-2.2.0 https://github.com/nxp-imx/meta-imx.git bsp/meta-imx
    source meta-agl/scripts/aglsetup.sh -m frdm-imx95 -f agl-devel
    bitbake agl-image-minimal

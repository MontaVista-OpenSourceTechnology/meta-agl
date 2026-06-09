require conf/include/agl_imx-common.inc

IMX_DEFAULT_BSP = "nxp"

# Force BSP-specific overrides for mx95.
# meta-freescale bans raw :mx95 overrides via MACHINEOVERRIDES_EXTENDER_FILTER_OUT.
# Without this line, every recipe seeing :mx95 in MACHINEOVERRIDES raises SkipRecipe.
# Value matches MACHINEOVERRIDES_EXTENDER:mx95:use-nxp-bsp in imx-base.inc, INCLUDING
# imxgpu/imxmali/imxgpu2d/imxgpu3d. These overrides make meta-freescale's mesa bbappend
# strip egl/gbm/gles from Mesa, so the proprietary Mali stack (mali-imx) provides them
# instead — i.e. real GPU (Mali-G310) rendering, not Mesa software/CPU rendering.
MACHINEOVERRIDES_EXTENDER:mx95:forcevariable = "imx-generic-bsp:imx-nxp-bsp:imxdrm:imxdpu:imxgpu:imxmali:imxgpu2d:imxgpu3d:mx9-generic-bsp:mx9-nxp-bsp:mx95-generic-bsp:mx95-nxp-bsp"

# OP-TEE: imx95-evk.inc adds "optee" to MACHINE_FEATURES which pulls in
# packagegroup-fsl-optee-imx -> optee-client. That recipe is skipped because
# AGL's meta-agl-core/files/group has no static ID for the "teeclnt" group.
# Remove for AGL porting phase. Re-enable in Y2 when TEE is needed.
MACHINE_FEATURES:remove = "optee"

# Prefer NXP's linux-imx (6.12, has FRDM DTB) over meta-freescale's linux-fslc-imx (6.6)
# Must use :mx95-nxp-bsp not :mx95 — raw :mx95 is banned (see MACHINEOVERRIDES_EXTENDER above)
PREFERRED_PROVIDER_virtual/kernel:mx95-nxp-bsp = "linux-imx"

# Prefer NXP's u-boot-imx from meta-imx-bsp (has imx95_15x15_frdm defconfig)
PREFERRED_PROVIDER_virtual/bootloader:mx95-nxp-bsp = "u-boot-imx"
PREFERRED_PROVIDER_u-boot:mx95-nxp-bsp            = "u-boot-imx"

# GPU rendering — route EGL/GLES/GBM to NXP's proprietary Mali stack (mali-imx,
# libmali.so) so the Mali-G310 does the work instead of the CPU. With imxgpu/imxgpu3d
# now in MACHINEOVERRIDES, meta-freescale's mesa bbappend strips egl/gbm/gles from Mesa,
# so mali-imx is the only provider — but pin it explicitly to be unambiguous.
# Mesa still provides desktop GL (virtual/libgl) via swrast; Mali does not ship libGL.
PREFERRED_PROVIDER_virtual/egl              = "mali-imx"
PREFERRED_PROVIDER_virtual/libgbm           = "mali-imx"
PREFERRED_PROVIDER_virtual/libgles1         = "mali-imx"
PREFERRED_PROVIDER_virtual/libgles2         = "mali-imx"
PREFERRED_PROVIDER_virtual/libgles3         = "mali-imx"
PREFERRED_PROVIDER_virtual/libgl            = "mesa"
PREFERRED_PROVIDER_virtual/mesa             = "mesa"

# Pin Weston to poky's 13.0.1. NXP's weston_14.0.2.imx requires pipewire/weston-dev
# deps that don't resolve cleanly in this layering.
PREFERRED_VERSION_weston:mx95-nxp-bsp = "13.0.1"

# ── BBMASK ────────────────────────────────────────────────────────────────────

# meta-imx-bsp (walnascar/Yocto 5.2) has bbappends for recipe versions that
# don't exist in scarthgap AGL. Mask them to avoid parse errors.
BBMASK += "meta-imx/meta-imx-bsp/recipes-graphics/mesa/mesa.bbappend"
BBMASK += "meta-imx/meta-imx-bsp/recipes-graphics/vulkan/vulkan-wsi-layer"
BBMASK += "meta-imx/meta-imx-bsp/recipes-graphics/xwayland/xwayland_24.1"

# meta-imx-bsp's qemu 9.0.2.imx uses UNPACKDIR (Yocto 5.2 rename of WORKDIR).
# Mask both target and native variants so poky's qemu_8.2.7 (scarthgap) is used.
BBMASK += "meta-imx/meta-imx-bsp/recipes-devtools/qemu/qemu_9.0.2.imx.bb"
BBMASK += "meta-imx/meta-imx-bsp/recipes-devtools/qemu/qemu-native_9.0.2.imx.bb"

# meta-imx-bsp's alsa-utils bbappend adds a patch that reverts an upstream fix
# (0001-Revert-aplay-fix-S24_LE-wav-header.patch). That fix is already present in
# poky scarthgap's alsa-utils 1.2.11, so the revert can't apply (Hunk #1 FAILED,
# reverse-applied). Mask the bbappend; FRDM doesn't need the S24_LE quirk.
BBMASK += "meta-imx/meta-imx-bsp/recipes-multimedia/alsa/alsa-utils_%.bbappend"

# NXP weston recipes require pipewire/weston-dev deps that don't resolve in this layering.
# Use poky's weston 13.0.1 (see PREFERRED_VERSION above).
BBMASK += "meta-imx/meta-imx-bsp/recipes-graphics/wayland/weston_14.0.2.imx.bb"
BBMASK += "meta-imx/meta-imx-bsp/recipes-graphics/wayland/weston_10.0.5.imx.bb"
BBMASK += "meta-freescale/recipes-graphics/wayland/weston_10.0.5.imx.bb"
BBMASK += "meta-freescale/recipes-graphics/wayland/weston_12.0.4.imx.bb"

# NXP wayland/wayland-protocols recipes target recipe versions not in scarthgap
# or use UNPACKDIR. Mask all; poky's wayland 1.22.0 / wayland-protocols 1.36 are used.
BBMASK += "meta-imx/meta-imx-bsp/recipes-graphics/wayland/wayland_%.bbappend"
BBMASK += "meta-imx/meta-imx-bsp/recipes-graphics/wayland/wayland-protocols_1.41.imx.bb"
BBMASK += "meta-freescale/recipes-graphics/wayland/wayland-protocols_1.32.imx.bb"

# GPU rendering: use meta-imx-bsp's mali-imx_r54p1.2 (priority 8, correct for i.MX95).
# Keep meta-freescale's older mali-imx_r50.4 masked so r54p1.2 wins unambiguously.
BBMASK += "meta-freescale/recipes-graphics/mali"

# NXP libdrm forks conflict with poky's libdrm in scarthgap.
BBMASK += "meta-imx/meta-imx-bsp/recipes-graphics/drm/libdrm_2.4.123.imx.bb"
BBMASK += "meta-imx/meta-imx-bsp/recipes-graphics/drm/libdrm_2.4.116.imx.bb"

# wireplumber bbappend uses UNPACKDIR (Yocto 5.2); empty in scarthgap → install fails.
BBMASK += "meta-imx/meta-imx-bsp/dynamic-layers/multimedia-layer/recipes-multimedia/wireplumber/wireplumber_%.bbappend"

# meta-imx-bsp and meta-freescale pipewire bbappends add GStreamer pipewiresrc
# patches that don't apply cleanly to pipewire 1.0.9 in scarthgap (wrong context /
# already upstream). Since we use standard gstreamer (NXP gstreamer is masked),
# none of these patches are needed. Mask both bbappends.
BBMASK += "meta-imx/meta-imx-bsp/dynamic-layers/multimedia-layer/recipes-multimedia/pipewire/pipewire_%.bbappend"
BBMASK += "meta-freescale/dynamic-layers/multimedia-layer/recipes-multimedia/pipewire/pipewire_%.bbappend"

# NXP gstreamer forks reference NXP-specific libdrm modifiers (plugins-good) and
# NXP wayland-protocols extensions (plugins-bad: alpha-compositing-unstable-v1.xml)
# that are not available with standard libdrm/wayland-protocols. Fall back to poky.
BBMASK += "meta-freescale/recipes-multimedia/gstreamer/gstreamer1.0-plugins-good_1.24.7.imx.bb"
BBMASK += "meta-freescale/recipes-multimedia/gstreamer/gstreamer1.0-plugins-bad_1.24.7.imx.bb"
BBMASK += "meta-imx/meta-imx-bsp/recipes-multimedia/gstreamer/gstreamer1.0-plugins-good_1.26.6.imx.bb"
BBMASK += "meta-imx/meta-imx-bsp/recipes-multimedia/gstreamer/gstreamer1.0-plugins-bad_1.26.6.imx.bb"

# meta-imx-bsp psplash bbappend uses UNPACKDIR (Yocto 5.2) to install imx.conf;
# UNPACKDIR is undefined in scarthgap so install tries to stat '/imx.conf'.
BBMASK += "meta-imx/meta-imx-bsp/recipes-core/psplash/psplash_git.bbappend"

# meta-imx-bsp linux-firmware bbappend uses UNPACKDIR and installs Murata QCA/CYW
# firmware for chips not on FRDM-IMX95 (which uses IW612). Mask it entirely.
BBMASK += "meta-imx/meta-imx-bsp/recipes-kernel/linux-firmware/linux-firmware_%.bbappend"

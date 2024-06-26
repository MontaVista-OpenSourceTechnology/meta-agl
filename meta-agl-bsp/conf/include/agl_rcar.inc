require conf/include/agl_rcar-nogfx.inc

# Enable AGL virtualization features
MACHINE_FEATURES:append:rcar-gen3 = " agl-egvirt"

# Enable Gfx Pkgs
MACHINE_FEATURES:append:rcar-gen3 = " gsx"
BB_MULTI_PROVIDER_ALLOWED:append:rcar-gen3 = " virtual/libgl virtual/egl virtual/libgles1 virtual/libgles2"

# for Wayland/Weston
PREFERRED_PROVIDER_virtual/libgles1:rcar-gen3 = ""
PREFERRED_PROVIDER_virtual/libgles2:rcar-gen3 = "virtual-gles-user-module"
PREFERRED_PROVIDER_virtual/egl:rcar-gen3 = "virtual-gles-user-module"
PREFERRED_PROVIDER_virtual/libgl:rcar-gen3 = ""
PREFERRED_PROVIDER_virtual/mesa:rcar-gen3 = "mesa"

PREFERRED_PROVIDER_libgbm:rcar-gen3 = "libgbm"
PREFERRED_PROVIDER_virtual/libgbm:rcar-gen3 = "libgbm"
PREFERRED_RPROVIDER_libgbm-dev:rcar-gen3 = "libgbm"

PREFERRED_RPROVIDER_libomxil:rcar-gen3 = "omx-user-module"
PREFERRED_PROVIDER_virtual/libomxil:rcar-gen3 = "omx-user-module"
VIRTUAL-RUNTIME_libomxil:rcar-gen3 = "omx-user-module"

# Add for gstreamer plugins ugly
LICENSE_FLAGS_ACCEPTED:rcar-gen3 = "commercial"

MACHINE_FEATURES:append:rcar-gen3 = " multimedia"

DISTRO_FEATURES:append:rcar-gen3 = " use_eva_pkg"

#DISTRO_FEATURES:append:rcar-gen3 = " h265dec_lib mpeg2dec_lib"
DISTRO_FEATURES:append:rcar-gen3 = " h264dec_lib h264enc_lib aaclcdec_lib aaclcdec_mdw"

# Mask out meta-renesas-rcar-gen3's tweaks to weston-init, as they do
# not seem necessary for anything in AGL, and the addition of
# dbus.service and multi-user.target dependencies to the weston systemd
# unit that is done is problematic with respect to potentially blocking
# weston if any user units like application framework "platform"
# services fail. They also likely affect boot up speed with respect to
# getting weston started.  There is no clear rationale expressed in the
# meta-renesas-rcar-gen3 commit history for the extra dependencies, and
# testing shows no issues on H3ULCB when not having them.
BBMASK += "meta-renesas/meta-rcar-gen3/recipes-graphics/wayland/weston-init.bbappend"

# Add graphics and decoder drivers to packagegroup-machine-base
# recommendation.
MACHINE_EXTRA_RRECOMMENDS:append:rcar-gen3 = " \
    kernel-module-pvrsrvkm \
    kernel-module-vsp2 \
    kernel-module-vspm  \
    kernel-module-vspm-if \
    omx-user-module \
"

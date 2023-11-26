MACHINE = "rockchip-rk3588-nanopc-t6"

BBMASK += " \
    meta-rockchip/recipes-multimedia/gstreamer \
    meta-rockchip/recipes-graphics/wayland/weston_%.bbappend \
    "

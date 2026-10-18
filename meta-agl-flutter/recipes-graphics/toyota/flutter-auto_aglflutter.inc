ADD_VULKAN = "${@bb.utils.contains("DISTRO_FEATURES", "vulkan", " backend-wayland-vulkan", "", d)}"
REMOVE_EGL = "${@bb.utils.contains("DISTRO_FEATURES", "vulkan", "backend-wayland-egl egl-3d egl-transparency egl-multisample", "", d)}"

# Disable watchdog for now to reduce log spam.
# Further investigation is required into what it would take to
# properly enable it like in a production implementation.
AGL_FLUTTER_PACKAGECONFIG_REMOVE = "wdt_systemd"
PACKAGECONFIG:remove = "${AGL_FLUTTER_PACKAGECONFIG_REMOVE}"

PACKAGECONFIG:append:raspberrypi4 = "${ADD_VULKAN}"
PACKAGECONFIG:remove:raspberrypi4 = "${REMOVE_EGL}"

PACKAGECONFIG:append:raspberrypi5 = "${ADD_VULKAN}"
PACKAGECONFIG:remove:raspberrypi5 = "${REMOVE_EGL}"

PACKAGECONFIG:append:rk3588s = "${ADD_VULKAN}"
PACKAGECONFIG:remove:rk3588s = "${REMOVE_EGL}"

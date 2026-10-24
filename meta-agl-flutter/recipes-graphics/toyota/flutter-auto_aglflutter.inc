# Temporarily override to pick up some fixes that meta-flutter has not
# gotten yet (as of 2026/10/21).
HOMESCREEN_COMMIT = "223a6af3a86b60060e44a321438cb2861ac46d7d"

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

# flutter-surround-view shows its camera feeds as platform views, which
# ivi-homescreen only supports with the FlutterCompositor path.
PACKAGECONFIG:append:raspberrypi5 = " compositor"

# AGL's DISTRO does not enable the 'vulkan' DISTRO_FEATURE, so vulkan-loader is
# skipped and mali-imx's build-time DEPENDS on it cannot be satisfied
# (Nothing PROVIDES 'vulkan-loader'). We only need the Mali EGL/GLES/GBM stack for
# Weston + Flutter GPU rendering, not the Vulkan ICD. Drop the vulkan-loader build
# dependency and the -libvulkan package's RDEPENDS on the (masked) vulkan-wsi-layer.
# The -libvulkan package is still produced but is not installed in the image.
DEPENDS:remove = "vulkan-loader"
RDEPENDS:${PN}-libvulkan = ""

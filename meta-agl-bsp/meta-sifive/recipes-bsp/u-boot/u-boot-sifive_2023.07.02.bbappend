FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
# Need to add the original u-boot recipe location so CVE patch from poky
# will be found (see SPEC-5562 in JIRA).
FILESEXTRAPATHS:append := ":${COREBASE}/meta/recipes-bsp/u-boot/files"

SRC_URI:append = " file://0001-WIP-Make-BSP-work-under-YP-kirkstone.patch "

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

require recipes-kernel/linux/linux-agl.inc

SRC_URI_append  = " file://namespace_fix.cfg \
    "

# For Xen
SRC_URI_append = " \
    ${@bb.utils.contains('AGL_XEN_WANTED','1','file://xen-be.cfg','',d)} \
"
SRC_URI_append_m3ulcb = " \
    ${@bb.utils.contains('AGL_XEN_WANTED','1','file://r8a7796-m3ulcb-xen.dts;subdir=git/arch/${ARCH}/boot/dts/renesas','',d)} \
"
KERNEL_DEVICETREE_append_m3ulcb = " \
    ${@bb.utils.contains('AGL_XEN_WANTED','1','renesas/r8a7796-m3ulcb-xen.dtb','',d)} \
"

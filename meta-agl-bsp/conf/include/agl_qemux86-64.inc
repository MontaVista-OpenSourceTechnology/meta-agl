# Configurations to run on VirtualBox/VMWare
#
# To get wide screen than default, there are a selection of resolutions
# available:
#
#UVESA_MODE = "1024x768-32"
UVESA_MODE = "1280x1024-32"
#UVESA_MODE = "1600x1200-32"
#
# To avoid corrupt boot screen by systemd message, you can use serial
# console separated from VGA console or disable all boot messages by
# kernel command line.
#
# Configuration for serial console
QB_KERNEL_CMDLINE_APPEND:append = " console=ttyS0,115200n8"
#
# All boot message will be off
QB_KERNEL_CMDLINE_APPEND:append = " quiet"

# Add firmware required by Up^2 board and default Intel mPCIe wifi card
# sold by upshop.org
MACHINE_EXTRA_RRECOMMENDS:append = " \
    linux-firmware-i915 \
    linux-firmware-rtl8168 \
    linux-firmware-ibt-hw-37-8 \
    linux-firmware-iwlwifi-7265d \
    wireless-regdb-static \
"

# Image support
# NOTE: wic.{xz,bmap} are here since qemu targets override
#       AGL_DEFAULT_IMAGE_FSTYPES to not include them, but for Intel
#       we actually do want them for use on physical hardware.
AGL_EXTRA_IMAGE_FSTYPES = "wic.xz wic.bmap ${@bb.utils.contains('AGL_FEATURES', 'AGLCI', 'wic.vmdk.xz', 'wic.vmdk', d)}"

# Root device
ROOT_VM = "root=PARTUUID=${DISK_SIGNATURE}-02"

# Force the virtio video device as 'vmware' doesn't always work
QB_OPT_APPEND:append = " -vga virtio"

# DRM device weston/compositor systemd unit should depend upon
WESTON_DRM_DEVICE = "dev-dri-card0.device"

# Use our own wks file
WKS_FILE = "systemd-intel-corei7-64-bootdisk.wks"

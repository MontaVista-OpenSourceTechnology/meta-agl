require agl_imx-common.inc

# Force use of the community supported LTS kernel instead of the
# default linux-imx
IMX_DEFAULT_KERNEL_imx8mqevk = "linux-fslc-imx"

# For EVKB wifi support
MACHINE_FEATURES_append = " bcm4356"

# Add helper to drive setting up HCI UART device
MACHINE_EXTRA_RRECOMMENDS_append = " hci-uart-helper"

AGL_DEFAULT_INITRAMFS_FSTYPES := ""

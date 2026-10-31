# Default IMAGE FSTYPES - tegraflash for flashing and ext3 for netboot
AGL_DEFAULT_IMAGE_FSTYPES := "tegraflash-tar.zst ext3.xz"
# Default initramfs fstypes - ext3 for netboot and cpio.gz for flashing
AGL_DEFAULT_INITRAMFS_FSTYPES := "ext3.gz cpio.gz"

# enforce nvme0n1p1
TNSPEC_BOOTDEV:forcevariable = "nvme0n1p1"
TNSPEC_BOOTDEV_DEFAULT:forcevariable = "nvme0n1p1"

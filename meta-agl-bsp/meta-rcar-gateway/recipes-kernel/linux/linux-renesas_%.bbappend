FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " \
    ${@bb.utils.contains('MACHINE_FEATURES', 'canfd', 'file://0001-Porting-to-support-device-driver-Canfd-from-Control-.patch', '', d)} \
"

do_install:append () {

    # Remove firmware file that is not packaged in the kernel.
    # It throws an error during do_package.
    # It seems to be moved out of the kernel in later BSP versions.
    rm -rf ${D}/lib/firmware/r8a779f0_ufs.bin
    rm -rf ${D}/lib/firmware
    rm -rf ${D}/lib

}


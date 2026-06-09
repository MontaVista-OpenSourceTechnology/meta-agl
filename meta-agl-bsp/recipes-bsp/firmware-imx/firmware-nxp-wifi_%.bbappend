# meta-freescale's firmware-nxp-wifi_1.1.bb installs firmware for several chips
# whose FILES lists are missing entries that exist in the newer NXP firmware
# tarball (8997 _v4, 9098 _v1, aw693 *.bin.se, iw610 *.bin.se), triggering
# do_package's installed-vs-shipped QA check. FRDM-IMX95 uses the IW612 chip
# (nxpiw612-sdio MACHINE_FEATURE) only, so remove the orphan files in do_install.
# Revisit when meta-freescale ships a FILES update that catches up with the
# firmware-imx tarball contents.
do_install:append() {
    rm -f ${D}${nonarch_base_libdir}/firmware/nxp/sduart8997_combo_v4.bin
    rm -f ${D}${nonarch_base_libdir}/firmware/nxp/sd8997_wlan_v4.bin
    rm -f ${D}${nonarch_base_libdir}/firmware/nxp/sd9098_wlan_v1.bin
    rm -f ${D}${nonarch_base_libdir}/firmware/nxp/sduart9098_combo_v1.bin
    rm -f ${D}${nonarch_base_libdir}/firmware/nxp/uartaw693_bt_v1.bin.se
    rm -f ${D}${nonarch_base_libdir}/firmware/nxp/pcieuartaw693_combo_v1.bin.se
    rm -f ${D}${nonarch_base_libdir}/firmware/nxp/pcieaw693_wlan_v1.bin.se
    rm -f ${D}${nonarch_base_libdir}/firmware/nxp/usbusb_iw610.bin.se
    rm -f ${D}${nonarch_base_libdir}/firmware/nxp/usbusbspi_iw610.bin.se
    rm -f ${D}${nonarch_base_libdir}/firmware/nxp/sduartspi_iw610.bin.se
}

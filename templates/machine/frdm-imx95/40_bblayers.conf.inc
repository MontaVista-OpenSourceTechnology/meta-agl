# meta-freescale: imx95-evk.inc base, i.MX community recipes (priority 5)
# meta-imx-bsp:  FRDM machine conf, linux-imx 6.12, u-boot-imx, M33 SM firmware (priority 8)
# meta-imx-bsp must be listed AFTER meta-freescale so its higher BBFILE_PRIORITY wins cleanly.
BBLAYERS =+ "\
  ${METADIR}/bsp/meta-freescale \
  "
BBLAYERS += "\
  ${METADIR}/bsp/meta-imx/meta-imx-bsp \
  "

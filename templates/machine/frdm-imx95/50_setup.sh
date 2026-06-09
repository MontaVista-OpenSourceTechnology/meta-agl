# FRDM-IMX95 is not present in AGL's scarthgap meta-freescale; it needs NXP's
# vendor meta-imx layer (walnascar). That layer is NOT part of the AGL repo
# manifest and must be cloned manually. Fail early with instructions if it is
# missing, so the user gets an actionable message here instead of a confusing
# "layer not found" / parse error from bitbake later.
if [ ! -e "$METADIR/bsp/meta-imx/meta-imx-bsp/conf/layer.conf" ]; then
    cat >&2 <<EOF

ERROR: machine '$MACHINE' requires NXP's meta-imx layer, which is missing.
       It is not part of the AGL repo manifest and must be cloned manually:

         git clone --depth=1 -b walnascar-6.12.49-2.2.0 \\
           https://github.com/nxp-imx/meta-imx.git \\
           "$METADIR/bsp/meta-imx"

       Then re-run aglsetup.sh (add -f to regenerate the build config).

EOF
    exit 1
fi

find_and_ack_eula $METADIR/bsp/meta-freescale EULA
export EULA_FLAG_NAME="ACCEPT_FSL_EULA"

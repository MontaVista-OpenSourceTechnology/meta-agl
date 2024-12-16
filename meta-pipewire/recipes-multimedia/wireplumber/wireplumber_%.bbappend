FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
    file://0001-linking-reset-link-when-moving-target.patch \
"

do_install:append() {
    systemd_dir="${D}${sysconfdir}/systemd/system/"

    # mask the main service, to enable split-instance configuration
    # accomodated by the services installed in wireplumber-config-agl
    # and wireplumber-policy-config-agl
    install -d ${systemd_dir}
    ln -s /dev/null ${systemd_dir}/wireplumber.service
}

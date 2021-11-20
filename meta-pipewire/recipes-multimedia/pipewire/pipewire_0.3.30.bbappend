PACKAGECONFIG = "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'bluez5', 'bluez', '', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'alsa', 'alsa pipewire-alsa', '', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'agl-devel', 'sndfile', '', d)} \
    ${@bb.utils.filter('DISTRO_FEATURES', 'systemd', d)} \
    gstreamer v4l2 \
"

SRC_URI += "\
    file://0001-alsa-plugin-allow-specifying-a-media.role-on-the-vir.patch \
    file://0001-null-sink-make-the-timerfd-non-blocking.patch \
    file://0002-node-driver-make-the-timerfd-non-blocking.patch \
"

do_install:append() {
    # install symlinks to alsalib configuration files
    for i in 50-pipewire.conf 99-pipewire-default.conf; do
        if [ -f ${D}${datadir}/alsa/alsa.conf.d/${i} ]; then
            mkdir -p ${D}${sysconfdir}/alsa/conf.d
            ln -s ${datadir}/alsa/alsa.conf.d/${i} ${D}${sysconfdir}/alsa/conf.d/${i}
        fi
    done
}

FILES:${PN}-alsa:append = "\
    ${sysconfdir}/alsa/conf.d/* \
"

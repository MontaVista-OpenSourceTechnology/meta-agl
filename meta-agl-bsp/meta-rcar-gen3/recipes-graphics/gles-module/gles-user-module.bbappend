require checksum_control.inc

RDEPENDS:${PN}:append = " wayland-wsegl"

do_install:append(){
	 sed -i 's/MODE="0660", OWNER/MODE="0660", SECLABEL{smack}="*", OWNER/g' ${D}${sysconfdir}/udev/rules.d/72-pvr-seat.rules 
	 sed -i 's/GROUP="video"/GROUP="display"/g' ${D}${sysconfdir}/udev/rules.d/72-pvr-seat.rules 
}

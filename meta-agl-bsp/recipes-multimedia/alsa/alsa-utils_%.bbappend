# walnascar alsa-utils installs udev rules to /rules.d, which is not packaged
# by the base recipe's FILES variable in scarthgap. Add it explicitly so the
# packaging QA check (installed-vs-shipped) does not fail.

FILES:${PN} += "/rules.d /rules.d/*"

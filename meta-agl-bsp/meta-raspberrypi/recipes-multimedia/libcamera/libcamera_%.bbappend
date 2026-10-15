# Mainline libcamera looks for the Pi 5's rp1-cfe entities by names the
# Raspberry Pi kernel doesn't use, so it finds no cameras. Use the
# Raspberry Pi fork of the same release.
SRC_URI:raspberrypi5 = "git://github.com/raspberrypi/libcamera.git;protocol=https;nobranch=1;tag=v0.6.0+rpt20251202"
SRCREV:raspberrypi5 = "f0e40f1c50bd0afe65727d6e407d0dcb42666ada"

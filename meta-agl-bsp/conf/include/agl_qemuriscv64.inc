# Root device
ROOT_VM = "root=PARTUUID=${DISK_SIGNATURE}-02"

# Over-ride setting in oe-core's qemuriscv64.conf
QB_MEM:qemuriscv64 = "-m 2048"

# Use our own wks file
WKS_FILE = "directdisk.wks.in"

# new rpm 4.19 in OE-Core/Poky uses CMake instead of autoconf, update
# selinux PACKAGECONFIG until meta-selinux catches up
PACKAGECONFIG[selinux] = "-DWITH_SELINUX=ON,-DWITH_SELINUX=OFF,libselinux"

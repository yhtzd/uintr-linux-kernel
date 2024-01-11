#!/bin/bash

cp skyloft_config .config
make oldconfig

make CC=cc -j40
sudo make INSTALL_MOD_STRIP=1 modules_install -j40
sudo make install
# grub2-mkconfig -o /boot/grub2/grub.cfg

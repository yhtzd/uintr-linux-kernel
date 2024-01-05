#!/bin/bash

cp .config-backup .config
make oldconfig

make CC=cc -j
make modules_install
make install
grub2-mkconfig -o /boot/grub2/grub.cfg

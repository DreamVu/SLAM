#!/bin/bash

MY_PROMPT='$ '

echo 
echo "Creating Udev rules for PAL camera";

echo "KERNEL==\"video*\", SUBSYSTEMS==\"usb\", ATTRS{idVendor}==\"2560\", ATTR{index}==\"0\", ATTRS{serial}==\"26259504\", ATTRS{manufacturer}==\"e-con systems\", SYMLINK+=\"video5\"" >/etc/udev/rules.d/mini.rules
echo "KERNEL==\"video*\", SUBSYSTEMS==\"usb\", ATTRS{idVendor}==\"2560\", ATTR{index}==\"0\", ATTRS{serial}==\"2230060E\", ATTRS{manufacturer}==\"e-con systems\", SYMLINK+=\"video6\"" >>/etc/udev/rules.d/mini.rules

echo "SUBSYSTEM==\"hid*\", ATTRS{idVendor}==\"2560\", ATTRS{serial}==\"26259504\", MODE=\"0666\", SYMLINK+=\"hid5\"" >>/etc/udev/rules.d/mini.rules

echo "SUBSYSTEM==\"hid*\", ATTRS{idVendor}==\"2560\", ATTRS{serial}==\"2230060E\", MODE=\"0666\", SYMLINK+=\"hid6\"" >>/etc/udev/rules.d/mini.rules

echo "Udev rule created for PAL Camera";
echo 
echo "[INFO] PLEASE REBOOT THE SYSTEM FOR CHANGES TO TAKE EFFECT"
exit 0

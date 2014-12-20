#!/sbin/static/busybox
export PATH=/sbin/static:/sbin

# if the userdata partition is larger then 4000MB we probably have Coldbird's unified layout
if [ `busybox blockdev --getsize64 /dev/block/platform/msm_sdcc.1/by-name/userdata | busybox sed -e 's/\([0-9]*\)[0-9]\{6\}/\1/'` -gt 4000 ]; then
    busybox ln -s /storage/emulated/legacy /sdcard
    busybox ln -s /storage/emulated/legacy /mnt/sdcard
    busybox ln -s /storage/emulated/legacy /storage/sdcard0
    busybox ln -s /mnt/shell/emulated/0 /storage/emulated/legacy
    busybox ln -s /storage/sdcard1 /extSdCard
    busybox ln -s /storage/sdcard1 /mnt/extSdCard
    busybox ln -s /storage/sdcard1 /external_sd
    busybox ln -s /storage/usbdisk /usbdisk
    busybox ln -s /storage/usbdisk /mnt/usbdisk
else
    busybox ln -s /storage/sdcard0 /sdcard
    busybox ln -s /storage/sdcard0 /mnt/sdcard
fi

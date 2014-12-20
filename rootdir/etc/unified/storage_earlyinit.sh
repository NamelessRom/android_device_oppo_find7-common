#!/sbin/static/busybox
export PATH=/sbin/static:/sbin

# if the userdata partition is larger then 4000MB we probably have Coldbird's unified layout
if [ `busybox blockdev --getsize64 /dev/block/platform/msm_sdcc.1/by-name/userdata | busybox sed -e 's/\([0-9]*\)[0-9]\{6\}/\1/'` -gt 4000 ]; then
    busybox cp /fstab.qcom.ufd /fstab.qcom
    busybox cp /init.fs.rc.ufd /init.fs.rc
else
    busybox cp /fstab.qcom.std /fstab.qcom
    busybox cp /init.fs.rc.std /init.fs.rc
fi
busybox blockdev --getsize64 /dev/block/platform/msm_sdcc.1/by-name/userdata | busybox sed -e 's/\([0-9]*\)[0-9]\{6\}/\1/' > datasize

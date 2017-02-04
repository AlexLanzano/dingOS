mount /dev/mmcblk0p1 /mnt/mmcblk0p1
cp kernel7.img /mnt/mmcblk0p1/ &
wait
umount /dev/mmcblk0p1
echo Done!

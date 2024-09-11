cd linux
mkdir -p root
mount rootfs.ext4 root
cd root/root
rm green_tee_client
cd ../../../linux
umount root
rm -rf root
cd ../
exit

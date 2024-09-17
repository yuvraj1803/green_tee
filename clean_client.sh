cd linux
mkdir -p root
mount rootfs.ext4 root
cd root/root
rm *.o
cd ../../../linux
umount root
rm -rf root
cd ../
cd client && make clean
exit

cd client && make
cd ../linux
mkdir -p root
mount rootfs.ext4 root
cd root/root
cp ../../../client/*.o .
cd ../../../linux
umount root
rm -rf root
cd ../
exit

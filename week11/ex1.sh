#!/bin/bash

sudo touch lofs.img

sudo dd if=/dev/zero of=lofs.img bs=1M count=50
sudo losetup -f  lofs.img

LOOP_DEVICE=$(losetup --associated lofs.img | cut -d: -f1)

sudo mkfs.ext4 $LOOP_DEVICE

sudo mkdir ./lofsdisk

sudo mount $LOOP_DEVICE

sudo chown $USER:$USER ./lofsdisk 

sudo echo "Ivan" >> ./lofsdisk/file1
sudo echo "Platonov" >> ./lofsdisk/file2

get_libs() {
    ldd $1 | awk 'BEGIN{ORS=" "}$1~/^\//{print $1}$3~/^\//{print $3}' | sed 's/ *$/\n/'
}



bin = $(/bin/echo)
sudo cp -f $bin ./lofsdisk
for lib in $(get_libs $bin); do
	sudo mkdir -p ./lofsdisk$(dirname $lib)
	sudo cp $lib ./lofsdisk$lib
done
bin = $(/bin/cat)
sudo cp $bin ./lofsdisk/
for lib in $(get_libs $bin); do
        sudo mkdir -p ./lofsdisk$(dirname $lib)
        sudo cp $lib ./lofsdisk$lib
done
bin = $(/bin/bash)
sudo cp $bin ./lofsdisk/
for lib in $(get_libs $bin); do
        sudo mkdir -p ./lofsdisk$(dirname $lib)
        sudo cp $lib ./lofsdisk$lib
done
bin = $(/bin/ls)
sudo cp $bin ./lofsdisk$bin
for lib in $(get_libs $bin); do
        sudo mkdir -p ./lofsdisk$(dirname $lib)
        sudo cp $lib ./lofsdisk$lib
done

sudo cp ex1 ./lofsdisk/

sudo chroot ./lofsdisk ./ex1 > ex1.txt 

./ex1 >> ex1.txt

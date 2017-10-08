#! /bin/bash

DINGOS_PATH=`pwd`
DINGOS_CONF="$DINGOS_PATH/Makefile.conf"
while read line
do
	IFS="=" read -a array <<< "$line"
	if [ ${array[0]} == "ARCH" ]; then
		DINGOS_ARCH=${array[1]}-elf
		break
	fi
done < $DINGOS_CONF


INSTALL_PATH="$DINGOS_PATH/compiler/"
URL="https://ftp.gnu.org/gnu/binutils/"
OLD_BINUTILS=`ls $DINGOS_PATH/compiler/ | grep -o "binutils[^\"]*tar\.gz"`
NEW_BINUTILS=`wget -q -O - https://ftp.gnu.org/gnu/binutils/ | grep -o "binutils[^\"]*tar\.gz" | tail -n1`

if [ "$OLD_BINUTILS" != "$NEW_BINUTILS" ]; then
	echo "New version of binutils found."

	URL=$URL$NEW_BINUTILS

	echo "Downloading binutils..."
	wget -P "$INSTALL_PATH" "$URL"


	echo "Unpackaging binutils..."
	tar -xzf $INSTALL_PATH$NEW_BINUTILS -C $INSTALL_PATH > /dev/null

	BINUTILS_PATH=$INSTALL_PATH$NEW_BINUTILS
	BINUTILS_PATH=${BINUTILS_PATH::-7}

	mkdir $INSTALL_PATH/cross/

	echo "Configuring binutils..."
	cd $BINUTILS_PATH
	./configure --target=$DINGOS_ARCH --prefix=$INSTALL_PATH/cross/ --with-sysroot --disable-nls --disable-werror

	echo "Building binutils..."
	make

	echo "Installing binutils..."
	make install
	cd $DINGOS_PATH

fi

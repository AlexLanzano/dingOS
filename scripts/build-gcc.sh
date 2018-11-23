#! /bin/bash
echo $DINGOS_PATH
INSTALL_PATH="$DINGOS_PATH/compiler/"
URL="https://ftp.gnu.org/gnu/gcc/"
OLD_GCC=`ls $DINGOS_PATH/compiler/ | grep -o "gcc[^\"]*"`
NEW_GCC=`wget -q -O - https://ftp.gnu.org/gnu/gcc/ | grep -o "gcc-[0-9][^\"/]*" | tail -n1`

if [ "$OLD_GCC" != "$NEW_GCC" ]; then
 echo "New version of gcc found."

 URL=$URL$NEW_GCC/$NEW_GCC.tar.gz

 echo "Downloading gcc..."
 wget -P "$INSTALL_PATH" "$URL"


 echo "Unpackaging gcc..."
 tar -xzf $INSTALL_PATH$NEW_GCC.tar.gz -C $INSTALL_PATH > /dev/null

 GCC_PATH=$INSTALL_PATH$NEW_GCC

 mkdir $INSTALL_PATH/cross/

 cd $GCC_PATH
 echo "Downloading prerequisites..."
 ./contrib/download_prerequisites

 echo "Configuring GCC..."
 ./configure --target=$DINGOS_ARCH --prefix=$INSTALL_PATH/cross/ --disable-nls --enable-languages=c --without-headers

 echo "Building gcc..."
 make all-gcc

 echo "Installing binutils..."
 make install-gcc
 cd $DINGOS_PATH

fi

INSTALL_PATH=`pwd`"/compiler/"

BINUTILS_URL="https://ftp.gnu.org/gnu/binutils/"
GCC_URL="https://ftp.gnu.org/gnu/gcc/"

SUFFIX=".tar.gz"

OLD_BINUTILS=`ls $INSTALL_PATH | grep -o "binutils[^\"]*" | head -1`
NEW_BINUTILS=`wget -q -O - https://ftp.gnu.org/gnu/binutils/ | grep -o "binutils[^\"]*tar\.gz" | tail -n1`
NEW_BINUTILS=${NEW_BINUTILS%$SUFFIX}

OLD_GCC=`ls $INSTALL_PATH | grep -o "gcc[^\"]*" | head -1`
NEW_GCC=`wget -q -O - https://ftp.gnu.org/gnu/gcc/ | grep -o "gcc-[0-9][^\"/]*" | tail -n1`
NEW_GCC=${NEW_GCC%$SUFFIX}

if [ "$OLD_BINUTILS" != "$NEW_BINUTILS" ]; then
 echo "New version of binutils found."

 BINUTILS_URL=$BINUTILS_URL$NEW_BINUTILS

 echo "Downloading binutils..."
 wget -P "$INSTALL_PATH" "$BINUTILS_URL"

 echo "Unpackaging binutils..."
 tar -xzf $INSTALL_PATH$NEW_BINUTILS -C $INSTALL_PATH > /dev/null

 BINUTILS_PATH=$INSTALL_PATH$NEW_BINUTILS
 BINUTILS_PATH=${BINUTILS_PATH::-7}

 echo "Configuring binutils..."
 cd $BINUTILS_PATH
 ./configure --target=$DINGOS_ARCH --prefix=$INSTALL_PATH/cross/ --with-sysroot --disable-nls --disable-werror

 echo "Building binutils..."
 make

 echo "Installing binutils..."
 make install
 cd $DINGOS_PATH

fi

if [ "$OLD_GCC" != "$NEW_GCC" ]; then
 echo "New version of gcc found."

 GCC_URL=$GCC_URL$NEW_GCC/$NEW_GCC.tar.gz
 echo $GCC_URL
 echo "Downloading gcc..."
 wget -P "$INSTALL_PATH" "$GCC_URL"


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

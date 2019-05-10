ARCH=$1
INSTALL_PATH=`pwd`"/compiler/"

CORE_COUNT=`nproc`

BINUTILS="binutils-2.32"
BINUTILS_URL="https://ftp.gnu.org/gnu/binutils/"
OLD_BINUTILS=`ls $INSTALL_PATH | grep -o "binutils[^\"]*" | head -1`

GCC="gcc-8.3.0"
GCC_URL="https://ftp.gnu.org/gnu/gcc/"
OLD_GCC=`ls $INSTALL_PATH | grep -o "gcc[^\"]*" | head -1`

mkdir -p $INSTALL_PATH

if [ -z "$OLD_BINUTILS" ]; then
 echo "New version of binutils found."

 BINUTILS_URL=$BINUTILS_URL$BINUTILS.tar.gz

 echo "Downloading binutils..."
 wget -P "$INSTALL_PATH" "$BINUTILS_URL"
 if [ $? -ne 0 ]; then
     echo "Failed to download binutils"
     exit 1
 fi
 echo "Unpackaging binutils..."
 tar -xf $INSTALL_PATH/$BINUTILS.tar.gz -C $INSTALL_PATH > /dev/null

 BINUTILS_PATH=$INSTALL_PATH/$BINUTILS

 echo "Configuring binutils..."
 cd $BINUTILS_PATH
 ./configure --target=$ARCH-elf --prefix=$INSTALL_PATH --with-sysroot --disable-nls --disable-werror

 echo "Building binutils..."
 make -j$CORE_COUNT

 echo "Installing binutils..."
 make -j$CORE_COUNT install
 cd $DINGOS_PATH

fi

if [ -z "$OLD_GCC" ]; then
 echo "New version of gcc found."

 GCC_URL=$GCC_URL$GCC/$GCC.tar.gz
 echo $GCC_URL
 echo "Downloading gcc..."
 wget -P "$INSTALL_PATH" "$GCC_URL"
 if [ $? -ne 0 ]; then
     echo "Failed to download gcc"
     exit 1
 fi

 echo "Unpackaging gcc..."
 tar -xzf $INSTALL_PATH/$GCC.tar.gz -C $INSTALL_PATH > /dev/null

 GCC_PATH=$INSTALL_PATH/$GCC

 cd $GCC_PATH
 echo "Downloading prerequisites..."
 ./contrib/download_prerequisites

 echo "Configuring GCC..."
 ./configure --target=$ARCH-elf --prefix=$INSTALL_PATH --disable-nls --enable-languages=c --without-headers

 echo "Building gcc..."
 make -j$CORE_COUNT all-gcc

 echo "Installing gcc..."
 make -j$CORE_COUNT install-gcc
 cd $DINGOS_PATH

fi

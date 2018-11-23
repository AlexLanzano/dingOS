export DINGOS_PATH=`pwd`
export DINGOS_ARCH="x86_64"
export DINGOS_CONFIG="$DINGOS_PATH/dingos.conf"

export CC="$DINGOS_PATH/compiler/gcc"
export OBJCOPY="$DINGOS_PATH/compiler/objcopy"

export CFLAGS="-Werror "
export CFLAGS+="-Werror "
export CFLAGS+="-Wextra "
export CFLAGS+="-ffreestanding "
export CFLAGS+="-nostdlib "

export INCLUDE_PATH="-I $DINGOS_PATH/include "

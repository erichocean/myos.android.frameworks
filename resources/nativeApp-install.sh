#
# Copyright 2014 myOS Group. All rights reserved.
#

APPLICATION_PATH=$(pwd)
if [ ${TARGET} = "All" ]; then
    export TARGET=MyOSApplication
    source ${MY_FRAMEWORKS_PATH}/resources/common-make.sh
    export TARGET=NativeActivity
    source ${MY_FRAMEWORKS_PATH}/resources/common-make.sh
    TARGET=All
else
    cd ${MY_FRAMEWORKS_PATH}
    ./install.sh
    cd ${APPLICATION_PATH}
    export TARGET=${TARGET}
    source ${MY_FRAMEWORKS_PATH}/resources/common-make.sh
fi



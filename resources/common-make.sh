#
# Copyright 2014 myOS Group. All rights reserved.
#

PARAM=x$1

CURRENT_DIRECTORY=$(pwd | awk -F'/' '{print $NF}')

if [ ${TARGET} = "NativeActivity" ]; then
    FRAMEWORK_NAME=NA${CURRENT_DIRECTORY}
else
    FRAMEWORK_NAME=${CURRENT_DIRECTORY}
fi

echo "============================== Building ${FRAMEWORK_NAME} =============================="

if [ ${PARAM} = "xclean" ] && [ ${CAN_CLEAN} = "YES" ]; then
    echo "------------------------------ clean ------------------------------"
    make clean
fi

make || exit

echo "============================== installing ${FRAMEWORK_NAME} =============================="

make copy

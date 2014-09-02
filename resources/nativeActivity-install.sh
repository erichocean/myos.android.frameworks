#
# Copyright 2014 myOS Group. All rights reserved.
#

PARAM1=x$1
if [ ${PARAM1} = "x" ] ; then
    PARAM1=run
elif [ ${PARAM1} = "xclean" ] ; then
    PARAM1=clean
    PARAM2=run
    PARAM3=clean
elif [ ${PARAM1} = "xnew" ] ; then
    PARAM1=run
    PARAM2=new
else
    PARAM1=$1
    PARAM2=$2
    PARAM3=$3
fi
APPLICATION_PATH=$(pwd)
cd ${MY_FRAMEWORKS_PATH}/resources
./install.sh ${PARAM1} ${PARAM2} ${PARAM3} ${APPLICATION_PATH}

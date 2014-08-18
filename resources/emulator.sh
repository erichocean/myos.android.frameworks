#
# Copyright 2014 myOS Group. All rights reserved.
#

PARAM=x$1
DEVICE=avd1
if [ ${PARAM} = "xrestart" ] ; then
echo "===== Restarting adb server ==========================="
adb kill-server
adb start-server
adb devices
exit
elif [ ${PARAM} != "x" ] ; then
DEVICE=$1
fi

#emulator -avd ${DEVICE} -gpu on &
emulator -avd ${DEVICE} &
disown

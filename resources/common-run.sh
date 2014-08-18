#
# Copyright 2014 myOS Group. All rights reserved.
#

PARAM=x$1

if [ ${PARAM} = "xnew" ] ; then
    echo "===== android update ================================="
    android update project -p . -s --target 1
#    echo
#    echo "build.xml file got created, pls add the <import file=\"commands.xml\" /> line to it then run again."
#exit
elif [ ${PARAM} = "xuninstall" ] ; then
    echo "===== uninstall ================================="
    ant uninstall
#adb shell "cd /data/app-lib;rm -r com.mn.mn*"
elif [ ${PARAM} = "xclean" ] ; then
    echo "===== ndk-build clean ================================="
    ndk-build clean
    ant clean
elif [ ${PARAM} = "xrestart" ] ; then
    echo "===== Restarting adb server ==========================="
    adb kill-server
    adb start-server
    adb devices
fi

ndk-build || exit
ant debug quit install

ant run

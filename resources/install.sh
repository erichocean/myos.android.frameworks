#
# Copyright 2014 myOS Group. All rights reserved.
#

${MY_FRAMEWORKS_PATH}/resources/home.sh

cd libraries
source ${MY_FRAMEWORKS_PATH}/libraries/install.sh
cd ..

cd frameworks
source ${MY_FRAMEWORKS_PATH}/frameworks/install.sh
cd ..

PARAM=x$1

if [ ${PARAM} = "xrun" ] ; then
    echo
    echo "****************************** run ******************************"
    if [ $2 = "new" ] ; then
        echo "------------------------------ new ------------------------------"
        cd $3
        ./run.sh new
    elif [ $2 = "clean" ] ; then
        echo "------------------------------ clean ------------------------------"
        cd $3
        ./run.sh clean
    elif [ $2 = "restart" ] ; then
        echo "------------------------------ restart ------------------------------"
        cd $3
        ./run.sh restart
    elif [ $2 = "uninstall" ] ; then
        echo "------------------------------ uninstall ------------------------------"
        cd $3
        ./run.sh uninstall
    else
        cd $2
        ./run.sh
    fi
elif [ ${PARAM} = "xclean" ] ; then
    PARAM2=x$2
    if [ ${PARAM2} = "xrun" ] ; then
        echo
        echo "****************************** run ******************************"
        if [ $3 = "new" ] ; then
            echo "------------------------------ new ------------------------------"
            cd $4
            ./run.sh new
        elif [ $3 = "clean" ] ; then
            echo "------------------------------ clean ------------------------------"
            cd $4
            ./run.sh clean
        elif [ $3 = "restart" ] ; then
            echo "------------------------------ restart ------------------------------"
            cd $4
            ./run.sh restart
        elif [ $3 = "uninstall" ] ; then
            echo "------------------------------ uninstall ------------------------------"
            cd $4
            ./run.sh uninstall
        else
            cd $3
            ./run.sh
        fi
    fi
fi

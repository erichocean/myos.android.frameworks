#
# Copyright 2014 myOS Group. All rights reserved.
#

echo
echo "****************************** libraries ******************************"

CAN_CLEAN=NO
TARGET=Universal

cd objc
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd icu
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd pixman
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd png
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd freetype
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd expat
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd fontconfig
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd cairo
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd lcms
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd MAGLESv1_enc
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

#cd MARenderControl_enc
#source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
#cd ..

#cd MAOpenglSystemCommon
#source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
#cd ..

#cd MAOpenglCodecCommon
#source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
#cd ..

cd MAEGL
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd MAKit
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

CAN_CLEAN=YES

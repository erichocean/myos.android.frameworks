#
# Copyright 2014 myOS Group. All rights reserved.
#

echo
echo "****************************** frameworks ******************************"

CAN_CLEAN=NO

TARGET=Universal

cd CoreFoundation
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd Foundation
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

TARGET=All

cd CoreGraphics
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd CoreText
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd IOKit
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd OpenGLES
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

cd CoreAnimation
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

CAN_CLEAN=YES

cd UIKit
source ${MY_FRAMEWORKS_PATH}/resources/common-install.sh
cd ..

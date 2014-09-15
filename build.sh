#
# Copyright 2014 myOS Group. All rights reserved.
#

echo
echo "****************************** frameworks ******************************"

CAN_CLEAN=NO

TARGET=Universal

cd CoreFoundation
source ${MYOS_PATH}/android/sdk/scripts/common-build.sh
cd ..

cd Foundation
source ${MYOS_PATH}/android/sdk/scripts/common-build.sh
cd ..

TARGET=All

cd CoreGraphics
source ${MYOS_PATH}/android/sdk/scripts/common-build.sh
cd ..

cd CoreText
source ${MYOS_PATH}/android/sdk/scripts/common-build.sh
cd ..

cd IOKit
source ${MYOS_PATH}/android/sdk/scripts/common-build.sh
cd ..

cd OpenGLES
source ${MYOS_PATH}/android/sdk/scripts/common-build.sh
cd ..

cd CoreAnimation
source ${MYOS_PATH}/android/sdk/scripts/common-build.sh
cd ..

CAN_CLEAN=YES

cd UIKit
source ${MYOS_PATH}/android/sdk/scripts/common-build.sh
cd ..

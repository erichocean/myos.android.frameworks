#
# Copyright 2014 myOS Group. All rights reserved.
#

echo
echo "****************************** Cleaning frameworks ******************************"

#cd CoreFoundation
#make clean
#cd ..

#cd Foundation
#make clean
#cd ..

cd CoreGraphics
make clean
cd ..

cd CoreText
make clean
cd ..

cd IOKit
make clean
cd ..

cd OpenGLES
make clean
cd ..

cd CoreAnimation
make clean
cd ..

cd UIKit
make clean
cd ..

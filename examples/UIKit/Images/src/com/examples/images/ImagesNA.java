
package com.examples.images;

public class ImagesNA extends android.app.NativeActivity {
    
    static {
        System.loadLibrary("CoreFoundation");
        System.loadLibrary("Foundation");
        System.loadLibrary("NACoreGraphics");
        System.loadLibrary("NACoreText");
        System.loadLibrary("NAIOKit");
        System.loadLibrary("NAOpenGLES");
        System.loadLibrary("NACoreAnimation");
        System.loadLibrary("NAUIKit");
        System.loadLibrary("Images");
    }
}
/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.examples.paths;

public class PathsNA extends android.app.NativeActivity {
    
    static {
        System.loadLibrary("CoreFoundation");
        System.loadLibrary("Foundation");
        System.loadLibrary("NACoreGraphics");
        System.loadLibrary("NACoreText");
        System.loadLibrary("NAIOKit");
        System.loadLibrary("NAOpenGLES");
        System.loadLibrary("NACoreAnimation");
        System.loadLibrary("NAUIKit");
        System.loadLibrary("Paths");
    }
}
### Wrapper of CCurl (Pearl Diver)

This is the android folder for the react-native app. 

which wraps a function: 
```
pow(String trytes, int minWeight, int offset);
```
Error handling is nonexistent 

To Add this wrapper to your react-native app:
- copy app/src/main/**cpp** to your android/app/src/main/  
- copy app/src/main/java/**ccurl** to your android/app/src/main/java/
- open the android folder in android studio. 
- in the build.gradle (Module: app) add to ` defaultConfig` : 
```gradle
ndk {
            abiFilters 'x86', 'armeabi-v7a'
        }
externalNativeBuild {
            cmake {
                // pass command line arguments to cmake: our CMakeLists.txt needs it
                arguments '-DANDROID_TOOLCHAIN=clang', '-DANDROID_STL=gnustl_static'
            }
        }
```
- in the same gradle file add to `android`:
```gradle
externalNativeBuild {
        cmake {
            path 'src/main/cpp/CMakeLists.txt'
        }
    }
```
- sync gradle
- in the `MainApplication` java class add: `new CCurlReactPackage()` to the `getPackages()` method:
```java 
@Override
        protected List<ReactPackage> getPackages() {
            return Arrays.<ReactPackage>asList(
                    new MainReactPackage(),
                    new CCurlReactPackage()
            );
        }
```

- This should exose the module to react-native. To access in javascript add file ccurl.js: 
```javascript
'use strict';

import {NativeModules} from 'react-native';

module.exports = NativeModules.RNCCurl;
```
- This then can be used like:
 ```javascript
 import RNCCurl from './ccurl.js';
// returns a promise 
 var promise = RNCCurl.pow(trytes, offset, minweight);
 ```

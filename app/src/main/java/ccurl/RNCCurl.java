package ccurl;

import com.facebook.react.bridge.BaseJavaModule;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactMethod;

/**
 * Created by olmul on 29/9/17.
 */

public class RNCCurl extends BaseJavaModule {

    public RNCCurl() {
        CCURLLib.init();
    }

    @ReactMethod
    void pow(String msg, int offset, int minWeight, Promise promise) {
        String s = CCURLLib.pow(msg, minWeight, offset);


        if(s == null) {
            promise.reject("BADINPUTORSYSTEM", "Something went wrong, possibly input, possibly this code");
            return;
        }

        promise.resolve(s);

    }

    @Override
    public String getName() {
        return "RNCCurl";
    }
}

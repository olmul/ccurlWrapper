package ccurl;

/**
 * Created by olmul on 29/9/17.
 */

public class CCURLLib {
    static {
        System.loadLibrary("ccurl");
    }

    public static native void init();
    public static native String pow(String trytes, int minWeight, int offset);
}

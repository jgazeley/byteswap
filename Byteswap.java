import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.File;
import java.io.IOException;
import java.util.Stack;

public class Byteswap {

	public static void main(String[] args) throws IOException {
		File inputf = new File(args[0]);
		String outputf = args[1];
		int sizef = (int)inputf.length();
		FileInputStream fis = null;
		FileOutputStream fos = null;
		byte[] bs = new byte[sizef];
		Stack<Byte> s = new Stack<Byte>();

		try {
			// create new file input stream
			fis = new FileInputStream(inputf);
			fis.read(bs);
			for(int i = 0; i < sizef; i+=4) {

				for(int j = 0; j < 4; j++) {
					s.push(bs[i+j]);
				}
				for(int j = 0; j < 4; j++) {
					bs[i+j] = s.pop();
				}
		}

		fos = new FileOutputStream(outputf);
		fos.write(bs, 0, sizef);

			} catch(Exception ex) {
			// if any error occurs
			ex.printStackTrace();
			} finally {
			// releases all system resources from the streams
			if(fis!=null)
				fis.close();
			if(fos!=null)
				fos.close();
		}
	}
}
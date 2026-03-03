import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class client {
    public static void main(String[] args) throws IOException {
        System.out.println("Client started...");
        Socket socket=new Socket("localhost",8888);
        System.out.println("Client connected...");
        ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
        ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
        Scanner sc = new Scanner(System.in);
        String c_msg = sc.nextLine();
        oos.writeObject(c_msg);
        try {
            Object from_server = ois.readObject();
            System.out.println("From Server: " + (String) from_server);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        oos.flush();
    }
}
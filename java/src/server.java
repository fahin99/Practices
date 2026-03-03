import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class server{
    public static void main(String[] args) throws IOException{
        ServerSocket serverSocket = new ServerSocket(8888);
        System.out.println("Server started...");
        while(true) {
            Socket socket = serverSocket.accept();
            ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
            ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
            try {
                Object c_msg = ois.readObject();
                System.out.println("From client: " + (String) c_msg);
                String msg = (String) c_msg;
                msg=msg.toUpperCase();
                oos.writeObject(msg);
                oos.flush();
            }
            catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
    }
}
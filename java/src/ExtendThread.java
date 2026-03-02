class NewThread extends Thread{
    NewThread(){
        super("NewThread");
        start();
    }
    public void run(){
        try{
            for(int i=0;i<5;i++){
                System.out.println(i);
                Thread.sleep(500);
            }
        }
        catch(InterruptedException e){
            System.out.println("MainThread interrupted");
        }
        System.out.println("Exiting child thread");
    }

}
public class ExtendThread {
    public static void main(String[] args) {
        new NewThread();
    }
}
class NewThread1 implements Runnable{
    Thread t;
    NewThread1(){
        t = new Thread(this,"runnable thread");
        t.start();
    }
    public void run(){
        try{
            for(int i=1;i<6;i++){
                System.out.println("Child thread "+i);
                Thread.sleep(500);
            }
        }
        catch (InterruptedException e){
            System.out.println("MainThread interrupted");
        }
    }
}

public class ImplementThread {
    public static void main(String[] args){
        new NewThread1();
    }
}
public class MainThread{
    public static void main(String[] args) {
        Thread t=Thread.currentThread();
        System.out.println("Current thread is "+t);
        t.setName("changed_name");
        System.out.println("Current thread now is "+t);
        try{
            for(int i=5;i>=0;i--){
                System.out.println(i);
                Thread.sleep(100);
            }
        }
        catch(InterruptedException e){
            System.out.println("MainThread interrupted");
        }
    }
}
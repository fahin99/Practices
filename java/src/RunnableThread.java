class NewThread2 implements Runnable{
    Thread t;
    int thread_no;
    NewThread2(int thread_no){
        t=new  Thread(this, "Runnable "+thread_no);
        this.thread_no=thread_no;
        t.start();
    }
    public void run(){
        for(int j=1;j<6;j++){
            System.out.println(thread_no+" child thread "+j);
            try{
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

public class RunnableThread{
    public static void main(String[] args){
        NewThread2 t1=new NewThread2(1);
        NewThread2 t2=new NewThread2(2);
        System.out.println("Thread 1 alive? "+t1.t.isAlive());
        System.out.println("Thread 2 alive? "+t2.t.isAlive());
        try{
            t1.t.join();
            t2.t.join();
        }
        catch(InterruptedException e){
            e.printStackTrace();
        }
        System.out.println("Thread 1 alive? "+t1.t.isAlive());
        System.out.println("Thread 2 alive? "+t2.t.isAlive());
        System.out.println("Main thread exited...");
    }
}
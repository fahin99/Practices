import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

class Producer implements Runnable{
    Thread t;
    String name;
    BlockingQueue<String> q;
    Producer(String name,BlockingQueue<String> q){
        this.name=name;
        this.q=q;
        t=new Thread(this,name);
        t.start();
    }
    public void run(){
        System.out.println(name+" started...");
        int i=0;
        while(true){
            try {
                if (q.size() >= 5) {
                    System.out.println("Queue is full");
                    Thread.sleep(2000);
                }
                i++;
                q.put("cake "+i);
                System.out.println(name+ " created cake "+i);
                Thread.sleep(500);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}

class Consumer implements Runnable{
    BlockingQueue<String> q;
    String name;
    Thread t;
    Consumer(String name,BlockingQueue<String> q){
        this.name=name;
        this.q=q;
        t=new Thread(this,name);
        t.start();
    }
    public void run(){
        System.out.println(name+" started...");
        while(true){
            try{
                if(q.size()==0){
                    System.out.println("Queue is empty");
                    Thread.sleep(2000);
                }
                System.out.println(name+" got "+q.take());
                Thread.sleep(800);
            }
            catch(InterruptedException e){
                throw new RuntimeException(e);
            }
        }
    }
}

public class Producer_Consumer{
    public static void main(String[] args){
        BlockingQueue<String> q=new ArrayBlockingQueue<String>(5);
        Producer producer=new Producer("Podcast", q);
        Consumer consumer1=new Consumer("Producer_1", q);
        Consumer consumer2 = new Consumer("Producer2",q);
    }
}
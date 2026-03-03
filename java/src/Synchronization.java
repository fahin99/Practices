class Printer{
    void print(Person p){
        System.out.println(p.name+ " -> Printing method...");
        for(int i=0;i<p.pages;i++){
            System.out.println(p.name+" -> printed paper "+(i+1));
        }
        System.out.println(p.name=" -> Finished");
    }
}
class Person implements Runnable{
    Thread t;
    String name;
    int pages;
    final Printer printer;
    Person(String name, int pages, Printer printer){
        this.name=name;
        this.pages=pages;
        this.printer=printer;
        t = new Thread(this,name);
        t.start();
    }
    public void run(){
        synchronized (printer){
            printer.print(this);
        }
    }
}


public class Synchronization{
    public static void main(String[] args){
        Printer printer=new Printer();
        Person hridoy = new Person("hridoy", 5,printer);
        Person mahim = new Person("mahim", 10,printer);
    }
}
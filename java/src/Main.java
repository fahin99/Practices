import java.util.ArrayList;

class Book{
    private int book_id;
    private String book_title;
    private boolean availability;
    public Book(int id, String title, boolean avail){
        book_id=id;
        book_title=title;
        availability=avail;
    }
    public int get_id(){
        return book_id;
    }
    public String getTitle(){
        return book_title;
    }
    public boolean isAvailable(){
        return availability;
    }
    public void borrow(){
        availability=false;
    }
    public void back(){
        availability=true;
    }
    public void display(){
        System.out.println("Book ID: "+book_id+", Title: "+book_title+", Availability: "+availability);
    }
}
class LibraryBranch{
    private int branch_id;
    private ArrayList<Book> books;
    private static final int MAX_BOOKS=20;
    public LibraryBranch(int id){
        branch_id=id;
        books=new ArrayList<>();
    }
    public int getBranch_id(){
        return branch_id;
    }
    public boolean add(Book b){
        if(books.size()>=MAX_BOOKS){

        }
    }
}
class Main {
    static void main(String[] args) {

    }
}

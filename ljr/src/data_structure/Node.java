package data_structure;

//定义节点
public class Node {
    public int timestamp;
    public int size;
    public Node next=null;

    public Node(int time,int s){
        timestamp = time;
        size = s;
        next = null;
    }
}

package data_structure;

//简单实现
public class Linkedlist {
    public int len;
    public Node head;  //包内的类之间可以直接使用
    public Node tail;  //尾指针

    //构造方法: 默认构造
    public Linkedlist(){
        len = 0;
        head = null;
        tail = null;
    }

    //根据字符串初始化链表。   写来方便测试的，和项目逻辑无关。
    public Linkedlist(String init){
        int len = init.length();
        String[] l = init.split("-");
        Node p=null;
        for( int i=0;i<l.length;i++){
            if (i==0){
//                Node n = new Node(Integer.parseInt(l[i]));
                String s = l[i].replace("(","");
                s = s.replace(")","");
                String[] bucket = s.split(",");
                Node n = new Node(Integer.parseInt(bucket[0]),Integer.parseInt(bucket[1]));
                p = n;
                head = n;
                tail = p;
            }
            else{
//                Node n = new Node(Integer.parseInt(l[i]));
                String s = l[i].replace("(","");
                s = s.replace(")","");
                String[] bucket = s.split(",");
                Node n = new Node(Integer.parseInt(bucket[0]),Integer.parseInt(bucket[1]));
                p.next = n;
                p = n;
                tail = p;
            }
            this.len++;
        }
    }

    //打印链表
    public void show(){
//        System.out.println("链表大小:"+ len);
        System.out.print("当前链表:");
        Node p = head;
        while(p!=null){
            System.out.print("(");
            System.out.print(p.timestamp);
            System.out.print(",");
            System.out.print(p.size);
            System.out.print(")");
            System.out.print("-->");
            if(p.next==null){
                System.out.print("null");
            }
            p = p.next;
        }
        System.out.println(" ");
    }


    //尾插
    public void append(int timestamp,int s){
        if (this.len==0){
            Node t = new Node(timestamp,s);
            this.head = t;
            this.tail = t;
            this.len++;
        }
        else{
            Node t = new Node(timestamp,s);
            tail.next = t;
            tail = t;
            len++;
        }

    }

    public void append(Node tmp){
        tail.next = tmp;
        tail = tmp;
        len++;
    }

    //头插
    public void head_insert(int timestamp,int s){
        if (this.len==0){
            Node t = new Node(timestamp,s);
            this.head = t;
            this.tail = t;
            this.len++;
        }
        else{
            Node t = new Node(timestamp,s);
            t.next = head;
            this.head = t;
            this.len++;
        }

    }

    //删除最旧桶
    public void delete_tail(){
        //链表空
        if (len==0){
            return;
        }
        //只有一个节点
        if (len==1){
            len = 0;
            head = null;
            tail = null;
            return;
        }
        //
        Node p = head;
        while(p.next!=tail){
            p = p.next;
        }
        p.next = null;
        tail = p;
        len--;
    }

    //合并指定位置节点和下一节点（通过数据整合到前一节点，后面的节点简单删除
    public void merge(Node p){
        //指针是否合法
        if (p!=null&&p.next!=null){
            p.size = p.size + p.next.size;
            //删除p.next节点
            if(p.next.next!=null){
                p.next = p.next.next;
                this.len--;
            }else{
                this.tail = p;
                p.next = null;
                this.len--;
            }
        }
        else{
            System.out.println("合并位置为空，无法合并");
        }
    }

    //估计1bit个数 = 每个桶的size + 最后一个桶的size的一半
    public int eval(){
        if (this.len==0){
            return 0;
        }
        int res=0;
        Node p =head;
        while(p.next!=null){
            res = res + p.size;
            p = p.next;
        }
        //尾节点/最后一个桶 如果有超出
        res+= 0.5*p.size;
        return res;
    }



    //按索引插入

    //删除节点

    //按位置找到节点

    //按位置修改节点
}


//模板实现，泛型实现

//定义链表接口


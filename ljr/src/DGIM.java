import data_structure.Linkedlist;
import data_structure.Node;

public class DGIM {
    public static void main(String[] args){
        // "(3,1),(4,2),(6,2)"
//        Linkedlist l = new Linkedlist("(3,1)-(4,2)-(6,2)");
        Linkedlist l = new Linkedlist();
        l.show();
        int[] mydata = {0,1, 0, 1, 1, 0,0,0,1,0,0,1,0,0,1,1,1,0,1,1,0,1};
        int datasize = mydata.length;
        int window = 7;
        //打印估计值和真实的值的间隔
        int eval_interval = 2;
        //真实值
        int true_value =0;
        //什么时候显示桶的情况
        int show_bucket_time1 = 2;
        int show_bucket_time2 = 4;
        int show_bucket_time3 = 7;
        int current_time = 1;
        //移动指针，判断移除最旧桶（头插法建表的，链表的尾节点
        while(current_time<=datasize){
            //判断是否有落后的桶
            if ((l.tail!=null) && (l.tail.timestamp<=current_time-window)){
                //删除尾节点/落后的桶
                l.delete_tail();
            }
            //1到来：
            if (mydata[current_time-1]==1){
                //建桶
                l.head_insert(current_time,1);
                //查看后两个桶的size是否等于当前桶size
                Node p = l.head;
                while(p.next!=null&&p.next.next!=null&&p.size==p.next.size&&p.next.size==p.next.next.size){
                    //指针后移
                    p=p.next;
                    //合并桶
                    l.merge(p);
                }


            }
            //------桶已更新完---

            //计算真实值:  判断新来到的bit是1，则计数加1; 判断移出窗口的那个bit是1，则计数减1
            if (mydata[current_time-1]==1){
                true_value++;
            }
            if ((current_time-1-window>=0)&&mydata[current_time-1-window]==1){
                true_value--;
            }

            //评估
            if (current_time%eval_interval==0){
                System.out.println("当前timestamp="+current_time);
                //打印当前所有桶
                l.show();
                //验证:打印当前窗口
                System.out.print("当前窗口：");
                System.out.print("[");
                for (int i = current_time-window;i<current_time;i++){
                    if(i>=0){
                        System.out.print(mydata[i]);
                        System.out.print(",");
                    }
                }
                System.out.println("]");
                System.out.print("估计值:");
                System.out.println(l.eval());
                System.out.print("真实值:");
                System.out.println(true_value);

                System.out.println("-----------------------");

            }
            //打印桶
//            if (current_time==show_bucket_time1){
//                l.show();
//            }
            //接收下一bit数据
            current_time++;
        }

    }

}

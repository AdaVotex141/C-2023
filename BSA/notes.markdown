![](2023-11-30-10-05-44.png)
![](2023-11-30-10-05-58.png)
![](2023-11-30-10-06-10.png)
![](2023-11-30-10-06-55.png)
![](2023-11-30-10-07-44.png)
```
void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc);
```
sending functions to sth.

extension:
BSA:vertical row of pointers->可以用其他类型的linked list、quene之类的
![](2023-11-30-10-19-43.png)
create an array of pointers

![](2023-11-30-10-21-20.png)
检查删除一个pointers of arrays
然后删除整个vertical array

实际上，每行都是有2^n的格子
所以index是固定的
0 1格 0~row=0,sum=0
1 2格 1 2~row=1~sum=2^1+2^0=3
2 4格 3 4 5 6~row=2,sum=1+2+2^2=7
3 8格 7 8 9 10 11 12 13 14~row=3,sum=15
4 16格 15 16 17 18...
...

6-4=2+1
indx indx 3和5都的exponent都是3
但是要找的是2^1和2^0 2^2

BST_rows是一共有30个vertical array of pointers
所以最后一个如果被assign的话一共有2^30的格子
但是不能用math.h

使用binary bits？？
15=1111
0：0000
3：11
16： 10000

actual=0
size=1
进去

tostring的逻辑：
1.indx<=MaxIndex就停下来
2.从头遍历，如果indx<=MaxIndex就停下来
//对所有的array row 遍历，
```C
//literate every row 
while(row<30){
    if(arr[row]!=NULL){




    }
    row++
}


```
```
Maxindex:-1
Maxindex:15
index:0
index:0
index:0
index:0
index:15
{[0]=0}{}{}{}{[15]=15}
Maxindex:100
index:0
index:0
index:0
index:0
index:15
index:15
index:100
{[0]=0}{}{}{}{[15]=15}{[0]=0}{}{}{}{[15]=15}{}{[100]=100}
```




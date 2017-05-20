# howto-use-struct
如何随意而优雅的使用结构体struct

-----------------------------------------------------------------------------------------
错误的log标记
87f342ea2bde03673aad895699ef82f3497a571a
说道sizeof的问题，对的说法是sizeof 在运行时才能知道值

822ef450642b827242cc45d99968b853f61374c1
这不是结构体的初始化问题，而是数组的问题，数组就不可以这样赋值，必须将最小元素赋值。恰恰就像二维数组那样，不可能这样做:int a[3][3]; a[0] = {1, 2, 3}; 错， 大错 ！
不只是结构体数组，任何的数组都是一样的，C编译器禁止这样的赋值操作，在初始化中是可以的。
http://blog.csdn.net/dengziliang001/article/details/8720808

-------------------------------------------------------------------------------------------
参考
0.0 从整体上讲，结构体初始化和赋值
http://blog.csdn.net/dengziliang001/article/details/8720808
http://codewenda.com/c%e8%af%ad%e8%a8%80%e7%bb%93%e6%9e%84%e4%bd%93%e7%9b%b4%e6%8e%a5%e8%b5%8b%e5%80%bc/

1.对于结构体变量赋值的误区
http://blog.csdn.net/tietao/article/details/7257835

2.零长数组相关
http://blog.csdn.net/yang_yulei/article/details/23395315

3.运算符的优先级，尤其是前两组优先级的
http://www.slyar.com/blog/c-operator-priority.html

---------------------------------------------------------------------------------------------
1.简单结构体（初始化一个包含char, int, char \*, char [x], int[][], char \*[], \）的不同场景的使用，如使用指针，如取得内部数据，如通过内部获取整体container of; 结构体内存的copy；

2.特殊结构体处理, union, attribute\_packed, char [0] ;

3.复杂结构体的处理， 结构体里面嵌套另一个结构体，如何灵活的初始化其中一部分数据，另一部分数据放到其他地方初始化，犹如rubbish.c

4.最终检测成果，请思考rubbish.c和4bitled中i2c的driver里面对结构体的应用的方式，是不是一样的呢，是如何达到相同目的的。

后记：
#10 结构体、位运算以及其他
#10.1 C语言结构体（Struct）
#10.2 C语言结构体数组
#10.3 C语言结构体和指针
#10.4 C语言枚举类型（Enum）
#10.5 C语言共用体（Union）
#10.6 大端小端以及判别方式
#10.7 C语言位域(位段)
#10.8 C语言位运算
#10.9 对数据或文件内容进行加密
#10.10 用typedef给类型起一个别名
#10.11 C语言const：禁止修改变量的值

5.请思考，如何像内核那样，通过结构体来实现面向对象，c也是面向对象的，这是非c程序员不会知道的。

---------------------------------------------------------------------------------
意外收获
使用结构体，如果想要在被调用的函数里面，来遍历结构体的成员整型int [x]数组将变得很简单，不必在参数中加入数组的长度 x.

意外收获
本以为知道了数组，但是在结构体中使用数组才算真的知道了数组的初始化，赋值等等的问题和里面的坑，就是初始化可以 如二维数组的元素[0] = {1, 2, 3}，或者一维数组元素[0] = 1这种形式， 但
定义之后，放到别处赋值的话这么搞就是错的，一定要对最小元素逐个赋值， 比如 二维[0][0] = 1, 比如 一维[0] = 1.

当然，知道了也要时刻清醒， 因为有时候在结构体是数组或者结构体里面的成员是数组的时候容易混乱，连自己都骗了。

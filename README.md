# howto-use-struct
如何随意而优雅的使用结构体struct

-------------------------------------------------------------------------------------------
参考
0.0 从整体上讲，结构体初始化和赋值
http://blog.csdn.net/dengziliang001/article/details/8720808
http://codewenda.com/c%e8%af%ad%e8%a8%80%e7%bb%93%e6%9e%84%e4%bd%93%e7%9b%b4%e6%8e%a5%e8%b5%8b%e5%80%bc/

1.对于结构体变量赋值的误区
http://blog.csdn.net/tietao/article/details/7257835

2.零长数组相关
http://blog.csdn.net/yang_yulei/article/details/23395315

---------------------------------------------------------------------------------------------
1.简单结构体（初始化一个包含char, int, char \*, char [x], int[][], char \*[], \）的不同场景的使用，如使用指针，如取得内部数据，如通过内部获取整体container of; 结构体内存的copy；

2.特殊结构体处理, union, attribute\_packed, char [0] ;

3.复杂结构体的处理， 结构体里面嵌套另一个结构体，如何灵活的初始化其中一部分数据，另一部分数据放到其他地方初始化，犹如rubbish.c

4.最终检测成果，请思考rubbish.c和4bitled中i2c的driver里面对结构体的应用的方式，是不是一样的呢，是如何达到相同目的的。

5.请思考，如何像内核那样，通过结构体来实现面向对象，c也是面向对象的，这是非c程序员不会知道的。

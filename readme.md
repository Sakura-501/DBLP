### DBLP文献管理系统

这是一个利用C++和Python语言处理dblp.xml的文献管理系统，由**汤子韬、简智彬、邱云中、涂剑锋**合力完成。

该系统分为前后端模块，先是在后端模块运用C++和Python处理原始的dblp.xml文件生成不同目录下的可用处理文件；前端模块使用qt制作，可以调用后端处理的文件使用，并展示到界面上。

各文件夹说明：

code：存放前后端的源代码。

resource：存放处理后的资源文件

​	-graph：存放合作关系图

​	-Titles:按标题名命名文件名方式存储标题名的txt

​	-Titlessearch：顺序存储方式存储标题名的txt

​	-wordCloud：存放年度热点词的云图

​	-allauthor：顺序存储方式存储作者名

​	-coauthor：按作者名命名文件名方式存储作者名的txt

​	-year：按年方式存储标题名

​	-year_analysis：每年不同单词出现频率的记录

​	-allauthor_result.txt：作者写作次数的统计结果

​	-cluster：聚团分析结果

Based on Qt 6.2.2 (MSVC 2019, 64 bit)
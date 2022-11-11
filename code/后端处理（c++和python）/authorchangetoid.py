# coding=utf-8
import xml.sax
from xml.sax.handler import feature_external_ges
import json
import copy

class AuthorHandler(xml.sax.ContentHandler):
    # 首先初始化
    def __init__(self):
        # print("1")
        # 存标签的内容
        self.CurrentData = ""
        # 存作者名字
        self.dict = {}
        # 读取作者名字
        self.name = ""
        # 作者的id
        self.id = 0

    # 有关于外部实体的解析
    def resolveEntity(self, publicID, systemID):
        print("TestHandler.resolveEntity(): %s %s" % (publicID, systemID))
        return systemID

    # 读到开始标签时,艹一开始名字写错了，调了半小时
    def startElement(self, tag, attributes):
        # print("2")
        # 记录标签
        self.CurrentData = tag
        self.name = ""
        # if tag == "article":
        #     print(attributes["mdate"])

    # 读到结束闭合标签时
    def endElement(self, tag):
        # print("3")
        if self.CurrentData == "author":  # 如果这个标签是author，就要保存id
            # 设立一个标志检测是否存入过,没有会返回-1
            flag = self.dict.get(self.name, -1)
            if flag == -1:
                self.dict[self.name] = self.id
                self.id = self.id + 1
                self.name = ""
        self.CurrentData = ""

    # 内容事件
    def characters(self, content):
        # print("4")
        # print(content)
        if self.CurrentData == "author":
            self.name += content


class CollabrationHandler(xml.sax.ContentHandler):
    # 首先初始化
    def __init__(self, dict, file):
        # print("1")
        # 存标签的内容
        self.CurrentData = ""
        # 读取作者名字
        self.name = ""
        # 作者的id
        self.id = 0
        # 一个标记，标志读入文章的种类，也是检测开头与结尾标签
        self.flag = False
        # author-ID 的字典
        self.dict = dict
        # 存一篇文章的所有合作作者（列表
        self.author = []
        # 结果写出的文件流
        self.file = file
        # 合作作者关系的边集合set
        self.edge = set()
        # 一篇文章所有的合作作者都存在一个列表里
        self.onepage = []

    # 有关于外部实体的解析
    def resolveEntity(self, publicID, systemID):
        print("TestHandler.resolveEntity(): %s %s" % (publicID, systemID))
        return systemID

    # 读到开始标签时,艹一开始名字写错了，调了半小时
    def startElement(self, tag, attributes):
        # print("2")
        # 记录标签
        self.CurrentData = tag
        self.name = ""
        # if (tag == "article" or tag == "inproceedings" or tag == "proceedings" or
        # tag == "book" or tag == "incollection" or tag == "phdthesis" or
        # tag == "mastersthesis" or tag == "www" or tag == "person" or
        # tag == "data"):
        # if tag == "article":
        if tag == "book":
            self.author.clear()  # 标签开头先初始化一遍
            self.flag = True  # 标记开始读入一篇文献
        # if tag == "article":
        #     print(attributes["mdate"])

    # 读到结束闭合标签时
    def endElement(self, tag):
        # print("3")
        # 超一开始就真只测了article。。。。。
        # if (tag == "article" or tag == "inproceedings" or tag == "proceedings" or
        # tag == "book" or tag == "incollection" or tag == "phdthesis" or
        # tag == "mastersthesis" or tag == "www" or tag == "person" or
        # tag == "data") and self.flag == True:
        # if (tag == "article") and self.flag == True:
        if (tag == "book") and self.flag == True:
            self.flag = False
            # 去除掉空列表和只有一个作者的列表
            if len(self.author) > 1:
                c = copy.deepcopy(self.author)
                self.onepage.append(c)
            # for i in self.author:
            #     for j in self.author:
            #         if i < j and (i, j) not in self.edge:
            #             self.file.write(str(i) + ' ' + str(j) + '\n')
            #             self.edge.add((i, j))

    # 内容事件
    def characters(self, content):
        # print("4")
        # print(content)
        # 首先检测是否已经进入一篇文献
        if self.flag == True:
            self.name = content
            isAuthor = self.dict.get(self.name, -1)
            if isAuthor != -1:
                # 这里是把作者名字加进去，但是考虑到名字太长，要不直接换成id值？
                self.author.append(self.name)
                # self.author.append(self.dict.get(self.name))



if __name__ == "__main__":
    # 创建一个XMLReader
    parser = xml.sax.make_parser()
    # 固定 turn off namespaces
    parser.setFeature(xml.sax.handler.feature_namespaces, 0)
    parser.setFeature(feature_external_ges, True)
    # 需要自己重写ContextHandler
    ah = AuthorHandler()
    parser.setContentHandler(ah)
    # 有关于外部实体的一些东西，不是太懂
    parser.setEntityResolver(ah)
    parser.setDTDHandler(ah)
    f = open("dblp\\dblp\\src\\dblp.xml", "r")
    parser.parse(f)
    f.close()
    # 作者和id都写入文本中
    # with open("id-all.json", "w", encoding='utf-8') as file:
    #     # for key, value in ah.dict.items():
    #     #     # print(key)
    #     #     file.write(str(value) + " " + key + "\n")
    #     json.dump(ah.dict, file)
    # file.close()

    # 直接把一篇文章下面所有作者的名字写入一个列表里面
    # 另外一个思路是作者的id值先存进来
    with open("edge-book.json", "w", encoding='utf-8') as file:
        edgehandler = CollabrationHandler(ah.dict, file)
        parser.setContentHandler(edgehandler)
        parser.setEntityResolver(edgehandler)
        parser.setDTDHandler(edgehandler)
        f = open("dblp\\dblp\\src\\dblp.xml", "r")
        parser.parse(f)
        json.dump(edgehandler.onepage, file)
    f.close()

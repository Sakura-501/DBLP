#写 coList.txt
# def print_coauthor():
#     with open()



# 1.节点列表(输入co_list形式的原始数据行)
def get_nodes(co_list):
    ''' 用来生成节点列表 co_list: 一维列表'''
    nodes_list = []
    for authors in co_list:
        auths = authors.split("|")
        for auth in auths:
            if auth not in nodes_list:
                nodes_list.append(auth)
                print("+++++++++++++++++++++++++++++++{}".format(auth))
    return nodes_list



# 2. 边列表(输入原始数据行)
def get_edges(co_list):
    ''' （Newest）co_list: 一维列表'''
    edge_list = []
    num = 1
    for authors in co_list:
        auths = authors.split("|")
        auths = sorted(auths)
        # 边
        length = len(auths)
        for i in range(length - 1):
            for j in range(i + 1, length):
                edge_list.append([auths[i], auths[j]])
                print("+++++++++++++++++++++++++++++++{}++{}".format(auths[i],auths[j]))
    return edge_list

def get_adjacency_list(nodes_list, edge_list):
    '''
        nodes_list:节点列表
        edge_list: 边列表
    '''

    # 初始化邻接表
    adjacency_list = []

    # 遍历节点名
    for node in nodes_list:
        node_co = []
        # 每个节点的邻接表：首位初始化为头结点[node,0,0,0,...,0,0]
        node_co.append(node)

        # 遍历所有边,对节点进行匹配
        for edge in edge_list:
            # 对包含当前节点的边,提取连接关系。
            if node in edge:
                for each_node in edge:
                    if (each_node != node) and (each_node not in node_co):
                        node_co.append(each_node)  # 添加子节点
        adjacency_list.append(node_co)
        print("+++++++++++++++++++++++++++++++{}".format(node_co))
    return adjacency_list

tpco_list=""
with open('coList.txt','r')as readfile:
    List=readfile.read()
    tpco_list+=List
tpco_list=tpco_list.split('\n')
co_List=[]
for char in tpco_list:
    if char!='':
        co_List.append(char)
# print(co_List)
nodes=get_nodes(co_List)
print("get_nodes++++++++++++++finish")
# print(len(nodes))
edges=get_edges(co_List)
print("get_edges++++++++++++++finish")
# print(len(edges))
adjacency_list=get_adjacency_list(nodes,edges)
print("get_adjacency_list++++++++++++++finish")
print(adjacency_list)
for list in adjacency_list:
    id0=list[0]
    # print(id0)
    toDel=[]
    for id in list:
        if int(id)<int(id0):
            toDel.append(id)
    # print(toDel)
    for dele in toDel:
        list.remove(dele)
todelL=[]
for list in adjacency_list:
    if(len(list)<2):
        todelL.append(list)
for dele in todelL:
    adjacency_list.remove(dele)
# print(adjacency_list)
with open('adList.txt','w') as writefile:
    writefile.write("{} {}\n".format(str(len(nodes)),str(len(edges))))
    for list in adjacency_list:
        head=list[0]
        for id in list:
            if id!=head:
                writefile.write("{} {}\n".format(str(head), str(id)))
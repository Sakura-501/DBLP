import json


class treeNode:  # node class include properties and methods of node
    def __init__(self, name_value, num_occur, parent_node):
        self.name = name_value  # value is node string
        self.count = num_occur  # value is int
        self.node_link = None  # value is class_node
        self.parent = parent_node  # value is class_node
        self.children = {}  # content is node.name : class_node

    def inc(self, num_occur):
        self.count += num_occur  # count node

    def displaces(self, ind=1):
        a = 1
        # print('  ' * ind, self.name, ' ', self.count)
        # for child in self.children.values():
        #     child.displaces(ind + 1)  # iteration output


# update items header forms
def update_header(node_test, target_node):
    while node_test.node_link is not None:
        node_test = node_test.node_link
    node_test.node_link = target_node


# update iteratly tree (top to down)
def update_tree(items, in_tree, header_table, count):
    if items[0] in in_tree.children:
        in_tree.children[items[0]].inc(count)
    else:
        in_tree.children[items[0]] = treeNode(items[0], count, in_tree)  # build branch
        if header_table[items[0]][1] is None:
            header_table[items[0]][1] = in_tree.children[items[0]]
        else:
            update_header(header_table[items[0]][1], in_tree.children[items[0]])
    if len(items) > 1:
        update_tree(items[1:], in_tree.children[items[0]], header_table, count)


# build FP-Tree
def creat_tree(data_set, min_sup=0):  # data_set is dictionary
    header_table = {}
    for trans in data_set:
        for item in trans: # item是frozenset里面的元素
            header_table[item] = header_table.get(item, 0) + data_set[trans] # 这里应该是开始计数

    for item_1 in list(header_table.keys()):
        # 如果频率小于某个值，就会删掉
        if header_table[item_1] < min_sup:
            del (header_table[item_1])

    # # 测试一下,输出header检测一下
    # for key, value in header_table.items():
    #     print(key + ": " + str(value))

    # 检测header是否存在元素。。
    fre_item_set = set(header_table.keys())
    # print(fre_item_set)
    if len(fre_item_set) == 0:
        return None, None
    for item_1 in header_table:
        # items header table includes name and node count and address of node
        header_table[item_1] = [header_table[item_1], None]

    # # 测试一下,输出header检测一下
    # for key, value in header_table.items():
    #     print(key + ": " + str(value))

    ret_tree = treeNode("Null Set", 1, None)  # root node

    # # 测试一下原始数据
    # for key in data_set:
    #     print(key)

    for trans_set, count in data_set.items():
        local_id = {}
        for item_1 in trans_set: # item_1就是那些原始数据
            if item_1 in fre_item_set: #fre_item_set是刚才筛选出来的数据元素
                local_id[item_1] = header_table[item_1][0]

        # # 测试 (居然全部都输进去了
        # for key, value in local_id.items():
        #     print(key+": "+str(value))

        if len(local_id) > 0:
            order_set = [v[0] for v in sorted(local_id.items(), key=lambda p: p[1], reverse=True)]
            update_tree(order_set, ret_tree, header_table, count)

        # 看看排序之后的
        # for key in order_set:
        #     print(key)

    return ret_tree, header_table


def local_data(): # 本地测试数据集
    # test_data = [['A', 'C', 'E', 'B', 'F'],
    #              ['A', 'C', 'G'],
    #              ['E'],
    #              ['A', 'C', 'E', 'G', 'D'],
    #              ['A', 'C', 'E', 'G'],
    #              ['E'],
    #              ['A', 'C', 'E', 'B', 'F'],
    #              ['A', 'C', 'D'],
    #              ['A', 'C', 'E', 'G'],
    #              ['A', 'C', 'E', 'G']
    #              ]
    test_data = [['f', 'a', 'c', 'd', 'g', 'i', 'm', 'p'],
                 ['a', 'b', 'c', 'f', 'l', 'm', 'o'],
                 ['b', 'f', 'h', 'j', 'o'],
                 ['b', 'c', 'k', 's', 'p'],
                 ['a', 'f', 'c', 'e', 'l', 'p', 'm', 'n'],
                 ]
    return test_data


# example dataset
def load_data(): # 外部文件加载数据集
    # test_data = [['I1', 'I2', 'I5'],
    #              ['I2', 'I4'],
    #              ['I2', 'I3'],
    #              ['I1', 'I2', 'I4'],
    #              ['I1', 'I3'],
    #              ['I2', 'I3'],
    #              ['I1', 'I3'],
    #              ['I1', 'I2', 'I3', 'I5'],
    #              ['I1', 'I2', 'I3']]
    with open("edge.json","r",encoding='utf-8') as file: # 加载edge.json
        test_data = json.load(file)
    return test_data


def creat_set(data_set): # set的键又是一个set， 牛
    ret_dic = {}
    for trans in data_set:
        ret_dic[frozenset(trans)] = ret_dic.get(frozenset(trans), 0) + 1
    return ret_dic


# search prefix tree
def before_tree(header_table_node, bef_path):
    if header_table_node.parent is not None:
        bef_path.append(header_table_node.name)
        before_tree(header_table_node.parent, bef_path)


# search all prefix tree of the same node
def find_path(base_pat, tree_node):
    cond_pats = {}
    while tree_node is not None:
        pre_path = []
        before_tree(tree_node, pre_path)
        if len(pre_path) > 1:
            cond_pats[frozenset(pre_path[1:])] = tree_node.count
        tree_node = tree_node.node_link
    return cond_pats


# mine tree
def mine_tree(in_tree, header_table, min_sup, pre_path, fre_item_set, fre_item_count):
    fre_item_1 = [v[0] for v in sorted(header_table.items(), key=lambda p: p[1][0])]
    for base_pat in fre_item_1:
        new_fre_set = pre_path.copy()
        new_fre_set.add(base_pat)
        # support count of frequent itemset
        fre_item_count[frozenset(new_fre_set)] = header_table[base_pat][0]
        fre_item_set.append(new_fre_set)
        cond_pat_path = find_path(base_pat, header_table[base_pat][1])
        my_tree, my_header = creat_tree(cond_pat_path, min_sup)
        # print("condition tree for :", new_fre_set)
        if my_tree is not None:
            my_tree.displaces(1)
        if my_header is not None:
            mine_tree(my_tree, my_header, min_sup, new_fre_set, fre_item_set, fre_item_count)
    return fre_item_set, fre_item_count


# calculate support rate %
def support_grate(fre_item_count, trans_dic):
    total_trans = sum(trans_dic.values())
    for item_set in fre_item_count.keys():
        set_grate[item_set] = float(fre_item_count[item_set] / total_trans)
    return set_grate


if __name__ == "__main__":
    fre_item = []
    fre_item_count = {}
    set_grate = {}
    # sim_data = local_data()
    sim_data = load_data() # 这里是把edge.json加载进来
    set_data = creat_set(sim_data)
    my_data_tree, my_header_table = creat_tree(set_data, 0) # 在这里要设置阈值，小于的就舍去
    # my_data_tree.displaces()  # print FP-Tree
    fre_item, fre_item_count = mine_tree(my_data_tree, my_header_table, 0, set([]), fre_item, fre_item_count)
    grate_sup = support_grate(fre_item_count, set_data)
    # print(fre_item)
    # print(fre_item_count)
    # print(grate_sup)
    for key in fre_item:
        # 当有一组关联的作者数超过十个的时候才输出来
        if len(key) > 20:

            print(key)
        with open("allresult.json","w",encoding='utf-8') as file:
            json.dump(fre_item, file)

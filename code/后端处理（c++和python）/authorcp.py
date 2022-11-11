
id_list=[]
with open(r'C:\Users\13601\Desktop\DBLP-Coauthor-master\DBLP-Coauthor-master\authors.txt','r') as readfile:
    tempid=readfile.read()
    ids=tempid.split('\n')
    # print(ids)
    for id in ids:
        # print(id)
        if id.count(',')>1 :
            id_list.append(id)

print(id_list)
with open(r'C:\Users\13601\Desktop\DBLP-Coauthor-master\DBLP-Coauthor-master\authorspy.txt','w') as writefile:
    for id in id_list:
        writefile.write("{}\n".format(id))
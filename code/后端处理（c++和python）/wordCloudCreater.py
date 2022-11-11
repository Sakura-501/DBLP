import matplotlib.pyplot as plt  # 数据可视化
import jieba  # 词语切割
import wordcloud  # 分词
from wordcloud import WordCloud, ImageColorGenerator, STOPWORDS  # 词云，颜色生成器，停止词
import numpy as np  # 科学计算
from PIL import Image  # 处理图片




for i in range(1936,2023):
    with open('D:\大作业\DBLPQuickBrowser-master\DBLPQuickBrowser\Runable_Program\src\year\{}.txt'.format(i), 'r', encoding='gbk') as f:  # 打开新的文本转码为gbk
        textfile = f.read()  # 读取文本内容
    wordlist = jieba.lcut(textfile)  # 切割词语
    print(wordlist)
    space_list = ' '.join(wordlist)  # 空格链接词语
    # print(space_list)
    backgroud = np.array(Image.open('D:\paperana\wordCould\wordcouldBG.jpg'))
    #生成词云图
    stop_word=["a", "b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","s",
		"t","u","v","w","x","y","z","an", "are", "all", "any", "been", "both", "each", "either", "one", "two", "three",
		"four", "five", "six", "seven", "eigth", "nine", "ten", "none", "little", "few", "many", "much",
		"other", "another", "some", "no", "every", "nobody", "anybody", "somebody", "everybody", "when", "on",
		"at", "as", "first", "secend", "third", "fouth", "fifth", "sixth", "ninth", "above", "over", "below",
		"under", "beside", "behind", "of", "the", "after", "from", "since", "for", "which", "by", "next",
		"where", "how", "who", "there", "where", "is", "was", "were", "do", "did", "this", "that", "in",
		"last", "tomorrow", "yesterday", "before", "because", "against", "except", "beyond", "along", "among",
		"but", "so", "towards", "to", "it", "me", "i", "he", "she", "his", "they", "them", "her", "its", "and",
		"has", "have", "my", "would", "then", "too", "or", "our", "off", "we", "be", "into", "weel", "can",">","/",
		"having", "being", "even", "us", "these", "those", "if", "ours", "with", "using", "the", "based","-","<i>","</i>","<"]
    my_stopwords = set(STOPWORDS)
    for char in stop_word:
        STOPWORDS.add(char)
    wc = WordCloud(width=563, height=567,
                   background_color='white',
                   mode='RGB',
                   mask=backgroud,  # 添加蒙版，生成指定形状的词云，并且词云图的颜色可从蒙版里提取
                   max_words=18,
                   stopwords=my_stopwords,  # 内置的屏蔽词,并添加自己设置的词语
                   font_path='C:\Windows\Fonts\STZHONGS.ttf',#设置字体
                   max_font_size=200,
                   relative_scaling=0.6,  # 设置字体大小与词频的关联程度为0.4
                   random_state=50,
                   scale=2
                   ).generate(space_list)

    image_color = ImageColorGenerator(backgroud)  # 设置生成词云的颜色
    wc.recolor(color_func=image_color)

    # plt.imshow(wc)  # 显示词云
    # plt.axis('off')  # 关闭x,y轴
    # plt.show()  # 显示
    wc.to_file('D:\paperana\wordCould\{}wordCloud.jpg'.format(i))  # 保存词云图
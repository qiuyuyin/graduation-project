import matplotlib.pyplot as plt
import matplotlib as mpl

mpl.rcParams['font.family'] = 'Times New Roman'
mpl.rcParams['font.size'] = 12
mpl.rcParams['svg.fonttype'] = 'none'


# 数据
x = [1, 2, 3, 4, 5]
y1 = [2.333, 4, 3, 1, 5]
y2 = [1, 3, 2, 4, 2]

# 画图
plt.plot(x, y1, marker='o', label='1')
plt.plot(x, y2, marker='o', label='2')

# 图形标签
plt.title('test')
plt.xlabel('xx')
plt.ylabel('yy')



# 显示图形
# 显示每个坐标点的值
for i in range(len(x)):
    plt.text(x[i], y1[i]+0.05, f'{y1[i]}', ha='center', va='bottom')
    plt.text(x[i], y2[i]+0.05, f'{y2[i]}', ha='center', va='bottom')

plt.savefig('example.svg', format='svg')

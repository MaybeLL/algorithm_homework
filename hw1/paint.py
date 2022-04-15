import numpy as np
import matplotlib.pyplot as plt

x = np.arange(0, 100000, step=10000)
est = []
true = []
with open('rst4paint.txt', 'r') as fin:
    for line in fin.readlines():
        line = line.strip('\n').split('\t')
        est.append(int(line[0]))
        true.append(int(line[1]))
# print("     idx: ", x)
print(" est sum: ", est)
print("true sum: ", true)
plt.plot(x, est, color="blue", linewidth=2.5, linestyle="-", label="estimate")
plt.plot(x, true, color="red",  linewidth=2.5, linestyle="-", label="truth")
upper = max(max(est), max(est)) + 10000
lower = min(min(est), min(est)) - 10000
plt.ylim(lower, upper)

# # 设置纵轴记号
plt.yticks(np.arange(lower,upper,step=19999))
plt.xticks(np.arange(0, 100000, step=10000))
plt.legend(loc='upper left')
plt.savefig("误差数据图.png")
plt.show()

plt.close()
loss = np.abs(np.array(est) - np.array(true)) / np.array(true)
print("loss: ", loss)
plt.plot(x, loss, color="blue", linewidth=2.5, linestyle="-", label="loss rate")
plt.legend(loc='upper left')
plt.savefig("误差率图.png")
plt.show()
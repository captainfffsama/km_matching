[toc]

使用km算法来实现检测目标之间匹配

# 使用方法
测试:
```
mkdir build
cd build
cmake ..
make 
```

具体使用方法见 test_main.cpp

# 已知可能的坑
- 现在矩阵用的float计算,可能精度出问题导致 km算不准,现在是精度差小于0.01就算一样,但是极端情况下,cost 矩阵的值代价就小于这个值,那会有问题
- label不一致和增补代价都是固定值,极端数值情况下可能会有问题



# TODO
- [ ] 尝试其他算法,比如 Gabow
- [ ] 优化 km 的 dfs,将递归修改成非递归,防止超大矩阵导致爆栈
- [ ] 优化 km 的实现,比如将 dfs 换成 bfs



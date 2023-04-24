本仓库Fork自MiniOB

毕业设计为在关系数据库上实现混合存储

之前设计的部分已经完成

现在还需要完成的内容：
- ~~实现列存中表的信息，即将数据写入到文件中~~
- ~~实现列存中表的读取~~
- ~~实现列存的同步过程~~
- ~~实现列存中表的写入，由于列ID都是不变的，所以在读取中会将之前存在的内容进行合并~~
- 实现列存中的多个RowSet的Compact
- 实现列存中的列存索引

```bash
# 运行：
cd build
cmake .. -DDEBUG=ON
make
bin/miniolap -f ../etc/olapserver.ini
# 新建shell
cd build
bin/observer -f ../etc/observer.ini
# 新建shell
cd build
bin/obclient
```

